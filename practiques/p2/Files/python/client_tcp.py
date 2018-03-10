import socket, select, sys, signal, struct

HOST='127.0.0.1'
PORT=5000

socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try: 
	socket_client.connect((HOST, PORT))
else:
	print "Host unreachable"
	sys.exit()

print "Client connected to the server"
while True:
	read_socket, _,_ = select.select([sys.stdin, socket_client],[],[])
	if read_socket[0] == socket_client[0]:
		data = socket.recv(1024)
		print "data = ",str(data)
	if not data:
		print "Disconnected from server"
		sys.exit(1)
		sys.stdout.write(data)

	else:
		msg = sys.stdin.readline()
		socket_client.send(msg)
