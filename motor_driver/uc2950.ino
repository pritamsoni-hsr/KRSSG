#include <avr/io.h>
#include <avr/interrupt.h>
int a=0,flag=1;
volatile int ovf=0,Error=0,Prev_Error=0,pwm_value=0;
volatile uint16_t Ticks_new=0,Ticks=0,temp=0,Target_Ticks=315;
volatile float Intg=0;
float Kp=0.28,Ki=0,Kd=0.0035,pid=0,dt=0.004096;
int Hall1=21,Hall2=20,Hall3=19;
int S1=4,S2=5,S3=6,S4=7,S5=8,S6=9;
bool direction=true;    //1-cw,0-ccw
void Stop(){
  analogWrite(S1,255);
  analogWrite(S3,255);
  analogWrite(S5,255);
  analogWrite(S2,0);
  analogWrite(S4,0);
  analogWrite(S6,0);
}
volatile int HallValue(){
  return((digitalRead(Hall1))+(digitalRead(Hall2)*2)+(digitalRead(Hall3)*4));//Bases are 1,2,4.
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
  pinMode(Hall1,INPUT);
  pinMode(Hall2,INPUT);
  pinMode(Hall3,INPUT);
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
    if (direction==1)
      Check_PWM_CW(HallValue());
    if (direction==0)
      Check_PWM_CCW(HallValue());
}
ISR(INT1_vect){
    if (direction==1)
      Check_PWM_CW(HallValue());
    if (direction==0)
      Check_PWM_CCW(HallValue());
}
ISR(INT2_vect){
    if (direction==1)
      Check_PWM_CW(HallValue());
    if (direction==0)
      Check_PWM_CCW(HallValue());
}
ISR(INT3_vect){
    Ticks++;
}
ISR(TIMER5_OVF_vect){
  Ticks_new=Ticks-temp;
  temp=Ticks;
  flag=1;
  PID();
}
void setup() {
  Serial.begin(9600);
  int myTimeout = 1;  // milliseconds for Serial.read
  Serial.setTimeout(myTimeout);
  Init_Pins();
  Init_Interrupt();
  TCCR5A=0;
  TCCR5B=(1<<CS50);//Prescaler=0.
  TIMSK5=(1<<TOIE5);//OVF Interrupt Enable.
  TCNT5=0;
  ovf=0;
}
void loop(){

  while(stream.available()){
    a=stream.read();
    b=a.toInt();
  }

  if(flag==1){
    Serial.println(Ticks_new);
    flag=0;
  }
}
void PID(){
  Error=Target_Ticks-Ticks_new;
  Intg=Intg+Error*dt;
  pid=pid+(Kp*Error)+(Kd*(Error-Prev_Error)/dt)+Ki*Intg;
  if(pid>255){
    pid=255;
  }
  else if(pid<0){
    pid=0;
  }
   Prev_Error=Error;
   pwm_value=pid;
}
