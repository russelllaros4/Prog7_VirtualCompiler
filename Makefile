OBJ= Prog7.o Assembler.o Hashtable.o Hash.o
OPTS= -g -c -Wall -Werror

assemble: $(OBJ)
	g++ -o Assemble $(OBJ)
prog7.o: Prog7.cc Assembler.h Hashtable.h Hash.h 
	g++ $(OPTS) Prog7.cc
assembler.o: Assembler.cc Assembler.h Hashtable.h Hash.h Link.h
	g++ $(OPTS) Assembler.cc
hashtable.o: Hashtable.cc Hashtable.h Hash.h
	g++ $(OPTS) Hashtable.cc
hash.o: Hash.cc Hash.h
	g++ $(OPTS) Hash.cc
clean:
	rm -f *.o testhash *~
