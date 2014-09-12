/*
 BME 464 Arduino Project
 
 Lab Design Exercise: Arduino ADC/DAC
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin, 
 and also maps to a range from -5 to 5 V and displays the result
 on the LCD shield in binary.
 
 
 The circuit:
 * 
 
 created 5 Sept. 2014
 by Karmyn McKnight & Megan Lu
 
 
 */
 
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
 
#define WHITE 0x7 
 
 

// These constants won't change.  They're used to give names
// to the pins used:
int inpin = A0;  // Analog input pin (from power supply or func gen)
int outpin = 3; // Analog output pin (to o-scope or multimeter)
float analogin = 3; // analog input (0-1023)
int int_input = 0; // integer part of input
float dec_input = 0; // decimal part of input
float actual_voltage = 0; // actual input voltage
unsigned long time;
unsigned long oldTime;
unsigned long delayLCD;


/*
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
float voltageScaled = 0.0;
float voltageAbsolute = 0.0;
float voltageDecimal = 0.0;
*/


void setup() {
  pinMode(inpin, INPUT);
  pinMode(outpin, OUTPUT);
  
  time = millis();
  oldTime = millis();
  
  lcd.begin(16,2);
  lcd.setBacklight(WHITE);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  
  time = millis();
  Serial.println(oldTime);
  Serial.println(time);
  
  // read the analog in value:
  analogin = analogRead(inpin);            
  // map it to the range of the analog out:
  Serial.println(analogin);
  actual_voltage = (analogin*10)/1023-5; // calculate actual input value
  
  // Separate into integer and decimal components
  int_input = abs(actual_voltage);
  dec_input = abs(actual_voltage) - int_input;
  
  
  // display binary number on LCD once a second
  if ((time-oldTime)>=1000) {
    Serial.println("print");
    print_LCD();
    oldTime=time;
  }
  
  // scale input for output
  float scaled_output = ((analogin + 1)/4) - 1;
  
  // output 0-5 V corresponding to input
  analogWrite(outpin, scaled_output);
  delay(1);
  
  /*
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  Serial.print(outputValue);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue); 
  */

/*
  // map the output voltage to -5 to 5
  voltageScaled = map(outputValue, 0, 255, -5, 5);  
  Serial.print(voltageScaled);
*/

/*

  // print + or - and return the absolute value
  voltageAbsolute = printPositiveNegative(voltageScaled);
  Serial.print(voltageAbsolute);
  
  */
  
  // print binary representation of integer portion of
  //    voltage value (i.e. the part before the decimal point)
  // return the remaining part after the decimal point
//  voltageDecimal = printVoltageBeforeDecimal(voltageAbsolute);
  
  
  // print binary representation of the portion of the voltage
  //    value after the decimal point
//  decimalToBinary(voltageDecimal);


  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
//  delay(2);                     
}



void print_LCD(){
  lcd.setCursor(0,0);
  
  // Print sign
  if (actual_voltage>=0) {
    lcd.print("+");
  }
  else {
    lcd.print("-");
  }
  
  // Print integer
  if(int_input == 0){
    lcd.print("000."); 
  }

  if(int_input == 1){
    lcd.print("001."); 
  }

  if(int_input == 2){
    lcd.print("010."); 
  }

  if(int_input == 3){
    lcd.print("011."); 
  }

  if(int_input == 4){
    lcd.print("100."); 
  }

  if(int_input == 5){
    lcd.print("101."); 
  }
  
  // Print decimal
  int n = 12;  // 12 digits for decimal
  
  while(n>0) {
    // use trick for multiplication by 2 for decimals
    deci_input = dec_input*2;
    
    if (dec_input < 1) {
      lcd.print("0");
    }
    
    if (dec_input >= 1) {
      lcd.print("1");
      dec_input = dec_input - 1;
    }
    
    n = n-1;
  }
    
}




/*
float printPositiveNegative(float voltageInput) {
  lcd.setCursor(0,0);
  if (voltageInput>=0) {
    lcd.print("+");
    return voltageInput;
  }
  else {
    lcd.print("-");
    return abs(voltageInput);
  }
}


float printVoltageBeforeDecimal(float voltageValue) {
  lcd.setCursor(1,0);
  if (voltageValue>=5) {
    lcd.print("101.");
    return (voltageValue-5);
  }
  else if (voltageValue>=4) {
    lcd.print("100.");
    return (voltageValue-4);
  }
  else if (voltageValue>=3) {
    lcd.print("011.");
    return (voltageValue-3);
  }
  else if (voltageValue>=2) {
    lcd.print("010.");
    return (voltageValue-2);
  }
  else if (voltageValue>=1) {
    lcd.print("001.");
    return (voltageValue-1);
  }
  else {
    lcd.print("000.");
    return voltageValue;
  }
  
}



void decimalToBinary(float value) {

  int i=0;
  while (value>0) {
    lcd.setCursor((5+i),0);
    value=value*2;
    if (value>=1) {
      lcd.print("1");
      value=value-1;
    }
    else {
      lcd.print("0");
    }
    i=i+1;
  }  
  
}

*/


