INPUT=src
OUTPUT=build
BIN=$(OUTPUT)/bin
OBJ=$(OUTPUT)/obj
SERVERBIN=kws2
GCC=g++ -std=c++11

all: $(BIN)/$(SERVERBIN)

clean:
	rm -rf $(OUTPUT)

$(OUTPUT):
	mkdir -p $(OUTPUT)

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

$(OBJ)/Configurator.o: $(INPUT)/Configurator.cc $(INPUT)/Configurator.h
	$(GCC) -c $(INPUT)/Configurator.cc -o $(OBJ)/Configurator.o

$(OBJ)/Handler.o: $(INPUT)/Handler.cc $(INPUT)/Handler.h
	$(GCC) -c $(INPUT)/Handler.cc -o $(OBJ)/Handler.o

$(OBJ)/Socket.o: $(INPUT)/Socket.cc $(INPUT)/Socket.h
	$(GCC) -c $(INPUT)/Socket.cc -o $(OBJ)/Socket.o

$(BIN)/$(SERVERBIN): $(OUTPUT) $(BIN) $(OBJ) $(OBJ)/Configurator.o $(OBJ)/Handler.o $(OBJ)/Socket.o $(INPUT)/kws2.cc
	$(GCC) -o $(BIN)/$(SERVERBIN) $(OBJ)/Configurator.o $(OBJ)/Handler.o $(OBJ)/Socket.o $(INPUT)/kws2.cc
