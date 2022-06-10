import pyfirmata
import sys
import time
from hx711 import HX711

Calibration_Factor = -1098580.0
#Using SparkFun_HX711_Calibration Sketch

DataPin =4 
SckPin =5

hx711 = HX711(dout_pin = DataPin,
		pd_sck_pin = SckPin,
		channel='A',
		gain=64)

hx711.reset()


#scale = HX711(DataPin,SckPin)
#HX711 = scale
#scale.set_reading_format("MSB", "MSB")
#scale.set_reference_unit(Calibration_Factor)
#scale.begin(DataPin, SckPin)
#scale.set_scale(Calibration_Factor)
#scale.reset()
#scale.tare() # Scale to 0

board = pyfirmata.Arduino("/dev/ttyACM0")


while True:
	time.sleep(2)
	print("Reading")
	print(hx711.get_raw_data())
	print(" kg")
	print(" ")
