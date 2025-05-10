all: UDPEchoClient-Timeout UDPEchoServer

UDPEchoClient-Timeout: UDPEchoClient-Timeout.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc UDPEchoClient-Timeout.c DieWithError.c -o bin/client

UDPEchoServer: UDPEchoServer.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc UDPEchoServer.c DieWithError.c -o bin/server
