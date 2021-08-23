all: xd

xd:
	gcc writer.c -o writer
	gcc reader.c -o reader
	./reader 1000 5 & ./writer 1000 5
	./reader 10000 5 & ./writer 10000 5
	./reader 100000 1 & ./writer 100000 1
	./reader 1000000 1 & ./writer 1000000 1
	./reader 10000000 1 & ./writer 1000000 1
	./reader 100000000 1 & ./writer 1000000 1