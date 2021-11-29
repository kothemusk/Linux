TARGET=ex14
CXX=gcc
CXXFLAGS=-W2
OBJECTS=producer_consumer.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) -lpthread
producer_consumer.o: producer_consumer.c
	$(CXX) -c producer_consumer.c -lpthread
clean:
	rm $(OBJECTS) $(TARGET)
