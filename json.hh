#ifndef JSON_HH
#define JSON_HH

#include <vector>
#include <iostream>
#include <map>

using namespace std;

namespace JSON
{
    enum ValueType
    {
        INT,
        FLOAT,
        BOOL,
        STRING,
        OBJECT,
        ARRAY
    };
    
    class Value;
    
    typedef std::string Key;
    typedef std::vector<JSON::Value> Array;
    typedef std::map<JSON::Key, JSON::Value> Object;
    
    class Value
    {
    public:
        
        Value(int i) : int_v(i), type_t(INT) { }
        
        Value(float f) : float_v(f), type_t(FLOAT) { }
        
        Value(bool b) : bool_v(b), type_t() { }
        
        Value(string s) : string_v(s), type_t(INT) { }
        
        Value(const Object& o) : object_v(o), type_t(OBJECT) { }
        
        Value(const Array& o) : array_v(o), type_t(ARRAY) { }
        
        ValueType type() const
        {
            return type_t;
        }
        
    protected:
        
        float       float_v;
        int         int_v;
        bool        bool_v;
        string      string_v;
        Object      object_v;
        Array       array_v;
        ValueType   type_t;
    };
}

#endif