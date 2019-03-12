CC = g++ -std=c++11 -g
OBJ = sermain.o SysServer.o Mqueue.o Client.o Contral.o Model.o View.o WorkPthread.o TcpServer.o DataBase.o


sermain:$(OBJ)
	$(CC) -o $@ $^ -lpthread -ljson -levent -lmysqlclient

sermain.o:sermain.cpp
	$(CC) -c $<

SysServer.o:SysServer.cpp SysServer.h
	$(CC) -c $<

WorkPthread.o:WorkPthread.cpp WorkPthread.h
	$(CC) -c $<

Client.o:Client.cpp Client.h
	$(CC) -c $<

Mqueue.o:Mqueue.cpp Mqueue.h
	$(CC) -c $<

DataBase.o:DataBase.cpp DataBase.h
	$(CC) -c $<

TcpServer.o:TcpServer.cpp TcpServer.h
	$(CC) -c $<

Contral.o:Contral.cpp Contral.h
	$(CC) -c $<

Model.o:Model.cpp Model.h
	$(CC) -c $<

View.o:View.cpp View.h
	$(CC) -c $<

clean:
	rm -rf $(OBJ) main
