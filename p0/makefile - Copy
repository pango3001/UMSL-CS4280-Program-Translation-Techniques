CXX	= g++
CXXFLAGS = -g -Wall
TARGET1	= main
TARGET2	= tree
OBJS1	= main.o
OBJS2	= tree.o
DEPS    = node.h
RM      = rm -f

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	$(CC) -o $@ $(OBJS1)

$(TARGET2): $(OBJS2)
	$(CC) -o $@ $(OBJS2) $(DEPS)

.PHONY: clean

clean:
	$(RM) core *.o $(TARGET1) $(TARGET2)
