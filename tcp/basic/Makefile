.PHONY: app
app: client server

.PHONY: client
client: TCPEchoClient.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClient.c DieWithError.c -o ./bin/client

.PHONY: server
server: TCPEchoServer.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer.c DieWithError.c HandleTCPClient.c -o ./bin/server
