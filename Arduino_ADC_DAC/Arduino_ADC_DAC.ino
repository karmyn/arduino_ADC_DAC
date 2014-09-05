/*
 Lab Design Exercise: Arduino ADC/DAC
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin, 
 and also maps to a range from -5 to 5 V and displays the result
 on the LCD shield in binary.
 
 
 The circuit:
 * 
 
 created 5 Sept. 2014
 by Karmyn McKnight
 
 
 */
 
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
 
 
 
 

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
float voltageScaled = 0.0;
float voltageAbsolute = 0.0;



void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue); 
  

  // map the output voltage to -5 to 5
  voltageScaled = map(outputValue, 0, 255, -5, 5);  


  // print + or - and return the absolute value
  voltageAbsolute = printPostiveNegative(voltageScaled);
  
  // print binary representation of integer portion of
  //    voltage value (i.e. the part before the decimal point)
  // return the remaining part after the decimal point
  voltageDecimal = printVoltageBeforeDecimal(voltageAbsolute);
  
  
  // print binary representation of the portion of the voltage
  //    value after the decimal point
  decimalToBinary(voltageDecimal);





/*


convert decimal to binary, print 

*/



  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}



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



