import cv2
import numpy
import serial
from time import sleep

ser = serial.Serial(port='/dev/cu.usbmodem1101', baudrate=9600, timeout=3)
sleep(3)

lower_red = numpy.array([134, 83, 39])
upper_red = numpy.array([137, 94, 75])

cap = cv2.VideoCapture(1)

while(1):
    _, frame = cap.read()
    cv2.flip(frame, flipCode=0)
    frame = cv2.GaussianBlur(frame, (5, 5), 0)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_red, upper_red) 
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if contours:
        largest_contour = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest_contour)

        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        #x = x + w / 2
        #y = y + h / 2

        nx = int((min(x, 1000) / 1000) * 100)
        ny = 100 - int((min(y, 700) / 700) * 100)

        #ser.write(f"{int(nx)}:{int(ny)}?".encode())
        print(f"{nx}:{ny}?")
        ser.write(f"{nx}:{ny}?".encode())

        # sleep(1)
        bytes = ser.read(1)
        print(bytes)

    res = cv2.bitwise_and(frame,frame, mask= mask) 
    cv2.imshow('frame',frame) 
    cv2.imshow('mask',mask) 
    cv2.imshow('res',res) 
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
cv2.destroyAllWindows() 
  
cap.release() 
