# JSON++

JSON\+\+ is a **self contained** Flex/Bison JSON parser for C\+\+11. It parses strings and files in JSON format, and builds an in-memory tree representing the JSON structure. JSON objects are mapped to `std::map`s, arrays to `std::vector`s, JSON native types are mapped onto C++ native types. The library also includes printing on streams. Classes exploit move semantics to avoid copying parsed structures around. It doesn't require any additional library (not even `libfl`).

## Updates 

*July 20, 2014* - In the past few months I have merged various pull requests, which I considered good additions to the code (e.g., someone fixed memory leaks, someone improved the CMake build system, someone started to add support for unicode escaped characters). These were all very good contributions, and I'd like to thank anyone that has filed a pull request for JSON++. However, I have sometimes overlooked the code that I was merging and, sometimes, pull requests with early code were merged in the main distribution. For this reason, a few days ago I have rolled back to a previous version of the code, from the end of June. This is my first open source projects that gains a bit of traction (the repository has about 1500 visits per month), and I'll be more careful in merging pull requests from now on.

## Git repository

A version of this repository (regularly mirrored) is available on [GitHub](https://github.com/tunnuz/json).

## Contributors

JSON++ is not a personal project anymore, people is constantly writing to me, and sending pull requests to improve it and make it better. I'd like to thank these people by adding them to this *Contributors* section (in order of contribution).

* [Jakob Leben](https://bitbucket.org/jleben)
* [Thomas Rinklin](https://bitbucket.org/t-ri)
* [Luca Di Gaspero](https://bitbucket.org/ldigaspero)
* [Helmuth Ploner](https://bitbucket.org/HelmuthPloner)

Thanks for your effort fellas.

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
		
        // Or build the object manually
        Object obj;
    
        obj["foo"] = true;
        obj["bar"] = 3;
    
        Object o;
        o["given_name"] = "John";
        o["family_name"] = "Boags";
    
        obj["baz"] = o;
        
        Array a;
        a.push_back(true);
        a.push_back("asia");
        a.push_back("europe");
        a.push_back(55);
    
        obj["test"] = a;
        
		cout << o << endl;
        
        return 0;
	}

## How to build JSON++

The project includes a `CMakeLists.txt` files which allows you to generate build files for most build systems. Just run

    cmake .    

and then

    make

The project generates 


* json.tab.hh,
* json.tab.cc, and
* lex.yy.cc

files from `json.l` and `json.y`, then compiles them (and a few other files) into a `libjson` library, which is finally used to link the `test` executable. You can use the library in your projects, or use the Flex/Bison files straight away.

## Flex/Bison quirks when using C++ classes

This section is for the ones who got here because they're trying to build stuff with Flex/Bison and C\+\+. This was my first Flex/Bison parser (the main motivation behind its development being that I didn't find a parser for JSON in C\+\+ which didn't require a number of extra libraries, plus I wanted to learn Flex/Bison).

So, for the ones venturing in this world, here's a few things I wish I knew when I set off to write the parser.

1. Every rule of the Bison grammar has a left-hand side, to which the parsed objects (no matter their type), must be assigned. To do this, a `union` is used. Bison uses the `%union { ... }` rule to declare the types inside the union, which must only contain **native C types** or **pointers** to C++ classes,
2. in case pointers to C++ classes are used in `%union`, classes extending `std` containers **won't work**, so you'll need to wrap `std` stuff in your own classes,
3. always put a starting rule in the grammar to assign the result of the overall parse to a variable, e.g., `json: value { $$ = $1; }`,
4. as a general rule, functions requiring Flex functions, e.g., `yy_scan_string`, etc., should be defined in the `.l` file, and their prototypes put in the `.y` file as well, so that they can be called from the parser's functions,
5. ... (to be continued as I find out more).

## Licensing

This code is distributed under the very permissive MIT License but, if you use it, you might consider referring to the repository.