import socket

HOST = "192.168.56.1"  # The server's hostname or IP address
PORT = 11000  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b"0.963 kg,")
    s.sendall(b"420 RPM,")
    s.sendall(b"<EOF>")
    data = s.recv(1024)

print(f"Received {data!r}")
