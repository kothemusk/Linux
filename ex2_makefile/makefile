TARGET=week3_makefile
CXX=gcc
CXXFLAGS=-W2
OBJECTS=main.o plus.o minus.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
main.o: main.c
	$(CXX) -c $^
plus.o: plus.c
	$(CXX) -c plus.c
minus.o: minus.c
	$(CXX) -c minus.c
clean:
	rm $(OBJECTS) $(TARGET)
