.PHONY: all clean
	
all: json test
	
json: json.tab.c lex.yy.c json.hh
	g++ -std=c++11 -lfl json.tab.c json.tab.h lex.yy.c -o json  
	
json.tab.c: json.y
	bison -d json.y
	
lex.yy.c: json.l
	flex json.l

clean:
	rm -rf json.tab.c json.tab.h lex.yy.c json test
	
test: json.hh test.cc json.cc
	g++ -std=c++11 test.cc json.cc -o test