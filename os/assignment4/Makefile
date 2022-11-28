CC = gcc
TARGET = a.out
OBJS = UI.o Optimal.o FIFO.o LIFO.o LRU.o LFU.o SC.o ESC.o linkedList.o Queue.o

all : $(TARGET)

$(TARGET) : $(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

UI.o :
	$(CC) -c UI.c

linkedList.o :
	$(CC) -c linkedList.c

Queue.o :
	$(CC) -c Queue.c

Optimal.o:
	$(CC) -c Optimal.c

FIFO.o :
	$(CC) -c FIFO.c

LIFO.o :
	$(CC) -c LIFO.c

LRU.o :
	$(CC) -c LRU.c

LFU.o :
	$(CC) -c LFU.c

SC.o :
	$(CC) -c SC.c

ESC.o :
	$(CC) -c ESC.c

clean :
	rm -f $(OBJS) $(TARGET)
