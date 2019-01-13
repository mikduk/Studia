make: parser.y lexer.l
	bison -d parser.y
	flex lexer.l
	g++ -std=c++11 -o kompilator lex.yy.c parser.tab.c -lfl

clean:
	rm parser.tab.c parser.tab.h lex.yy.c $(OBJ) kompilator
