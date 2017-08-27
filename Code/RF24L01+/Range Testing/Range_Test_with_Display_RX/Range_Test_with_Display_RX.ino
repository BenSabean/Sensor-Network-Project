/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/
#include <SPI.h>
#include "RF24.h"
/****************** User Config ***************************/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins CE and CS respectively */
RF24 radio(2,3);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

char message [32];

void setup() 
{
  radio.begin();
  
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);

  // Setting lower data rate
  radio.setDataRate(RF24_250KBPS);

  // Setting retries param1 = 250us*param1 , param2 = count
  radio.setRetries(15, 15);

  // Setting COM channel 0-125
  radio.setChannel(110);

  // Calculate message lenght dynamically
  radio.enableDynamicPayloads();
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);

  radio.startListening();
}

void loop() 
{
  // Sending the data
  if (radio.available())
      radio.read(&message, radio.getDynamicPayloadSize());
  
} // Loop
