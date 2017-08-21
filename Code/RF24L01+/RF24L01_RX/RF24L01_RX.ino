/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/
#include <SPI.h>
#include "RF24.h"
#include <printf.h>
/****************** User Config ***************************/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins CE and CS respectively */
RF24 radio(2,3);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

void setup() 
{
  Serial.begin(115200);
  printf_begin();
  
  radio.begin();
  
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);


  // Setting lower data rate
  if(!radio.setDataRate(RF24_250KBPS))
    Serial.println("DataRate 250KB failed");

  // Setting retries param1 = 250us*param1 , param2 = count
  radio.setRetries(10, 15);

  // Setting COM channel 0-125
  radio.setChannel(110);

  // Calculate message lenght dynamically
  radio.enableDynamicPayloads();
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);

  // Printing debug details
  radio.printDetails();
  Serial.println("--------------------------------");
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() 
{
    String message;
    
    if(Serial.available())
    {
      message = Serial.readString();
      if(message.length() <= 32)
      {
        char buff[32];
        message.toCharArray(buff, message.length() + 1);
        
        Serial.println("Send: " + message);

        // Sending //
        radio.stopListening();                                  // First, stop listening so we can talk.
        // Sending the data
        if (!radio.write( &buff, message.length() + 1) )
            Serial.println("***FAILED***");
        radio.startListening();
        
      }
      else 
        Serial.println("***MESSAGE TOO LONG***");
    }

    if(radio.available())
    {
      char rx_buff[32]; // 32 is the max byte number
      uint8_t len = radio.getDynamicPayloadSize();
      radio.read(&rx_buff, len);
      Serial.println("Got: " + String(rx_buff));
    }
  
} // Loop
