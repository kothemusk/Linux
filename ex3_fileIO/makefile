TARGET=ex4
CXX=gcc
CXXFLAGS=-W2
OBJECTS=numbering.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
numbering.o: numbering.c
	$(CXX) -c numbering.c
clean:
	rm $(OBJECTS) $(TARGET)
