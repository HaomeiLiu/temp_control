#include "ADS123X.h"

#define TEMP_A0     2  //Digital Input, input MUX select
#define TEMP_A1     12 //Digital Input, temperature sensor select
#define TEMP_PDWN   3  //Digital Input, power down: hold low to power down and reset
#define TEMP_SCLK   4  //Digital Input, serial clock
#define TEMP_DOUT   5  //Digital Output, data ready (low) and data output
#define TEMP_SPEED  6  //Digital Input, data rate select
#define TEMP_GAIN0  7  //Digital Input, gain select
#define TEMP_GAIN1  8  //Digital Input, gain select

ADS123X temp;

void setup() {
	
  Serial.begin(38400);
  Serial.println("ADS123X Demo");

  Serial.println("Before setting up the temp:");
  Serial.print("read: \t\t");
  
  temp.begin(TEMP_DOUT, TEMP_SCLK, TEMP_PDWN, TEMP_GAIN0, TEMP_GAIN1, TEMP_SPEED, TEMP_A0, TEMP_A1);
  
  long value_long;
  temp.read(AIN1, value_long);
  Serial.println(value_long);			// print a raw reading from the ADC

  float value_double;
  Serial.print("read average: \t\t");
  temp.read_average(AIN1,value_double,20);
  Serial.println(value_long);  	// print the average of 20 readings from the ADC

  temp.set_scale(AIN1,2280.f);        // calibrating the temp with known temperature; see the README for details
  temp.tare(AIN1);				       

  Serial.println("After calibration:");

  Serial.print("read: \t\t");
  temp.read(AIN1, value_long);
  Serial.println(value_long);                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  temp.read_average(AIN1,value_double,20);
  Serial.println(value_long);       // print the average of 20 readings from the ADC


  Serial.println("Readings:");
}

void loop() {
  
  float value;
  Serial.print("one reading:\t");
  temp.get_units(AIN1,value,1,true);
  Serial.print(value, 1);
  float value_avg;
  Serial.print("\t| average:\t");
  temp.get_units(AIN1,value_avg,10,true);
  Serial.println(value_avg, 1);

  //temp.power_down();			        // put the ADC in sleep mode
  delay(1000);
  //temp.power_up();
}
