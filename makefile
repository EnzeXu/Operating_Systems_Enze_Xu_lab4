cc = gcc
all: server node hacker
.PHONY: clean

server: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o server print_server.c

node: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -pthread -o node node.c

hacker: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o hacker hacker.c

clean: 
	rm server 
	rm node
	rm hacker 