cc = gcc
all: server node hacker
.PHONY: clean

node: node.c messageTools.h semaphoreTools.h sharedMemoryTools.h basicTools.h
	$(cc) -o node node.c

server: print_server.c messageTools.h basicTools.h
	$(cc) -o server print_server.c

hacker: hacker.c messageTools.h basicTools.h
	$(cc) -o hacker hacker.c

clean:
	rm node
	rm server
	rm hacker