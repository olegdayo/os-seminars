all: SigAction
SigAction: SigAction.c DieWithError.c
	mkdir bin 2> /dev/null || true
	gcc SigAction.c DieWithError.c -o bin/sigaction
