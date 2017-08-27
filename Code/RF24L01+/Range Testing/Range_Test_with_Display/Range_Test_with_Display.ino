#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <SPI.h>
#include "RF24.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins CE and CS respectively */
RF24 radio(2,3);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

char message [] = "test";
unsigned int count = 0;
unsigned long start;

void setup() 
{
  // Setting up the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(500);
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  radio.begin();
  
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);

  // Setting lower data rate
  if(!radio.setDataRate(RF24_250KBPS))
    display.println("DataRate 250KB failed");

  // Setting retries param1 = 250us*param1 , param2 = count
  radio.setRetries(15, 15);

  // Setting COM channel 0-125
  radio.setChannel(110);

  // Calculate message lenght dynamically
  radio.enableDynamicPayloads();
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);

  radio.stopListening(); 
}

void loop() 
{
  display.clearDisplay();

  // Time
  display.setCursor(0, 0);
  display.println("RANGE TEST");
  
  count = 0;
  
  start = millis();
  while(millis() - start <= 1000)
  {
    // Sending the data
    if (radio.write( &message, sizeof(message)))
        count ++;
  }
  
  // Packets Per Second
  display.print("PPS: ");
  display.println(count);
  Serial.println(count);
 
  display.display();

  //delay(10);
}
