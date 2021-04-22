all: ejecucion

reindex: clear create ejecucion
create:
	gcc createbinary.c -o create
	./create
ejecucion: create
	gcc reader.c -o reader 
	gcc p1-odProgram.c -o p1-odProgram
	./reader & ./p1-odProgram
clear:
	rm -f ./create
	rm -f ./reader
	rm -f ./p1-odProgram
	