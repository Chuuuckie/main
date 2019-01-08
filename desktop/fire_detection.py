import time

import cv2
import numpy as np
from imutils.video import VideoStream
import imutils


accumulated_exposures = None
seconds_per_frame = 1.0
# Are we using the Pi Camera?
usingPiCamera = False

if usingPiCamera:
    frameSize = (320, 240) # Set initial frame size.
    video = VideoStream(src=0, usePiCamera=usingPiCamera, resolution=frameSize,
		framerate=32).start() # Initialize mutithreading the video stream.
    time.sleep(2.0) # Allow the camera to warm up.
    timeCheck = time.time()
else:     
    video = cv2.VideoCapture(0) #Get the USB Camera Device Com Port
 
while True:    
    if not usingPiCamera:
        (grabbed, frame) = video.read()
        if not grabbed:
            break
    else:
        frame = video.read()
     
    #if the heatmap is None we create it with same size as frame, single channel
    if type(accumulated_exposures) == type(None):
        accumulated_exposures = np.zeros((frame.shape[0], frame.shape[1]), dtype=np.float)
    #print("exposure:".format(accumulated_exposures))       
    maskimg = np.zeros(accumulated_exposures.shape, dtype=np.float) 
 
    #accumulate the heatmap object exposure time
    accumulated_exposuresmask = accumulated_exposures + maskimg    

#Start old code
    blur = cv2.GaussianBlur(frame, (21, 21), 0)
    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
 
    lower = [18, 50, 50]
    upper = [35, 255, 255]
    lower = np.array(lower, dtype="uint8")
    upper = np.array(upper, dtype="uint8")
    mask = cv2.inRange(hsv, lower, upper)
     
    output = cv2.bitwise_and(frame, hsv, mask=mask)
    no_red = cv2.countNonZero(mask)
    cv2.imshow("output", output)
    #print("output:", frame)
    if int(no_red) > 100000:
        print ('Fire detected')
        print (no_red)
    #else:
    #   print(int(no_red))
   #print("output:".format(mask))
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
cv2.destroyAllWindows()
if not usingPiCamera:
    video.release()
