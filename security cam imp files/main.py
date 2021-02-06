import cv2
import pyautogui
import winsound
import requests
from cv2.cv2 import CascadeClassifier


def sound():
    winsound.PlaySound('alert.wav', winsound.SND_FILENAME)


def send():
    files = {'photo': open(r"C:\Users\srikar\Desktop\Test\img1.png", 'rb')}
    requests.post(
        'https://api.telegram.org/bot(xxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx)/sendphoto?chat_id=xxxxxxxxx',
        files=files)


def screenshot():
    my_screenshot = pyautogui.screenshot()
    my_screenshot.save(r'C:\Users\srikar\Desktop\Test\img1.png')


face_cascade: CascadeClassifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)

while True:
    # Read the frame
    _, img = cap.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 5)
    # Draw the rectangle around each face
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 255, 0), 2)

        screenshot()

        # sound()
        send()
    # Display
    cv2.imshow('cam', img)
    # Stop if escape key is pressed
    if cv2.waitKey(10) == ord('q'):
        break
# Release the VideoCapture object
cap.release()
