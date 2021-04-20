labapp: labapp.o zoomrecs.o
	gcc -o labapp labapp.o zoomrecs.o
labapp.o: labapp.c
	gcc -c labapp.c
zoomrecs.o: zoomrecs.c
	gcc -c zoomrecs.c