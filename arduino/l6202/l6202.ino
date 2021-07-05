#define IN1 10 // IN1 and 2 needs to have pwm (pin with ~)
#define IN2 11 
#define EN 9 

const int speedStep =15;
const int speedDelay = 1000;// delay between speed increment

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);
  Serial.println("L6202 Test");
  
}

void loop() {

 for(int speed=0; speed<=255; speed +=speedStep)
 {
  L293D('L',speed, 1);//CW step rotation
  delay(speedDelay);// delay between each step
 }

  delay(50);// 50 millisecond delay
}


/*
 * L293D(char dir,int spd, int en)
 * dir is character either L for CW direction
 *  or R for CCW direction
 *  en is integer 1 to totate, 0 for stop
 *  spd is the speed value from 0 to 255
 */
void L293D(char dir,int spd, int en)
{
  if(dir =='L')
  {
    if(en ==0){
       Serial.println(" CW Motor Stopped");
    }else{
       Serial.print(" Rotating CW: "); 
       Serial.println(spd);/       
    }
    digitalWrite(EN ,en);
    analogWrite(IN1,spd);// send PWM with spd value to IN1
    digitalWrite(IN2,LOW);// LOW singal to IN2       
   
  }else{
    if(en ==0){
       Serial.println("Not Enabled");
    }else{
       Serial.print("Output Speed: "); 
       Serial.println(spd); 
    }    
    digitalWrite(EN ,en); 
    digitalWrite(IN1,LOW);
    analogWrite(IN2,spd); 
  }
}
