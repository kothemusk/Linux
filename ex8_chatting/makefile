TARGET=ex9
CXX=gcc
CXXFLAGS=-W2
OBJECTS=message.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
message.o: message.c
	$(CXX) -c message.c
clean:
	rm $(OBJECTS) $(TARGET)
