#include <Servo.h>
 #include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
/*Servo servothumb;         
Servo servoindex;         
Servo servomiddle;
Servo servoring;
Servo servopinky;*/
// Déclaration des broches pour chaque servomoteur
#define servothumb 3
#define servoindex 6
#define servomiddle 0
#define servoring 8
#define servopinky 11
 
char number[50];
char c;
String data;
int state = 0;
String myStringRec;
int stringCounter = 0;
bool stringCounterStart = false;
String myRevivedString;
int stringLength = 6;
 
int servoPinky,servoMiddle,servoIndex,servoThumb,servoRing;
int myVals[] ={0,0,0,0,0} ;
 
int myButton= 1;
bool portable;

// Objets Servo pour chaque servomoteur
Adafruit_PWMServoDriver pwm;
uint8_t servoPins[6] = {servothumb,servoindex,servomiddle,servoring,servopinky};

// Paramètres des servomoteurs
#define SERVO_MIN_PULSE_WIDTH 150
#define SERVO_MAX_PULSE_WIDTH 600
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  /*servothumb.attach(9); 
  servoindex.attach(10); 
  servopinky.attach(11);
  servoring.attach(12);
  servomiddle.attach(13);*/
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(100);
   
}
void loop() {

   
receiveData();
  if (servoPinky ==1){  /*servopinky.write(180);*/pwm.setPWM(servopinky, 0, SERVO_MIN_PULSE_WIDTH); }else{/*servopinky.write(0);*/pwm.setPWM(servopinky, 0, SERVO_MAX_PULSE_WIDTH);}
  if (servoIndex ==1){  /*servoindex.write(180)*/pwm.setPWM(servoindex, 0, SERVO_MIN_PULSE_WIDTH);}else{/*servoindex.write(0)*/pwm.setPWM(servoindex, 0, SERVO_MAX_PULSE_WIDTH);}
  if (servoMiddle ==1){ /* servomiddle.write(180)*/pwm.setPWM(servomiddle, 0, SERVO_MIN_PULSE_WIDTH);}else{/*servomiddle.write(0)*/pwm.setPWM(servomiddle, 0, SERVO_MAX_PULSE_WIDTH);}
  if (servoThumb ==1){  /*servothumb.write(180)*/pwm.setPWM(servothumb, 0, SERVO_MIN_PULSE_WIDTH);}else{/*servothumb.write(0)*/pwm.setPWM(servothumb, 0, SERVO_MAX_PULSE_WIDTH);}
  if (servoRing ==1){ /* servoring.write(180)*/pwm.setPWM(servoring, 0, SERVO_MIN_PULSE_WIDTH);}else{/*servoring.write(0)*/pwm.setPWM(servoring, 0, SERVO_MAX_PULSE_WIDTH);}
}
 
void receiveData() {
 while (Serial.available()) {
   char c = Serial.read();
    //data = Serial.read();
    //Serial.println(c);
    
    if (c == '$'){
      stringCounterStart = true;
    }
    if (stringCounterStart == true )
    {
      if (stringCounter < stringLength)
      {
        myRevivedString = String(myRevivedString + c);
        stringCounter++;
      }
      if (stringCounter >= stringLength) {
        stringCounter = 0; stringCounterStart = false;
        servoPinky = myRevivedString.substring(1, 2).toInt();
        servoRing = myRevivedString.substring(2, 3).toInt();
        servoMiddle = myRevivedString.substring(3, 4).toInt();
        servoIndex = myRevivedString.substring(4, 5).toInt();
        servoThumb = myRevivedString.substring(5, 6).toInt();
        /*Serial.print(servoPinky);
        Serial.print(" ");
        Serial.print(servoRing);
        Serial.print(" ");
        Serial.print(servoMiddle);
        Serial.print(" ");
        Serial.print(servoIndex);
        Serial.print(" ");
        Serial.println(servoThumb); */   
        myRevivedString = "";
      }
    }
  }
}
