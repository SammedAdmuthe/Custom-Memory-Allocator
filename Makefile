CC = gcc

memgrind: 
	$(CC) -o memgrind  memgrind.c && ./memgrind

clean:
	rm -rf memgrind *.o *.a 
