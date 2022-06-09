import serial
import time

#Constants
JS1 = []
JS2 = []

BSW = []
LSW = []

sub = "JS1"
bigButton = "BSW"
littleButton = "LSW"

Deadzone = 130

Controller =  serial.Serial("/dev/rfcomm0", 38400, timeout=1)

while True:
	myResult = Controller.readline().decode('utf-8').rstrip()
	if sub in myResult:
		JS1 = myResult.split(":")
		JS1.pop(0)
		print(JS1)
		#TEMPORARY FIX: X and Y are reversed, so in this case we use 1(y) instead of 0(x)
		if int(JS1[1]) > Deadzone:
			# stuur forwards
			print("forward")
		elif int(JS1[1]) < -Deadzone:
			# stuur reverse
			print("reverse")
		if int(JS1[0]) > Deadzone:
			print("right")
		elif int(JS1[0]) < -Deadzone:
			print("left")
		if int(JS1[2]) == 0:
			print("JoyStick 1 Pressed")
		#elif int(JS1[1] < 130)

	if bigButton in myResult:
		BSW = myResult.split(":")
		BSW.pop(0)
		print("BSW pressed")

	if littleButton in myResult:
		LSW = myResult.split(":")
		LSW.pop(0)
		print("LSW pressed")
