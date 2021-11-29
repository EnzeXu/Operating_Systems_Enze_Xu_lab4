cc = gcc
all: server node hacker
.PHONY: clean

server: server.c messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o server print_server.c

node: node.c messageTools.h semaphoreTools.h basicTools.h
	$(cc) -pthread -o node node.c

hacker: hacker.c messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o hacker hacker.c

clean: 
	rm server 
	rm node
	rm hacker 