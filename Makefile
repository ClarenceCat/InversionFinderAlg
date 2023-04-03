# File: Makefile
# Name: Daniel Grew - 0978547
# Description: This is the make file which compiles all components of the assignment 

# macros 
INC = inc/
SRC = src/
BIN = bin/

CC = gcc 
CFLAGS = -Wall -std=c11 -g


all: $(BIN)assignment2 

$(BIN)assignment2: $(BIN)main.o $(BIN)P11.o $(BIN)P12.o $(BIN)P21.o $(BIN)P22.o $(BIN)filehandler.o $(BIN)PointsHelpers.o 
	$(CC) $(CFLAGS) -L$(BIN) $(BIN)*.o -o $(BIN)assignment2 -lm

$(BIN)main.o: $(SRC)main.c $(INC)assignment2.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)main.c -o $(BIN)main.o 

$(BIN)P11.o: $(SRC)P11.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P11.c -o $(BIN)P11.o 

$(BIN)P12.o: $(SRC)P12.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P12.c -o $(BIN)P12.o 

$(BIN)P21.o: $(SRC)P21.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P21.c -o $(BIN)P21.o 

$(BIN)P22.o: $(SRC)P22.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P22.c -o $(BIN)P22.o 

$(BIN)filehandler.o: $(SRC)filehandler.c $(INC)assignment2.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)filehandler.c -o $(BIN)filehandler.o 


$(BIN)PointsHelpers.o : $(SRC)PointsHelpers.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)PointsHelpers.c -o $(BIN)PointsHelpers.o 

clean: 
	rm $(BIN)*.o $(BIN)assignment2  
