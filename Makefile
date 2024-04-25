CC = g++
CFLAGS = -g -Wall -std=c++11

# Define a rule to build the executable
main: main.o functions.o HashTable.o
	$(CC) $(CFLAGS) -o main main.o functions.o HashTable.o

# Define a rule to compile main.cpp
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

# Define a rule to compile HashTable.cpp
HashTable.o: HashTable.cpp HashTable.h
	$(CC) $(CFLAGS) -c HashTable.cpp

# Define a rule to compile functions.cpp
functions.o: functions.cpp HashTable.h
	$(CC) $(CFLAGS) -c functions.cpp

# Define a rule to clean the generated files
clean:
	rm -f *.o main