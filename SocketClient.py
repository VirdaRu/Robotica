import socket
import random

HOST = "192.168.56.1"  # The server's hostname or IP address
PORT = 11000  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    #weight = f"{0.963} kg,"
    weight = f"{random.randint(1, 5)} kg,"
    rpm = f"{random.randint(60, 420)} RPM,"

    s.sendall(bytes(weight, encoding='utf-8'))
    s.sendall(bytes(rpm, encoding='utf-8'))
    s.sendall(b"<EOF>")
    data = s.recv(1024)

print(f"Received {data!r}")
