.PHONY: app
app: client server

.PHONY: client
client: TCPEchoClientLoop.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClientLoop.c DieWithError.c -o ./bin/client

.PHONY: server
server: TCPEchoServer.h TCPEchoServer-Fork.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer-Fork.c DieWithError.c HandleTCPClient.c \
	CreateTCPServerSocket.c AcceptTCPConnection.c \
	-o ./bin/server
