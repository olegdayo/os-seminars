.PHONY: app
app: client server

client: TCPEchoClientLoop.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClientLoop.c DieWithError.c -o ./bin/client

server: TCPEchoServer.h TCPEchoServer-Thread.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer-Thread.c DieWithError.c HandleTCPClient.c \
	CreateTCPServerSocket.c AcceptTCPConnection.c \
	-o ./bin/server -pthread
