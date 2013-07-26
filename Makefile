.PHONY: all clean
	
all: json test
	
json: json.tab.c lex.yy.c json_st.hh json_st.cc
	g++ -std=c++11 $^ -o $@  
	
test: json_st.cc json_st.hh test.cc
	g++ -std=c++11 $^ -o $@	

json.tab.c: json.y
	bison -d json.y
	
lex.yy.c: json.l
	flex json.l

clean:
	rm -rf json.tab.c json.tab.h lex.yy.c json test
