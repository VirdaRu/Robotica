import cv2
import numpy as np
import imutils

# read image, will be video/videocapture
frame = cv2.imread("Visual-tracking/images\Baan_top_view.jpg")
# resize img for better viewing, not needed in final product
frame = cv2.resize(frame, (783, 480))

height = frame.shape[0]
width = frame.shape[1]


# turn image to greyscale
grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# invert image to make black white
bitwise = cv2.bitwise_not(grey)
# erode and dilate image to reduce white noise
bitwise = cv2.erode(bitwise, None, iterations=4)
bitwise = cv2.dilate(bitwise, None, iterations=3)
# threshold the image to get binary img of black and white
th, thres = cv2.threshold(bitwise, 225, 255, cv2.THRESH_BINARY_INV)

# invert image again (pretty sure these inverts arent needed, but it works for now)
invert = cv2.bitwise_not(thres)

# find contours
cnts = cv2.findContours(invert, cv2.RETR_EXTERNAL,
                        cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)

# array to save centroids of the black contours
line = []

# go through contours
for cnt in cnts:
    area = cv2.contourArea(cnt)

    # draw the contour
    cv2.drawContours(frame, [cnt], 0, (0, 255, 255), 3)
    # get centroid of contour
    M = cv2.moments(cnt)
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])
    # add the centroid to the array of points
    line.append((cx, cy))
    # draw centroid
    cv2.circle(frame, (cx, cy), 3, (0, 255, 255), 5)

# draw a line through the centroids (should be a fitted line, currently it draws from 1st to last)
cv2.line(frame, line[0], line[-1], (0, 0, 255), thickness=3)
# draw midline of camera for reference
cv2.line(frame, (int(width/2), height),
         (int(width/2), 0), (0, 255, 0), thickness=2)


cv2.imshow('bitwise', invert)
cv2.imshow('Black_line', frame)


k = cv2.waitKey(0)
cv2.destroyAllWindows()
