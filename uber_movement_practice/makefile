all: clear search
create:
	gcc createbinary.c -o create
	./create
	
search: create 
	gcc search.c -o search
	./search

clear:
	rm ./search
	rm ./create
	rm ./reader
	rm ./interface

ejecucion:
	gcc reader.c -o reader 
	gcc interface.c -o interface
	./reader & ./interface
	