#include <avr/io.h> 
#include <avr/interrupt.h>
int pwm_value=0;
volatile int a=0;
volatile int flag=25;
volatile uint32_t Ticks=0;
volatile uint32_t Ticks_new=0;
volatile uint32_t temp=0;
volatile int ovf=0;
volatile float dt=0.004096;
volatile int Error=0;
volatile int Prev_Error=0;
volatile int Intg=0;
volatile uint32_t Target_Ticks=315;
float Kp=0.28;
float Ki=0;
float Kd=0.0035;
float pid=0;
int Hall1=21;//Pin-21
int Hall2=20;//Pin-20
int Hall3=19;//Pin-19
int PmosA=4;
int ENA=5;
int PmosB=6;
int ENB=7;
int PmosC=8;
int ENC=9;
int drxn=17;
void Stop(){
  analogWrite(PmosA,255);
  analogWrite(PmosB,255);
  analogWrite(PmosC,255);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  analogWrite(ENC,0);
}
volatile int HallValue(){
  return((digitalRead(Hall1))+(digitalRead(Hall2)*2)+(digitalRead(Hall3)*4));//Bases are 1,2,4.   
}
void Check_PWM_CW(volatile int HallValue){
  switch(HallValue){
   case 0:    //+. +. +
   {
     Stop();
     break;
   }
   case 3:    //0. +. -
   {
     analogWrite(PmosA,0);
     analogWrite(ENA,0);
     analogWrite(PmosB,pwm_value);
     analogWrite(ENB,0);
     analogWrite(PmosC,0);
     analogWrite(ENC,pwm_value);
     break;
   }
   case 2:   //-. +. 0
    {
     analogWrite(PmosA,0);
     analogWrite(ENA,pwm_value);
     analogWrite(PmosB,pwm_value);
     analogWrite(ENB,0);
     analogWrite(PmosC,0);
     analogWrite(ENC,0);
     break;
    }
   case 6:    //-. 0. +
    {
     analogWrite(PmosA,0);
     analogWrite(ENA,pwm_value);
     analogWrite(PmosB,0);
     analogWrite(ENB,0);
     analogWrite(PmosC,pwm_value);
     analogWrite(ENC,0);
     break;
    }
   case 4:    //0. -. +
   {
     analogWrite(PmosA,0);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,pwm_value);
     analogWrite(PmosC,pwm_value);
     analogWrite(ENC,0);
     break;
   }
   case 5:    //+. -. 0
   {
     analogWrite(PmosA,pwm_value);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,pwm_value);
     analogWrite(PmosC,0);
     analogWrite(ENC,0);
     break;
    }
  case 1:   //+. 0. -
  {
     analogWrite(PmosA,pwm_value);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,0);
     analogWrite(PmosC,0);
     analogWrite(ENC,pwm_value);
     break;
   }
  case 7:
  {
   Stop();
   break;
  }  
 }
}
void Check_PWM_CCW(volatile int HallValue){
  switch(HallValue){
   case 0:    //+. +. +
   {
     Stop();
     break;
   }
   case 3:    //0 - +
   {
     analogWrite(PmosA,0);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,pwm_value);
     analogWrite(PmosC,pwm_value);
     analogWrite(ENC,0);
     break;
   }
   case 2:   //-. +. 0
    {
     analogWrite(PmosA,pwm_value);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,pwm_value);
     analogWrite(PmosC,0);
     analogWrite(ENC,0);
     break;
    }
   case 6:    //-. 0. +
    {
     analogWrite(PmosA,pwm_value);
     analogWrite(ENA,0);
     analogWrite(PmosB,0);
     analogWrite(ENB,0);
     analogWrite(PmosC,pwm_value);
     analogWrite(ENC,0);
     break;
    }
   case 4:    //0. -. +
   {
     analogWrite(PmosA,0);
     analogWrite(ENA,0);
     analogWrite(PmosB,pwm_value);
     analogWrite(ENB,0);
     analogWrite(PmosC,0);
     analogWrite(ENC,pwm_value);
     break;
   }
   case 5:    //+. -. 0
   {
     analogWrite(PmosA,0);
     analogWrite(ENA,pwm_value);
     analogWrite(PmosB,pwm_value);
     analogWrite(ENB,0);
     analogWrite(PmosC,0);
     analogWrite(ENC,0);
     break;
    }
  case 1:   //+. 0. -
  {
     analogWrite(PmosA,0);
     analogWrite(ENA,pwm_value);
     analogWrite(PmosB,0);
     analogWrite(ENB,0);
     analogWrite(PmosC,pwm_value);
     analogWrite(ENC,0);
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
  pinMode(PmosA,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(PmosB,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(PmosC,OUTPUT);
  pinMode(ENC,OUTPUT);
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
    if (digitalRead(drxn)==0)
      Check_PWM_CW(HallValue());

  if (digitalRead(drxn)==1)
      Check_PWM_CCW(HallValue());
  digitalWrite(LED_BUILTIN,!(digitalRead(LED_BUILTIN)));
}
ISR(INT1_vect){
    if (digitalRead(drxn)==0)
      Check_PWM_CW(HallValue());

  if (digitalRead(drxn)==1)
      Check_PWM_CCW(HallValue());
}
ISR(INT2_vect){
  if (digitalRead(drxn)==0)
      Check_PWM_CW(HallValue());

  if (digitalRead(drxn)==1)
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
  Init_Pins();
  pinMode(LED_BUILTIN,OUTPUT);
  Init_Interrupt();
  TCCR5A=0;
  TCCR5B=(1<<CS50);//Prescaler=0.
  TIMSK5=(1<<TOIE5);//OVF Interrupt Enable.
  TCNT5=0;
  ovf=0;
}
void loop(){
  if(flag==1){
    Serial.println(Ticks_new);
    flag=0;
  }
}
void PID(){
  Error=Target_Ticks-Ticks_new;
  Intg=Intg+Error*dt;
  pid=pid+(Kp*Error)+(Kd*(Error-Prev_Error)/dt)+Ki*Intg;
  //a=1;
  if(pid>255){
    pid=255;
  }
  else if(pid<0){
    pid=0;
  }
   Prev_Error=Error;
   //pid=(pid*255)/310;
   pwm_value=pid;
}