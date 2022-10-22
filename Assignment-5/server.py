from socket import *
 
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
serverSocket.bind(("localhost", serverPort))
serverSocket.listen()
print ("Server Ready")
connectionSocket, addr = serverSocket.accept()
print("Connection from the address-", addr, "is estd.")
flg = True
while flg:
    sentence = connectionSocket.recv(1024).decode()
    print('Client:', sentence)
    reply = input('Server: ')
    connectionSocket.send(reply.encode())
    if(sentence == 'exit'):
        flg = False

connectionSocket.close()
serverSocket.close()