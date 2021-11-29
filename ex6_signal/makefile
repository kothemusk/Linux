TARGET=ex7
CXX=gcc
CXXFLAGS=-W2
OBJECTS=signal.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
signal.o: signal.c
	$(CXX) -c signal.c
clean:
	rm $(OBJECTS) $(TARGET)
