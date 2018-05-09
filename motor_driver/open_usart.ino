#include <avr/io.h>
#include <avr/interrupt.h>

//pins
int S1=4; //pg5
int S2=5; //pe3
int S3=6; //ph3
int S4=7; //ph4
int S5=8; //ph5
int S6=9; //ph6

int H1=21;  //pd0
int H2=20;  //pd1
int H3=19;  //pd2

int D1=10; //PB3
int D2=11; //PB5
int D3=12; //PB6
uint16_t data=0;
//variables
int pwm_value=0;
bool drxn=0;

void Stop(){
  analogWrite(S1,255);
  analogWrite(S3,255);
  analogWrite(S5,255);
  analogWrite(S2,0);
  analogWrite(S4,0);
  analogWrite(S6,0);
}
// Commutation table
volatile int HallValue(){
  return((digitalRead(H1))+(digitalRead(H2)*2)+(digitalRead(H3)*4));	//Bases are 1,2,4.
}
void Check_PWM_CW(volatile int HallValue){
  switch(HallValue){
   case 0: {
	Stop();
	break;
}
   case 3: {                                      //0. +. -
	analogWrite(S1,0);
	analogWrite(S2,255);
	analogWrite(S3,pwm_value);
	analogWrite(S4,0);
	analogWrite(S5,0);
	analogWrite(S6,0);
	break;
   }
   case 2: {                                      //-. +. 0
	analogWrite(S1,0);
	analogWrite(S2,0);
	analogWrite(S3,pwm_value);
	analogWrite(S4,0);
	analogWrite(S5,0);
	analogWrite(S6,255);
	break;
}
   case 6: {                                      //-. 0. +
	analogWrite(S1,0);
	analogWrite(S2,0);
	analogWrite(S3,0);
	analogWrite(S4,255);
	analogWrite(S5,pwm_value);
	analogWrite(S6,0);
	break;
    }
   case 4: {                                      //0. -. +
	analogWrite(S1,0);
	analogWrite(S2,255);
	analogWrite(S3,0);
	analogWrite(S4,0);
	analogWrite(S5,pwm_value);
	analogWrite(S6,0);
break;
   }
   case 5: {                                      //+. -. 0
	analogWrite(S1,pwm_value);
	analogWrite(S2,0);
	analogWrite(S3,0);
	analogWrite(S4,0);
	analogWrite(S5,0);
	analogWrite(S6,255);
	break;
    }
  case 1: {                                       //+. 0. -
	analogWrite(S1,pwm_value);
	analogWrite(S2,0);
	analogWrite(S3,0);
	analogWrite(S4,255);
	analogWrite(S5,0);
	analogWrite(S6,0);
	break;
   }
  case 7:{
   Stop();
   break;
  }
 }
}
void Check_PWM_CCW(volatile int HallValue){
  switch(HallValue){
   case 0: {
     Stop();
     break;
   }
   case 3: {
     analogWrite(S1,0);
     analogWrite(S2,255);
     analogWrite(S3,0);
     analogWrite(S4,0);
     analogWrite(S5,pwm_value);
     analogWrite(S6,0);
     break;
   }
   case 2: {
     analogWrite(S1,pwm_value);
     analogWrite(S2,0);
     analogWrite(S3,0);
     analogWrite(S4,0);
     analogWrite(S5,0);
     analogWrite(S6,255);
     break;
    }
   case 6: {
     analogWrite(S1,pwm_value);
     analogWrite(S2,0);
     analogWrite(S3,0);
     analogWrite(S4,255);
     analogWrite(S5,0);
     analogWrite(S6,0);
     break;
    }
   case 4: {
     analogWrite(S1,0);
     analogWrite(S2,255);
     analogWrite(S3,pwm_value);
     analogWrite(S4,0);
     analogWrite(S5,0);
     analogWrite(S6,0);
     break;
   }
   case 5: {
     analogWrite(S1,0);
     analogWrite(S2,0);
     analogWrite(S3,pwm_value);
     analogWrite(S4,0);
     analogWrite(S5,0);
     analogWrite(S6,255);
     break;
    }
  case 1: {
     analogWrite(S1,0);
     analogWrite(S2,0);
     analogWrite(S3,0);
     analogWrite(S4,255);
     analogWrite(S5,pwm_value);
     analogWrite(S6,0);
     break;
   }
  case 7:
  {
   Stop();
   break;
  }
 }
}
void Init_Pins(){
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(S4,OUTPUT);
  pinMode(S5,OUTPUT);
  pinMode(S6,OUTPUT);
  pinMode(H1,INPUT);
  pinMode(H2,INPUT);
  pinMode(H3,INPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(18,INPUT);
  pinMode(17,INPUT);
}
void Init_Interrupt(){
  sei();
  TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12);
  TCCR2B|=(1<<CS20)|(0<<CS21)|(0<<CS22);
  TCCR3B|=(1<<CS30)|(0<<CS31)|(0<<CS32);
  EIMSK=(1<<INT0)|(1<<INT1)|(1<<INT2)|(1<<INT3);
  EICRA=(1<<ISC00)|(1<<ISC10)|(1<<ISC20)|(1<<ISC30);
}
ISR(INT0_vect){
  if (drxn == 0)
    Check_PWM_CW(HallValue());
  else if (drxn == 1)
    Check_PWM_CCW(HallValue());
}
ISR(INT1_vect){
  if (drxn == 0)
    Check_PWM_CW(HallValue());
  else if (drxn == 1)
    Check_PWM_CCW(HallValue());
}
ISR(INT2_vect){
  if (drxn == 0)
    Check_PWM_CW(HallValue());
  else if (drxn == 1)
    Check_PWM_CCW(HallValue());
}
void receiveData(){
  if (Serial.available()>0){
    data = Serial.read(); //stores data in bytes 
    pwm_value=data%127;
    drxn=data/127;
  }
}
int main(){
	Serial.begin(115200);
	Init_Pins();
  Init_Interrupt();
  
	while(1){
	receiveData();
	}
}


