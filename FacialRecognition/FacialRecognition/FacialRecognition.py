import cv2
import speech_recognition as sr
import pyttsx3
import pyaudio # Soundcard audio I/O access library
import wave # Python 3 module for reading / writing simple .wav files
import random
import time

MSGLimit = 0
# Load the cascade
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

def FaceRecognition():
    # To capture video from webcam. 
    cap = cv2.VideoCapture(0)
    # To use a video file as input 

    while True:
        # Read the frame
        _, img = cap.read()
        # Convert to grayscale
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # Detect the faces
        faces = face_cascade.detectMultiScale(gray, 1.1, 4)
        # Draw the rectangle around each face
        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
    
        if len(faces) > 0:
            if MSGLimit == 0:
                print("Hello! How is your day buddy?")
                # Handle interaction
                res = SpeechRecognition()
                MessageHandler(res)

                MSGLimit += 1
        else:
            MSGLimit = 0

        # Display
        cv2.imshow('Facial Recognizer', img)
        # Stop if escape key is pressed
        k = cv2.waitKey(30) & 0xff
        if k==27:
            break
    # Release the VideoCapture object
    cap.release()

def SpeechRecognition():

    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Speak Anything :")
        audio = r.listen(source)
        try:
            response = r.recognize_google(audio)
            print("You said : {}".format(response))
            return response
        except:
            print("Sorry i could not recognize what you said")
            SpeechRecognition()

def MessageHandler(response):
    if "good" in response:
        print("Good to Hear Mate!")
    elif "bad" in response:
        print("Im sorry you feel that way. Let me cheer you up!")
    else:
        print("Again please?")

def PlayGame():
    RPS = ["rock", "paper", "scissor"]
    print("Let's play Rock Paper Scissors, shall we?")
    response = SpeechRecognition()
    if response == None:
        PlayGame()
    else:
        if "yes" in response:
            print("Cool! Let's begin")
            print("Rock")
            time.sleep(0.5)
            print("Paper")
            time.sleep(0.5)
            print("Scissor")
            time.sleep(0.5)
            print("shoot")
            Answer = random.randint(0,2)

            print("Answer?")
            PlayerAnswer = SpeechRecognition()
            PlayerAnswer = PlayerAnswer.lower()
            print("i put:" + RPS[Answer])

            if PlayerAnswer == RPS[Answer] or (PlayerAnswer == "sza" and RPS[Answer] == "scissor"):
                print("A Draw")
            elif PlayerAnswer == "rock":
                if RPS[Answer] == "paper":
                    print("You lost!!")
                else:
                    print("Alright you win. congratulations!")
            elif PlayerAnswer == "paper":
                if RPS[Answer] == "scissor":
                    print("You lost!!")
                else:
                    print("Alright you win. congratulations!")
            elif PlayerAnswer == "scissor" or PlayerAnswer == "sza":
                if RPS[Answer] == "rock":
                    print("You lost!!")
                else:
                    print("Alright you win. congratulations!")

        else:
            print("Very Well")

PlayGame()
#FaceRecognition()