cc = gcc
all: server node hacker
.PHONY: clean

server: print_server.c messageTools.h semaphoreTools.h basicTools.h sharedMemoryTools.h
	$(cc) -o server print_server.c

node: node.c messageTools.h semaphoreTools.h basicTools.h sharedMemoryTools.h
	$(cc) -o node node.c

hacker: hacker.c messageTools.h semaphoreTools.h basicTools.h sharedMemoryTools.h
	$(cc) -o hacker hacker.c

clean: 
	rm server 
	rm node
	rm hacker 