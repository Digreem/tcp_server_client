all: server client

server: server.cpp
	gcc -g -o server server.cpp

client: client.cpp
	gcc -g -o client client.cpp
	
clean :
	rm -f *.o client server