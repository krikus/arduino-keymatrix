#include <KeyMatrix.h>

const int speakerPin = 11;
int rowsPins[]={2,3,4,5};
int colsPins[]={6,7,8,9};

char keymap[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

KeyMatrix keypad(4,4, (int*)rowsPins, (int*)colsPins, (char*)keymap);

//G E G E G A G F E F F D F D G F E D E G G E G G E G C H A G A H H H C
//4 3 4 3 4 5 4 A 3 A A 2 A 2 4 A 3 2 3 4 4 3 4 4 3 4 B 6 5 4 5 6 6 6 B
int char2tone(char c){
  switch (c){
    case '1': //C
      return 1915;
    case '2':
      return 1700;
    case '3':
      return 1519;
    case 'A':
      return 1432;
    case '4':
      return 1275;
    case '5':
      return 1136;
    case '6':
      return 1014;  
    case 'B': // C2
      return 956;
  }
  return 0;
}

int playTone = 0;

void pressed(char c){
  playTone = char2tone(c);
}

void released(char c){
  playTone = 0;
}

void setup(){
  pinMode(speakerPin, OUTPUT);
  keypad.onRelease(&released);
  keypad.whenPressed(&pressed,0);
}

void loop(){
  keypad.update();
  if (playTone > 0){
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(playTone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(playTone);
  }else{
    digitalWrite(speakerPin, LOW);
  }
}
