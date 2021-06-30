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
  //Read temperature
  temperature_read = readHeaterTemp();

  //Calculate PID output
  PID_value = PID_Calc(temperature_read);

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)  
  {    PID_value = 255;  }
  
  analogWrite(PWM_pin,255-PID_value);

  delay(300);
}


/******************
 * func readHeaterTemp: read current temperature and process to the correct format
 * output return_value: float, temperature in degree Celcius
 ******************/
float readHeaterTemp(){

  uint16_t v;
  pinMode(A0, INPUT);
  
  delay(1);

  //TODO: Process A0 input coming from PCB

  return v;
}

/******************
 * func PID_Calc: calculate the PID output
 * input current_heater_temp: float
 * output return_value: float
 ******************/
float PID_Calc(float current_heater_temp){
    float return_value;

    PID_error = set_temperature - current_heater_temp;
    previous_error = PID_error; //store for next loop

    //proportional
    PID_p = kp * PID_error;

    //integral
    //TODO: saturation limit
    if(-3 < PID_error <3){
        PID_i = PID_i + (ki * PID_error);
    }

    //derivative
    timePrev = Time;
    Time = millis();
    elapsedTime = (Time - timePrev) / 1000; 
    PID_d = kd*((PID_error - previous_error)/elapsedTime);

    return_value = PID_p + PID_i + PID_d;
    return return_value;
} 
