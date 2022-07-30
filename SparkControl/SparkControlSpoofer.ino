// USES SPARK BOX TO EMULATE A SPARK CONTROL
// Library dependenct: NimBLE 1.3.8
// Edit NimBLEDevice.cpp
// Probably here: C:\Users\XXXXX\Documents\Arduino\libraries\NimBLE-Arduino\src\NimBLEDevice.cpp

/*
  #ifdef SPARK_CONTROL
  uint8_t                     NimBLEDevice::m_own_addr_type = BLE_OWN_ADDR_RANDOM;
  #else
  uint8_t                     NimBLEDevice::m_own_addr_type = BLE_OWN_ADDR_PUBLIC;
  #endif
*/

// Set this if you have switches attached to your GPIOS
#define USE_GPIOS

// this triggers the changes in NimBLEDevice.spp
#define SPARK_CONTROL

// ACTIVE_HIGH define should be set if your pedal sets GPIOs to +ve when switch pressed 
//    uint8_t SCswitchPins[]{33,27,14,26}; 
// for your GPIO setup
// note SCswitchPins is in a strange order - [0][2][1][3]
//#define ACTIVE_HIGH

// Set your board type- if nothing set then generic ESP32 is assumed
//#define HELTEC
//#define M5CORE
//#define M5CORE2
//#define M5STICK
//#define oled

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306



//#ifdef oled
//#include <Wire.h>
//#include "SSD1306Wire.h"
//#endif

//#ifdef HELTEC
//#include "heltec.h"
//#endif
//
//#ifdef M5CORE2
//#include <M5Core2.h>
//#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void SparkControlStart();
void InitialiseGPIO();
void SparkControlLoop();
bool spark_box;


void setup() {
// general setup
  Wire.begin(0,4);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // text display tests
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(31,0);             // Start at top-left corner
  display.println(F("LOLIN"));
  display.setCursor(12,25); 
  display.print("Spark");
  display.setCursor(12,40); 
  display.print("Control");   
  display.display();


  Serial.begin(115200); 
  spark_box = false;
  InitialiseGPIO();
  if (spark_box) {
  }
  else {
    SparkControlStart();
  }
}

void loop() {
  if (spark_box) {
  }
  else { 
    SparkControlLoop();
  }
}
