import serial
if __name__ == '__main__':
    ser = serial.Serial('/dev/rfcomm0', 38400, timeout=1)
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
