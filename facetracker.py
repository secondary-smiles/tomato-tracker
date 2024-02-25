import cv2
import serial
from time import sleep

ser = serial.Serial(port='/dev/cu.usbmodem1201', baudrate=9600, timeout=3)
sleep(3)

# Load the cascade
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# To capture video from webcam. 
cap = cv2.VideoCapture(1)
# To use a video file as input 
# cap = cv2.VideoCapture('filename.mp4')

while True:
    # Read the frame
    _, img = cap.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw the rectangle around each face
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        nx = int((min(x, 1000) / 1000) * 100)
        ny = 100 - int((min(y, 500) / 500) * 100)

        #ser.write(f"{int(nx)}:{int(ny)}?".encode())
        print(f"{nx}:{ny}?")
        ser.write(f"{nx}:{ny}?".encode())

        # sleep(1)
        bytes = ser.read(1)
        print(bytes)
        break
    # Display
    cv2.imshow('img', img)
    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break
# Release the VideoCapture object
cap.release()
