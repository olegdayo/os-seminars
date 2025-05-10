all: UDPEchoClient UDPEchoServer-SIGIO

UDPEchoClient: UDPEchoClient.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc UDPEchoClient.c DieWithError.c -o bin/client

UDPEchoServer-SIGIO: UDPEchoServer-SIGIO.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc UDPEchoServer-SIGIO.c DieWithError.c -o bin/server
