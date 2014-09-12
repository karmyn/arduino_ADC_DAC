/*
 BME 464 Arduino Project
 
 Lab Design Exercise: Arduino ADC/DAC
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin, 
 and also maps to a range from -5 to 5 V and displays the result
 on the LCD shield in binary.
 
 created 5 Sept. 2014
 by Karmyn McKnight & Megan Lu
*/
 
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 
 
// CONSTANTS 
int inpin = A0;  // Analog input pin (from power supply or func gen)
int outpin = 3; // Analog output pin (to o-scope or multimeter)
float analogin = 3; // analog input (0-1023)
int int_input = 0; // integer part of input
float dec_input = 0; // decimal part of input
float actual_voltage = 0; // actual input voltage
unsigned long time;
unsigned long oldTime;
unsigned long delayLCD;

// INITIAL SETUP
void setup() {
  
  pinMode(inpin, INPUT);  // set input pin to input pinmode
  pinMode(outpin, OUTPUT);  // sest output pin to output pinmode
  
  time = millis();   // record current time
  oldTime = millis();  // record current time
  
  lcd.begin(16,2);     // initialize LCD
  lcd.setBacklight(WHITE);   // set backlight to white
 
  Serial.begin(9600); // initialize serial communication at 9600 bps

}


// REPEATING LOOP
void loop() {
  
  time = millis();  // record current time 
  
  // read the analog in value:
  analogin = analogRead(inpin);  // input of 0 to 1023    
  
  // map analog input to the range of the analog out:
  actual_voltage = (analogin*10)/1023-5; // range of -5 to 5
  
  // Separate into integer and decimal components
  int_input = abs(actual_voltage); // floor of value
  dec_input = abs(actual_voltage) - int_input;  // decimal value (<1)
  
  if ((time-oldTime)>=1000) {   // update LCD only once a second
    Serial.println("print");
    print_LCD(); // update LCD
    oldTime=time; // update oldTime to reflect new time
  }
  
  // scale input for output
  float scaled_output = ((analogin + 1)/4) - 1; // range of 0 to 255
  
  // output 0-5 V corresponding to input
  analogWrite(outpin, scaled_output);
  delay(1);
                 
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
  else if(int_input == 1){
    lcd.print("001."); 
  }
  else if(int_input == 2){
    lcd.print("010."); 
  }
  else if(int_input == 3){
    lcd.print("011."); 
  }
  else if(int_input == 4){
    lcd.print("100."); 
  }
  else if(int_input == 5){
    lcd.print("101."); 
  }
  
  // Print decimal
  int n = 12;  // allow space for 12 digits for decimal
  
  while(n>0) {
    // use trick for multiplication by 2 for decimals
    dec_input = dec_input*2;
    
    if (dec_input < 1) {
      lcd.print("0");
    }
    else {
      lcd.print("1");
      dec_input = dec_input - 1;
    }
    
    n = n-1;
  }
    
}

