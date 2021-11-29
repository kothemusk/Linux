TARGET=ex5
CXX=gcc
CXXFLAGS=-W2
OBJECTS=process.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
process.o: process.c
	$(CXX) -c process.c
clean:
	rm $(OBJECTS) $(TARGET)
