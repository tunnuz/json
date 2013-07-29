# JSON++

A Flex/Bison JSON parser for C++.

## Usage

	#include <iostream>
	#include "json.hh"
	
	using namespace std;
	using namespace JSON;
	
	int main(int argc, char** argv)
	{
		// Read JSON from a string
		Value v = parse_string(<your_json_string>);
		cout << v << endl;
        
        // Read JSON from a file
		v = parse_file("<your_json_file>.json");
		cout << v << endl;
		
		return 0;
	}

## How to build JSON++

Make sure you have Flex and Bison installed, since the parser and lexer will be generated on the fly. Then just run (to build the test ).

    make

## Flex/Bison quirks when using C++ classes

This section is for the ones who got here because they're trying to build stuff with Flex/Bison and C++. This was my first Flex/Bison parser (the main motivation behind its development being that I didn't find a parser for JSON in C++ which didn't require a number of extra libraries).

So, for the ones venturing in this world, here's a few things I wish I knew when I set off to write the parser.

1. `%union { ... }` must only contain native C types or pointers to C++ classes,
2. in case pointers to C++ classes are used in `%union`, classes extending `std` containers won't work,
3. put a starting rule in the grammar to assign the result of the parse to a variable, e.g., `json: value { $$ = $1; }`,
4. as a general rule, functions requiring Flex functions, e.g., `yy_scan_string`, etc., should be defined in the `.l` file, and their prototypes put in the `.y` file as well, so that they can be called from the parser's functions,
5. the JSON syntax tree classes (`json_st.hh` and `json_st.cc`) are implemented as collections of pointers for performance reasons (because of 1. the returned values from the parser must be pointers),
6. 