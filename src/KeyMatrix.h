#ifndef KeyMatrix_h
#define KeyMatrix_h

#include "Arduino.h"

typedef void (*keypadHandler)(char);

struct KeyState{
  bool isPressed;
  unsigned long firstChecked;
  bool lastState;
  unsigned long lastRepeat;
  KeyState(){
    isPressed = lastState = false;
    lastRepeat = firstChecked = 0;
  }
};

class KeyMatrix
{
public:
  KeyMatrix(int, int, int[], int[], char* );
  ~KeyMatrix();
  void setDebounce(int);
  void update();
  void whenPressed(keypadHandler fun, int ms);
  void onRelease(keypadHandler fun);
  void onPress(keypadHandler fun);
private:
  char *_charMap;
  keypadHandler _onClick;
  keypadHandler _onRelease;
  keypadHandler _whenPressed;
  int _pressedDebounce;
  int _sharedDebounce;
  int _numrows, _numcols;
  int *_rows, *_cols;
  KeyState* **_scanner;
  char pos2char(int r, int c);
};



#endif
