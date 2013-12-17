CFLAGS=-Wall -O2
FLAGS=-framework GLUT -framework OpenGL -framework Cocoa
CC=clang++
SRC=src/
BIN=bin/
all: $(BIN)run.app

$(BIN)run.app: $(BIN)main.o $(BIN)img.o $(BIN)extra.o
	$(CC) -o $(BIN)run.app $(BIN)main.o $(BIN)img.o $(BIN)extra.o $(CFLAGS)	$(FLAGS)

$(BIN)main.o: $(SRC)main.cpp $(SRC)main.h
	$(CC) -o $(BIN)main.o -c $(SRC)main.cpp $(CFLAGS)

$(BIN)extra.o: $(SRC)extra.cpp $(SRC)extra.h
	$(CC) -o $(BIN)extra.o -c $(SRC)extra.cpp $(CFLAGS)

$(BIN)img.o: $(SRC)RgbImage.cpp
	$(CC) -o $(BIN)img.o -c $(SRC)RgbImage.cpp $(CFLAGS)

$(BIN)glm.o: $(SRC)glm/glm.cpp $(SRC)glm/glm.h
	$(CC) -o $(BIN)glm.o -c $(SRC)glm/glm.cpp $(CFLAGS)

clean:
	rm -rf $(BIN)*.o

mrproper: clean
	rm -rf $(BIN)run.app

run: $(BIN)run.app
	./$(BIN)run.app Ronaldo Pato
