#include <KeyMatrix.h>
int rows=4;
int cols=4;
int rowsPins[]={4,5,6,7};
int colsPins[]={8,9,10,11};
char keymap[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void ONrelease(char key){
  Serial.print("RELEASED: ");
  Serial.println(key);
};

void ONpress(char key){
  Serial.print("PRESSED: ");
  Serial.println(key);
};

void whenPressed(char key){
  Serial.print("REPEAT: ");
  Serial.println(key);
};

KeyMatrix keypad(rows,cols,(int*)rowsPins, (int*)colsPins, (char*)keymap);
void setup(){
  Serial.begin(9600);
  keypad.onRelease(&ONrelease);
  keypad.onPress(&ONpress);
  keypad.whenPressed(&whenPressed,500);
  keypad.setDebounce(15);
}

void loop(){
  keypad.update();
}
