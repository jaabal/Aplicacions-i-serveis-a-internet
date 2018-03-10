import socket
import threading

bind_host = '192.168.2.5'
bind_port = 2000

# create an ipv4 (AF_INET) socket object using the tcp protocol (SOCK_STREAM)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#bind the socket class with IP and Port
server.bind((bind_ip, bind_port))

#ma backlog of connections
server.listen(5)

print 'Listening on {}:{}'.format(bind_ip,bind_port)

def handle_client_connection(client_socket):
	request = client_socket.recv(1024)
	print 'Received {}'.format(request)
	client_socket.send('Yes')
	client_socket.close()

while True:
	client_sock, address = server.accept()
	print 'Accepted connection from {}:{}'.format(address[0], address[1])
	client_handler = threading.Thread(
		target = handle_client_connection,
		args = (client_sock,)   	# without the comma it gets an error
	)
	client_handler.start()
