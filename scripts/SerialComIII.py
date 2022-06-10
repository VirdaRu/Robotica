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
import cv2
import numpy as np


#HOST = "141.252.29.73"
HOST = "25.66.57.255"
PORT = 11000

WeightSensor = "null"

def Vision():

    # capture video from source 0
    cap = cv2.VideoCapture(0)

    # read first frame to get frame info such as height and width
    _, frame = cap.read()

    height = frame.shape[0]
    width = frame.shape[1]

    # start while loop to loop through frames
    while(1):
       # get new frame at the start of every loop
       _, frame = cap.read()
       # blur image
       blur = cv2.GaussianBlur(frame, (11, 11), 0)
       # Converts images from BGR to HSV
       hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
       # lower and upper bounds for masking blue (might need tweaking to make more accurate)
       lower_blue = np.array([100, 50, 50])
       upper_blue = np.array([120, 255, 255])

       # only get colors inbetween the upper and lower
       mask = cv2.inRange(hsv, lower_blue, upper_blue)
       # erode and dilate to remove whitenoise
       mask = cv2.erode(mask, None, iterations=2)
       mask = cv2.dilate(mask, None, iterations=2)
       # get the contours of the image
       cnts, _ = cv2.findContours(
       mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

       # go through all the contours
       for cnt in cnts:
         # filter out too small and too big contours by using the area
         area = cv2.contourArea(cnt)

         if (area > 4000) & (area < 30000):
            # draw contours
            cv2.drawContours(frame, [cnt], 0, (0, 255, 255), 3)
            # get center of contour
            M = cv2.moments(cnt)
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            # draw centroid
            cv2.circle(frame, (cx, cy), 3, (0, 255, 255), 5)
            # determine if centroid is at left or right part of the frame
            if cx > (width/2 + 80):
                # turn right
                print("go right")
            elif cx < (width/2 - 80):
                # turn left
                print("go left")
            else:
                print("Hold Position")
       cv2.line(frame, (400, 0), (400,480),(0,0,0), thickness= 3)
       cv2.line(frame, (240, 0), (240, 480), (0,0,0), thickness =3)
    
       # show the binary image and the camera frame
       cv2.imshow('Binary', mask)
       cv2.imshow('Frame', frame)

       # exit windows with esc
       k = cv2.waitKey(5) & 0xFF
       if k == 27:
           break

    # Destroys all of the windows.
    cv2.destroyAllWindows()

    # release the captured frame
    cap.release()

def SendMSG(message):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
             s.connect((HOST,PORT))
             s.sendall(bytes(message, encoding='utf-8'))
             s.sendall(b",<EOF>")
             #data = s.recv(1024)


if __name__ == '__main__':

    print('Running. Press CTRL-C to exit.')
#define port on pi, baut rate, set a timeout of 1 second
    with serial.Serial("/dev/ttyACM0", 38400, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    cmd=input("Enter command : ")
                    arduino.write(cmd.encode())
                    #time.sleep(0.1) #wait for arduino to answer
                    while arduino.inWaiting()==0: pass

                    if  arduino.inWaiting()>0:
                        answer=arduino.readline().decode('utf-8').rstrip()

                        if cmd == "vision":
                              SendMSG(answer)

                        if cmd == "weight":
                              SendMSG(answer)

                        if cmd == "distance":
                              SendMSG(answer)

                        print(answer)
                        arduino.flushInput() #remove data after reading

            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")

