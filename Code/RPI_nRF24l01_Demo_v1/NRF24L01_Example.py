import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev


GPIO.setmode(GPIO.BCM)

Arduino1 = [0xe7, 0xe7, 0xe7, 0xe7, 0xe7]
Arduino2 = [0xe7, 0xe7, 0xe7, 0xe7, 0xc1]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

#radio.printDetails()

radio.powerUp()

radio.setChannel(110)
radio.setDataRate(NRF24.BR_250KBPS)
radio.setPALevel(NRF24.PA_MAX)

radio.setPayloadSize(32)

radio.setAutoAck(True)
radio.enableDynamicPayloads()

#radio.openWritingPipe(Arduino1)

radio.openReadingPipe(0, Arduino1)
radio.openReadingPipe(1, Arduino2)


radio.printDetails()
print("---------------------------")


radio.startListening()

while(1):

    # executes when payload available

    if(radio.available()):
        # Reading the payload
        rx_buff = []
        lenght = 0
        lenght = radio.getDynamicPayloadSize()
        radio.read(rx_buff, lenght)
        # Converting to string
        string = ""
        for n in rx_buff:
            string += chr(n)
        # Printing to screen
        print("Got: {}".format(string))
        print("Lenght: {}".format(lenght))

        
#    else:
#        tx_string = ""
#        tx_string  = raw_input()

#        radio.stopListening()
#        radio.write(tx_string)
#        radio.startListening()
    
