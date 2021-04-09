/*
 * This code references https://electronoobs.com/eng_arduino_tut24_2.php
 * with changes made to this specific application
 * */

 
/*    
 *    SCK             ==>     D9
 *    Vcc             ==>     Vcc (5v)
 *    Gnd             ==>     Gnd      */


//Pins
int PWM_pin = 3;

//Variables - For Modification
float set_temperature = 30;
//PID
int kp = 9.1;   int ki = 0.3;   int kd = 1.8;

//Variables - Do not modify
float temperature_read = 0.0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
int PID_value = 0;

//PID constants
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;


void setup() {
  pinMode(PWM_pin,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | 0x03;    // pin 3 and 11 PWM frequency of 980.39 Hz - fast pwm
  Time = millis(); 

  // generate a 1mhz clock pulse on Timer1 pins
  pinMode(9, OUTPUT);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 7;
  TCCR1A |= (1 << COM1A0);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
}


void loop() {
  // First we read the real value of temperature
  temperature_read = readHeaterTemp();
  //error between the setpoint and the real value
  PID_error = set_temperature - temperature_read;
  //Calculate the P value
  PID_p = kp * PID_error;
  //Calculate the I value in a range on +-3
  if(-3 < PID_error <3)
  {
    PID_i = PID_i + (ki * PID_error);
  }

  //For derivative we need real time to calculate speed change rate
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)  
  {    PID_value = 255;  }
  
  analogWrite(PWM_pin,255-PID_value);
  previous_error = PID_error;     //Remember to store the previous error for next loop.

  delay(300);
}



double readHeaterTemp() {

  uint16_t v;
  pinMode(A0, INPUT);
  
  delay(1);

  //TODO: Process A0 input coming from PCB

  return v;
}
