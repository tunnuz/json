#include <iostream>
#include "json.hh"

using namespace std;

int main(int argc, char** argv)
{
    Object obj;
    
    obj["foo"] = true;
    obj["bar"] = 1;
    
    Object o;
    o["failure"] = true;
    o["success"] = "no way";
    
    obj["baz"] = o;
        
    Array a;
    a.push_back(Value(true));
    a.push_back(Value("iajsia"));
    a.push_back(Value("asas"));
    a.push_back(Value(55));
    
    obj["beer"] = a;

    cerr << obj << endl;
    
    return 0;
}