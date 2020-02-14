all: encode

encode: encode.o functions.o
	gcc -Wall -o encode encode.o functions.o

encode.o: encode.c functions.h
	gcc -Wall -c encode.c functions.h

functions.o: functions.c functions.h
	gcc -Wall -c functions.c functions.h

clean:
	rm *.gch encode *.o