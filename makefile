cc = gcc

server: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o server print_server.c

node: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o node node.c

hacker: messageTools.h semaphoreTools.h basicTools.h
	$(cc) -o hacker hacker.c