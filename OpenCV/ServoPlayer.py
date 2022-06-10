import RPi.GPIO as GPIO
from gpiozero import AngularServo
from time import sleep
from gpiozero.pins.native import NativeFactory

my_factory = NativeFactory()

servo = AngularServo(17, min_pulse_width = 0.0006, max_pulse_width=0.00230)


