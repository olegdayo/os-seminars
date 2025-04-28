.PHONY: app
app: client server

.PHONY: client
client: TCPEchoClientLoop.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClientLoop.c DieWithError.c -o ./bin/client

.PHONY: server
server: TCPEchoServer-Select.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer.h TCPEchoServer-Select.c DieWithError.c \
	HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c \
	-o ./bin/server
