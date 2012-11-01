# neste template de Makefile so muda a lista
# dos SOURCES e o nome do EXECUTABLE.

CC = g++
CFLAGS = -c -Wall  -std=c++11  -fpermissive
LDFLAGS = -lgtest -lgsl -lgslcblas -lm -lpthread
SOURCES =  ../geometric_utils/geometry.cpp  main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = test 


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

