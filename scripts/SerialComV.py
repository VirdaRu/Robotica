#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device n                            arduino.flus

#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial
import time
import socket
import numpy as np


#OldHOST = "141.252.29.73"

#Constants
HOST = "25.66.57.255"
PORT = 11000

WeightSensor = "null"
sub = "JS1"
BSWstr = "BSW"
LSWstr = "LSW"

JS1 = []
BSW = []
LSW = []

Controller = serial.Serial("/dev/rfcomm0", 38400, timeout=1)
Deadzone = 130

#Sends a message using a TCP Socket (to Website)
def SendMSG(message):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((HOST,PORT))
         s.sendall(bytes(message, encoding='utf-8'))
         s.sendall(b",<EOF>")

def GetSpeed(position):
    return abs(int(position)/2 - 1)

if __name__ == '__main__':

    print('Running. Press CTRL-C to exit.')
    #define port on pi, baut rate, set a timeout of 1 second
    with serial.Serial("/dev/ttyACM0", 38400, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    ControllerInput = Controller.readline().decode('utf-8').rstrip()
                    print(ControllerInput)
                    if sub in ControllerInput:
                          JS1 = ControllerInput.split(":")
                          JS1.pop(0)
                          if int(JS1[1]) > Deadzone:
                                print("forward")
                                #Case there is an issue use a variable
                              #  mSpeed = GetSpeed(JS1[1])
                               # arduino.write("forward:{}".format(mSpeed).encode())
                                arduino.write("forward".encode())
                          elif int(JS1[1]) < -Deadzone:
                                arduino.write("reverse".encode())
                          if int(JS1[0]) > Deadzone:
                                arduino.write("right".encode())
                          elif int(JS1[0]) < -Deadzone:
                                arduino.write("left".encode())
                          if int(JS1[2]) == 0:
                                print("Easter Egg lmao")
                          else:
                                arduino.write("stop".encode())

                    #ButtonHandler
                    if BSWstr in ControllerInput:
                          BSW = ControllerInput.split(":")
                          BSW.pop(0)
                          #loop through all buttons
                          for i in range(4):
                               print(BSW[i])
                               #If button is pressed (0)
                               if BSW[i] == "0":
                                    print("BSW{}".format(i))
                                    arduino.write("BSW{}".format(i).encode())
                                    
                   if LSWstr in ControllerInput:
                          LSW = ControllerInput.split(":")
                          LSW.pop(0)
                          for i in range(4):
                               print(LSW[i])
                               if LSW[i] == "0":
                                    print("LSW{}".format(i))
                                    arduino.write("LSW{}".format(i).encode())

            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")
