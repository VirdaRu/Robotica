import cv2 
import numpy

myframe =cv2.imread('BeautifulTraffic.jpg')

myframe =cv2.resize(myframe, (800,600))
grey = cv2.cvtColor(myframe, cv2.COLOR_BGR2GRAY)

cv2.imshow('frame', grey)

k = cv2.waitKey(0)
cv2.destroyAllWindows()
