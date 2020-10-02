##Dan Parr and Ruiqi Sun
##EENG 350 SEED Lab
##Mini Project
##Aruco Detection
##10/07/2020

"""
This script contains three functions. The function 'detect_marker' reads an
image and determines if there is an Aruco marker in the image. If there is
an Aruco marker present, the function returns the quadrant where the marker
is.
If no Aruco marker is found, return 0.
If Aruco is in NE quadrant (quadrant 1), return 1.
If Aruco is in NW quadrant (quadrant 2), return 2.
If Aruco is in SW quadrant (quadrant 3), return 3.
If Aruco is in SE quadrant (quadrant 4), return 4.
To show the image on screen for troubleshooting, uncomment the 3 lines of code
above the outer 'if' statement.

The function 'take_picture' sets the ISO (light sensitivity) and
auto-white-balance of the camera, and then takes a picture and saves the
image for future processing. If the image is too dark, increase ISO value.
The image is a jpg but can be changed to png if needed.

The function 'main' initiates an infinite loop, so that the camera
continuously takes a picture, detects the presence of an Aruco marker, and
returns the quadrant it is in.

To run this script, connect a camera to the Raspberry Pi and run the module.
"""

#Import the necessary packages:
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2 as cv
import numpy as np
import cv2.aruco as aruco
from fractions import Fraction

#Function to return the quadrant that the Aruco marker is in:
def detect_marker(image):
   img = cv.imread(image) #read image
   aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250) #dictionary of Aruco markers
   param = aruco.DetectorParameters_create() #default detection parameters
   grayImg = cv.cvtColor(img,cv.COLOR_BGR2GRAY) #grayspace makes detection easier
   #detect aruco markers:
   corners, ids, rejected = aruco.detectMarkers(grayImg,
                                     aruco_dict,parameters=param)

   imgCenterX = int((img.shape[1]))/2 #calculate horizontal center
   imgCenterY = int((img.shape[0]))/2 #calculate vertical center

##Uncomment the following 3 lines if you want an image on your screen to help
##with troubleshooting

##   cv.imshow('aruco',grayImg) #shows image on screen
##   cv.waitKey(5000) #waits 5 seconds
##   cv.destroyWindow('aruco') #destroys image window

   if ids == None: #No Aruco marker has been detected
      return 0
   else: #An Aruco marker has been detected
      centerX = (corners[0][0][0][0] + corners[0][0][1][0] + corners[0][0][2][0] + corners[0][0][3][0])/4
      centerY = (corners[0][0][0][1] + corners[0][0][1][1] + corners[0][0][2][1] + corners[0][0][3][1])/4
      if (centerX > imgCenterX) and (centerY <= imgCenterY):
         return 1
      if (centerX <= imgCenterX) and (centerY < imgCenterY):
         return 2
      if (centerX < imgCenterX) and (centerY >= imgCenterY):
         return 3
      if (centerX >= imgCenterX) and (centerY > imgCenterY):
         return 4

#The following code was adapted from https://picamera.readthedocs.io/en/release-1.10/api_array.html#pirgbarray
#Function to take a picture and feed image into detect_marker function:
def take_picture():
   with PiCamera() as camera:
      with PiRGBArray(camera) as output:
         camera.iso = 400 #100 to 200 are good for daylight. 400 to 800 good for indoors
         camera.awb_gains = (Fraction(11,8),Fraction(39,32)) #set auto-white-balance
         camera.capture(output, 'rgb') #capture a picture from camera in RGB colorspace
         img = output.array #convert to NumPy array
         img = cv.cvtColor(img,cv.COLOR_RGB2BGR) #convert to BGR colorspace
         cv.imwrite('detect.jpg',img) #write image to file
         quadrant = detect_marker('detect.jpg') #feed image into detect_marker function
   return quadrant

#Main function to continuously take pictures and detect Aruco markers:
def main():
   while(1): #infinite loop
      quadrant = take_picture() #capture image and determine quadrant of Aruco marker
      print(quadrant)
      time.sleep(2) #adjust this to fit within time constraints of problem

main()






