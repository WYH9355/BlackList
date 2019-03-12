CC = g++ -std=c++11 -g
OBJ = climain.o RootProcess.o Selecter.o Server.o Sys.o TcpClient.o TcpServer.o

climain:$(OBJ)
	$(CC) -o $@ $^ -lpthread -ljson -levent 

climain.o:climain.cpp climain.h
	$(CC) -c $<

RootProcess.o:RootProcess.cpp RootProcess.h
	$(CC) -c $<

Selecter.o:Selecter.cpp Selecter.h
	$(CC) -c $<

Server.o:Server.cpp Server.h
	$(CC) -c $<

Sys.o:Sys.cpp Sys.h
	$(CC) -c $<

TcpClient.o:TcpClient.cpp TcpClient.h
	$(CC) -c $<

TcpServer.o:TcpServer.cpp Server.h
	$(CC) -c $<

clean:
	rm -rf $(OBJ) main
