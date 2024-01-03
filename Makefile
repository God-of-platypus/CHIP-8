OBJS = src/*.c
HEADERS = src/*.h
CC = gcc
C_FLAGS = -w -pedantic
L_FLAGS = -lSDL2
OBJ_NAME = chip-8

all: $(OBJS)
	$(CC) $(OBJS) $(HEADERS) $(C_FLAGS) $(L_FLAGS) -o $(OBJ_NAME) 
