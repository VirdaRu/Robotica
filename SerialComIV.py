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


#HOST = "141.252.29.73"
HOST = "25.66.57.255"
PORT = 11000

WeightSensor = "null"

def SendMSG(message):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
             s.connect((HOST,PORT))
             s.sendall(bytes(message, encoding='utf-8'))
             s.sendall(b",<EOF>")
             #data = s.recv(1024)
Controller = serial.Serial("/dev/rfcomm0", 38400, timeout=1)
sub = "JS1"
JS1 = []

Deadzone = 130

forward = "forward"

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
                                arduino.write(forward.encode())
                          elif int(JS1[1]) < -Deadzone:
                                arduino.write("reverse".encode())
                          else:
                                arduino.write("stop".encode())
                    #cmd=input("Enter command : ")
                    #arduino.write(cmd.encode())
                    #time.sleep(0.1) #wait for arduino to answer
                    #while arduino.inWaiting()==0: pass

                    #if  arduino.inWaiting()>0:
                    #    answer=arduino.readline().decode('utf-8').rstrip()
         
                    #    arduino.flushInput() #remove data after reading

            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")

