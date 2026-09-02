OBJ := $(patsubst %.c, %.o, $(wildcard * .c))
timmu.out: $(OBJ)
	gcc -o $@ $^
clean:
	rm *.out *.o

# addressbook: main.o functions.o
#	gcc main.o functions.o -o addressbook

# main.o: main.c project_header.h
#	gcc -c main.c

# functions.o: functions.c project_header.h
#	gcc -c functions.c

# clean:
#	rm -f *.o addressbook