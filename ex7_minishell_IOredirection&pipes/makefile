TARGET=ex8
CXX=gcc
CXXFLAGS=-W2
OBJECTS=ipc.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
ipc.o: ipc.c
	$(CXX) -c ipc.c
clean:
	rm $(OBJECTS) $(TARGET)
