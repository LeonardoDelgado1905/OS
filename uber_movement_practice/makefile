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