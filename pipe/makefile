.PHONY:all
all:client server

client:client.cpp
	gcc -o $@ $^
server:server.cpp
	gcc -o $@ $^

.PHONY:clean
clean:
	rm client server
