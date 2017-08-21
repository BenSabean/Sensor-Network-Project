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
#define Arduino1 1
#define Arduino2 2
#define RPI 0

const uint64_t addresses[] = {0x123456789aLL, 0xe7e7e7e7e7LL, 0xe7e7e7e7c1LL};

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
  radio.openWritingPipe(addresses[Arduino2]);
  radio.openReadingPipe(0,addresses[Arduino2]);
  radio.openReadingPipe(1,addresses[RPI]);
  //radio.openReadingPipe(1,addresses[RPI]);


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
        if (!radio.write( &buff, message.length()) )
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
    /*
    Serial.println(F("Now sending"));
    unsigned long start_time = micros();                        // Take the time, and send it.  This will block until complete
     if (!radio.write( &start_time, sizeof(unsigned long) )){
       Serial.println(F("failed"));
     }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
        unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
        radio.read( &got_time, sizeof(unsigned long) );
        unsigned long end_time = micros();
        
        // Spew it
        Serial.print(F("Sent "));
        Serial.print(start_time);
        Serial.print(F(", Got response "));
        Serial.print(got_time);
        Serial.print(F(", Round-trip delay "));
        Serial.print(end_time-start_time);
        Serial.println(F(" microseconds"));
    }
    // Try again 1s later
    delay(1000);
    */

