/*Wearable Sensor: Kanita Sivananthan, Lily Wang
Description: 

Website for GSR Sensor: https://wiki.seeedstudio.com/Grove-GSR_Sensor/ 
Website for LED Ring: https://create.arduino.cc/projecthub/aka3d6/heart-rate-monitor-wearable-and-wireless-using-ecg-e96dce?ref=platform&ref_id=424_trending___&offset=8
*/

/*
Pins --> REMINDER TO CHANGE IN THE CODE 
*/

#include <Adafruit_NeoPixel.h>

// Arduino PIN connected to the NeoPixels
#define PIN 5

// NeoPixels are attached to Arduino
#define NUMPIXELS 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//Define Variables
const int GSR=A0;                // Value of A0 pin
int sensorValue=0;               // Reset sensor value
int gsr_average=0;               // Reset average
long last_pix_upd = 0;           // Reset miliseconds since last pixel update

//Setup
void setup() {
  Serial.begin(9600);            // Opens serial port, sets data rate to 9600 bits per second (bps) 
  
  pixels.begin();                // Initializes the NeoPixel library
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(1,1,1));
  }
  pixels.show();
}

//Main Code
void loop() {
  
  //GSR Sensor Code
  long sum = 0;             
  for(int i=0; i<10; i++)           // Average the 10 measurements to remove the glitch
    {
    sensorValue = analogRead(GSR);  // Reads value of Sensor
    sum += sensorValue;             // Adds the value to the sensor
    delay(5);                       // Delay 5/1000 of a second
    }
    
  gsr_average = sum/10;             // Average of GSR readings
  Serial.println(gsr_average);      // Print average

  //NeoPixel LED Code
  long ms = millis();               // Milliseconds passed since Arduino board began running
  if(ms - last_pix_upd > 10)        // Update NeoPixel every # millesecons
  {
    last_pix_upd = ms;              // Keep track of updates
    
    //LED Variables
    int r, g, b;                    // RGB Values
    int max_bright = 160;           // Define Max brightness (@255 - excessive)

    //Risk Variables- research when LED should turn on
    const HIGH = 300;               // High Risk
    const MEDIUM = 200;             // Medium Risk
    const LOW = 100;                // Low Risk
    const NONE = 50;                // LED remains off

    // Color assignments based on Risk (HIGH, MEDIUM, LOW)
    if (gsr_average >= HIGH){
      r = maxbright; 
      g = max_bright; 
      b = max_bright;
    } else if (gsr_average >= MEDIUM){
      r = maxbright;
      g = 0;
      b = 0;
    } else if (gsr_average >= LOW){
      r = 0;
      g = maxbright;
      b = 0;
    } else {
      r = 0;
      g = 0;
      b = 0;
    }

    // Turn on pixels
    for(int i=0;  i<NUMPIXELS;  i++)
    {
      if(i < on_pixels){
          pixels.setPixelColor(NUMPIXELS-i-1, pixels.Color(r,g,b))
      } 
      else {
          pixels.setPixelColor(NUMPIXELS-i-1, pixels.Color(0,0,0));   //Turn off all other LEDs
      }
      
    }
    
    pixels.show(); 
  }


  //Human Resistance = (1024+2Serial_Port_Reading)10000/(512-Serial_Port_Reading), unit is ohm, Serial_Port_Reading is the value display on Serial Port(between 0~1023)

}