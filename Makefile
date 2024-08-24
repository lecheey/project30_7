CC = g++
SRC = main.cpp
TARGET = qsort

qsort:
	$(CC) -o $(TARGET) $(SRC) qsort.h qsort.cpp tpool.h tpool.cpp rhandler.h rhandler.cpp
