CC=gcc

tree: deque.c tree.c
	$(CC) -o tree tree.c deque.c
	
clean:
	del tree.exe