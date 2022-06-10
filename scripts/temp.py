import serial
ser = serial.Serial('/dev/rfcomm0', timeout=1, baudrate=38400)
serial.reset_input_buffer()
serial.reset_output_buffer()

while True:
    out = serial.readline().decode()
    if out!='' : print (out)
