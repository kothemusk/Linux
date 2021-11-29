TARGET=ex6
CXX=gcc
CXXFLAGS=-W2
OBJECTS=cronDaemon.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
process.o: cronDaemon.c
	$(CXX) -c cronDaemon.c
clean:
	rm $(OBJECTS) $(TARGET)
