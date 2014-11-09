#include "KeyMatrix.h"

KeyMatrix::KeyMatrix(int numrows, int numcolumns, int rows[], int cols[], char* keymap)
{
  _sharedDebounce = 0;
  _numrows = numrows;
  _numcols = numcolumns;
  _rows = rows;
  _cols = cols;
  _charMap = keymap;
  _scanner = new KeyState**[_numrows];
  for (int i=0; i<_numrows; i++){
    _scanner[i] = new KeyState*[_numcols];
    pinMode(_rows[i], OUTPUT);
    digitalWrite(_rows[i], HIGH);
    for (int j=0; j<_numcols; j++){
      pinMode(_cols[j], INPUT_PULLUP);
      _scanner[i][j] = new KeyState();
    }
  }
}

KeyMatrix::~KeyMatrix(){
  for (int i=0; i<_numrows; i++){
    for (int j=0; j<_numcols; j++){
      delete _scanner[i][j];
    }
    delete _scanner[i];
  }
}

void KeyMatrix::onPress(keypadHandler fun){
  _onClick = fun;
}

void KeyMatrix::onRelease(keypadHandler fun){
  _onRelease = fun;
}

void KeyMatrix::whenPressed(keypadHandler fun, int ms){
   _pressedDebounce = ms;
   _whenPressed = fun;
}

void KeyMatrix::setDebounce(int ms){
  _sharedDebounce = ms;
}
void KeyMatrix::update(){
  for (int i=0; i<_numrows; i++){
   digitalWrite(_rows[i], LOW);
    for (int j=0; j<_numcols; j++){

      if (digitalRead(_cols[j])==LOW){
        if (_scanner[i][j]->isPressed){
          //last time it was pressed also!
          if (!_scanner[i][j]->lastState && millis()-_scanner[i][j]->firstChecked > _sharedDebounce){
            //this is time to fire up event
            _scanner[i][j]->lastState=true;
            if (_onClick){
              _onClick(pos2char(i,j));
            }
          }
          if (_whenPressed && _scanner[i][j]->lastState){
            if (millis() - _scanner[i][j]->lastRepeat > _pressedDebounce){
              _whenPressed(pos2char(i,j));
              _scanner[i][j]->lastRepeat = millis();
            }
          }
        }else{
          //it wasn't pressed last time but it is now
          _scanner[i][j]->isPressed = true;
          _scanner[i][j]->firstChecked = millis();
          _scanner[i][j]->lastState = false;
        }
        //it's pressed now
      }else{
        if (_scanner[i][j]->lastState){
          //it was pressed but it's not now - release
          _scanner[i][j]->lastState=false;
          if (_onRelease){
            _onRelease(pos2char(i,j));
          }
        }
        _scanner[i][j]->isPressed = false;
      }
    }
    digitalWrite(_rows[i], HIGH);
  }
}


char KeyMatrix::pos2char(int r, int c){
  return _charMap[_numrows*r+c];
}
