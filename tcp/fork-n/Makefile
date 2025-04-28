.PHONY: app
app: client server

.PHONY: client
client: TCPEchoClientLoop.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClientLoop.c DieWithError.c -o ./bin/client

.PHONY: server
server: TCPEchoServer-ForkN.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer.h TCPEchoServer-ForkN.c DieWithError.c \
	HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c \
	-o ./bin/server
