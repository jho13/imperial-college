sudoku: main.o sudoku.o
	g++ main.o sudoku.o -o sudoku
	
%.o: %.cpp
	g++ -Wall -g -c $<
	
main.o: sudoku.h

sudoku.o: sudoku.h

clean: 
	rm -f sudoku *.o
