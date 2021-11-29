TARGET=ex13
CXX=gcc
CXXFLAGS=-W2
OBJECTS=synchronization.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) -lpthread
synchronization.o: synchronization.c
	$(CXX) -c synchronization.c -lpthread
clean:
	rm $(OBJECTS) $(TARGET)
