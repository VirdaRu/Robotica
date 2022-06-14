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
                    # start while loop to loop through frames

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
                    # cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                    #                         cv2.CHAIN_APPROX_SIMPLE)
                    # cnts = imutils.grab_contours(cnts)

                    cnts, _ = cv2.findContours(
                        mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

                    # go through all the contours
                    for cnt in cnts:
                        # filter out too small and too big contours by using the area
                        area = cv2.contourArea(cnt)

                        if (area > 4000) & (area < 20000):
                            # draw contours
                            cv2.drawContours(
                                frame, [cnt], 0, (0, 255, 255), 3)
                            # get center of contour
                            M = cv2.moments(cnt)
                            cx = int(M['m10']/M['m00'])
                            cy = int(M['m01']/M['m00'])
                            # draw centroid
                            cv2.circle(frame, (cx, cy), 3,
                                       (0, 255, 255), 5)
                            # determine if centroid is at left or right part of the frame
                            if cx > (width/2):
                                arduino.write("right".encode())
                                # turn right
                                print("go right")
                            elif cx < (width/2):
                                # turn left
                                arduino.write("left".encode())
                                print("go left")

            except KeyboardInterrupt:
                cap.release()
                print("KeyboardInterrupt has been caught.")
