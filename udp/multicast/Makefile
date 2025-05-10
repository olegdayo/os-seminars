all: MulticastReceiver MulticastSender

MulticastReceiver: MulticastReceiver.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc MulticastReceiver.c DieWithError.c -o bin/receiver

MulticastSender: MulticastSender.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc MulticastSender.c DieWithError.c -o bin/sender
