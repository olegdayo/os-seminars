.PHONY: app
app: client server

.PHONY: client
client: TCPEchoClientLoop.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoClientLoop.c DieWithError.c -o ./bin/client

.PHONY: server
server: TCPEchoServer.c DieWithError.c
	mkdir bin || true
	gcc TCPEchoServer.c DieWithError.c HandleTCPClient.c -o ./bin/server
