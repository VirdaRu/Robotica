#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device n                            arduino.flus

#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
# dmesg | grep "tty" to find port name

import serial
import time
import cv2
import numpy as np

# capture video from source 0

cap = cv2.VideoCapture(0)

# read first frame to get frame info such as height and width
_, frame = cap.read()

height = frame.shape[0]
width = frame.shape[1]

if __name__ == '__main__':

    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 56700, timeout=1) as arduino:
        time.sleep(0.1)  # wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    _, frame = cap.read()
                    # blur image
                    blur = cv2.GaussianBlur(frame, (11, 11), 0)
                    # Converts images from BGR to HSV
                    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
                    # lower and upper bounds for masking blue (might need tweaking to make more accurate)
                    # if is does not work reset s and v value back to 50
                    lower_blue = np.array([100, 75, 75])
                    upper_blue = np.array([120, 255, 255])

                    # only get colors inbetween the upper and lower
                    mask = cv2.inRange(hsv, lower_blue, upper_blue)
                    # erode and dilate to remove whitenoise
                    mask = cv2.erode(mask, None, iterations=2)
                    mask = cv2.dilate(mask, None, iterations=2)

                    cnts, _ = cv2.findContours(
                        mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

                    area = cv2.contourArea
                    # go through all the contours

                    # filter out too small and too big contours by using the area
                    if len(cnts) > 0:

                        c = max(cnts, key=cv2.contourArea)
                        x, y, w, h = cv2.boundingRect(c)

                        if cv2.contourArea(c) > 500:

                            # draw contours
                            cv2.drawContours(frame, c, -1, (0, 255, 255), 3)

                            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

                            # get center of contour
                            M = cv2.moments(c)
                            cx = int(M['m10']/M['m00'])
                            cy = int(M['m01']/M['m00'])
                            # draw centroid
                            cv2.circle(frame, (cx, cy), 3, (0, 255, 255), 5)
                            # determine if centroid is at left or right part of the frame
                            if cx < (width/2 + 100) and cx > (width/2 - 100):
                                arduino.write("stop".encode())
                                print("Stay center")
                            elif cx > (width/2):
                                # turn right
                                arduino.write("right".encode())
                                print("go right")
                            elif cx < (width/2):
                                # turn left
                                arduino.write("left".encode())
                                print("go left")     

            except KeyboardInterrupt:
                 cap.release()
                 print("KeyboardInterrupt has been caught.")
