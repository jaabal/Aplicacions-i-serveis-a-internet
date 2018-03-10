import socket 

host = '192.168.2.5'
port = 2000

# create an IPv4 (AF_INET) socket object using the tcp protocol (SOCK_STREAM)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect the client
client.connect((host, port))

# send some data
client.send('Do you receive this message?')

# receive the ACK
response = client.recv(4096)

print response
