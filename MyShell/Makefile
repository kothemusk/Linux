TARGET=minishell
CXX=gcc
CXXFLAGS=-W2
OBJECTS=minishell.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
minishell.o: minishell.c
	$(CXX) -c minishell.c
clean:
	rm $(OBJECTS) $(TARGET)
