import socket
import serial
import time as t

HOST= "141.252.29.74"
PORT= 11000

WeightSensor = "empty"
DistanceSensor = ",null"

#Read Location
ser = serial.Serial('/dev/ttyACM0',9600, timeout =1)
ser.reset_input_buffer()

while True:
	t.sleep(1)
	if ser.in_waiting > 0:
		WeightSensor = ser.readline().decode('utf-8').rstrip()
			
		#Debugging		
		print(WeightSensor)
	
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect((HOST,PORT))
		s.sendall(bytes(WeightSensor, encoding='utf-8'))
		s.sendall(bytes(DistanceSensor, encoding='utf-8'))
		s.sendall(b",<EOF>")
		data = s.recv(1024)

print(f"recieved {data!r}")

