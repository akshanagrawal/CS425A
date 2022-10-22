from socket import *
serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
clientSocket.connect((serverName, serverPort))
flg = True
while flg:
	sentence = input('Client: ')
	clientSocket.send(sentence.encode())
	reply = clientSocket.recv(1024).decode()
	print ('Server:', reply)
	if(sentence == 'exit'):
		flg = False
clientSocket.close()