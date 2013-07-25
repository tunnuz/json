.PHONY: all clean
	
all: json
	
json: json.tab.c lex.yy.c json.hh
	g++ -lfl json.tab.c json.tab.h lex.yy.c -o json  
	
json.tab.c: json.y
	bison -d json.y
	
lex.yy.c: json.l
	flex json.l

clean:
	rm -rf json.tab.c json.tab.h lex.yy.c