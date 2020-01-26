CC=gcc
LLC=llc
CFLAGS=-fno-stack-protector
TARGET=bubble_sort

all : $(TARGET) $(TARGET)_llvm

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(TARGET).o 
	$(CC) -o $(TARGET) $(TARGET).o

%.s: %.ll
	$(LLC) $<

$(TARGET)_llvm: $(TARGET).s $(TARGET)_llvm.o
	$(CC) -o $(TARGET)_llvm $(TARGET)_llvm.o $(TARGET).s

.PHONY: clean

clean:
	rm -rf *.o *~
