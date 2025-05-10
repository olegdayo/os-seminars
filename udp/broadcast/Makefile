all: BroadcastReceiver BroadcastSender

BroadcastReceiver: BroadcastReceiver.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc BroadcastReceiver.c DieWithError.c -o bin/receiver

BroadcastSender: BroadcastSender.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc BroadcastSender.c DieWithError.c -o bin/sender
