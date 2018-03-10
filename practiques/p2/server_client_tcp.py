# -*- coding: utf-8 -*-

##################################
# TCP/IP python server/client code
##################################

import socket, sys, select, struct, signal

# Arguments passed by command in order to diff a server from a client

if(sys.argv[1])=='-s')
	host = sys.argv[2]
	port = sys.argv[3]

elif(sys.argv[1])=='-c')
	host = sys.argv[2]
	port = sys.argv[3]

else:
	print $python server_client_TCP.py -s [host] [port]
	print $python server_client_TCP.py -c [host] [port]


def Client_setup(port, host):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((host,port))

def Server_setup(port, host):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host,port))
	s.listen(5)		# maximum number of clients which are allow to be connected with the server


 
	
