from collections import *
from math import *
from serial import Serial
from serial.tools.list_ports import comports

import time

# this may be specific to fogel's computer or the arduino itself?
# https://www.voti.nl/docs/usb-pid.html
# To list ports robert used - python -m serial.tools.list_ports -v
# Also python -m serial.tools.list_ports

VID_PID = '2341:0043'
BAUD_RATE = 115200
TIMEOUT = 0.5

#defines the usb port that he will communicate with over serial
def find_port():
    for port in comports():
        if VID_PID in port[2]:
            return port[0]
    return None


# this is also very important...
class Device():
    def __init__(self): #linkage is probably screwing something up
        port = find_port()
        if port is None:
            raise Exception('cannot find device')
        self.serial = Serial(port, BAUD_RATE, timeout=TIMEOUT)
        # self.flush()
        self.pos = 0

# he made his own flush? why? the below just fills the serial buffer with zeroes... maybe
    # def flush(self):
        # for i in range(10):
            # self.move(0, 0, 0)

    def readline(self):
        return self.serial.readline().decode('utf-8').strip() # He doesn't care what it looks for but this function will lock up the program until it reads soemthing (probably not certain)

# called by move - step 3 THIS IS THE MOST IMPORTANT PART
    def send(self, cmd):
        print(cmd.strip()) # gets rid of spaces (which don't exist) but good practice
        self.serial.write(cmd.encode('utf-8')) # converts to something for serial with python AND SENDS AS WELL THIS IS THE SEND DAVE
        self.serial.flush() # clears buffer (library)
        print(self.readline()) # this is waiting for Drew's "OK" called above - doesn't do anything with this but print

# called by step_to - step 2
    def move(self, pos):
        cmd = 'STEP %d\n' % (pos) # cmd is a variable that's a string! It's what's sent over serial
        # cmd = 'JOG %f %f %d\n' % (da1, da2, ms) #this says make a float, a float, and a decimal, a linebreak and the stuff in parenthesis is what gets filled in 
        self.send(cmd)

# we aren't sure what this is...
# t += dt

# Robert wrote this to see if when you run this directly does serial com make it to the arduino which it does - implying that this code is fine
# if __name__ == '__main__':
#     dev = Device()
#     while True:
#         dev.send('test')
#         time.sleep(1)
