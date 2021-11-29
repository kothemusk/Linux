TARGET=ex11
CXX=gcc
CXXFLAGS=-W2
OBJECTS=pthread.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) -lpthread
pthread.o: pthread.c
	$(CXX) -c pthread.c -lpthread
clean:
	rm $(OBJECTS) $(TARGET)
