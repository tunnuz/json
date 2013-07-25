#ifndef JSON_HH
#define JSON_HH

#include <vector>
#include <iostream>
#include <map>


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
            
    class Value
    {
    public:
        
        Value() {}
        
        Value(const int& i) : int_v(i), type_t(INT) { }
        
        Value(const float& f) : float_v(f), type_t(FLOAT) { }
        
        Value(const bool& b) : bool_v(b), type_t(BOOL) { }
        
        Value(const std::string& s) : string_v(s), type_t(STRING) { }
        
        Value(const char* s) : string_v(s), type_t(STRING) { }
        
        Value(const std::map<std::string, Value>& o) : object_v(o), type_t(OBJECT) { }
        
        Value(const std::vector<Value>& o) : array_v(o), type_t(ARRAY) { }

        Value& operator=(const Value& e)
        {
            
            type_t = e.type();
            
            switch (type_t)
            {
                case INT:
                int_v = e.int_v;
                break;

                case FLOAT:
                float_v = e.float_v;
                break;

                case BOOL:
                bool_v = e.bool_v;
                break;

                case STRING:
                string_v = e.string_v;
                break;

                case OBJECT:
                object_v = e.object_v;
                break;

                case ARRAY:
                array_v = e.array_v;
                break;                
            }
        
            return *this;
        }
        
        
        ValueType type() const
        {
            return type_t;
        }
                
        float float_v;
        int int_v;
        bool bool_v;
        std::string string_v;
        std::map<std::string, Value> object_v;
        std::vector<Value> array_v;
        ValueType type_t;
    };


std::ostream& operator<<(std::ostream&, const Value&);

std::ostream& operator<<(std::ostream&, const std::map<std::string, Value>&);

std::ostream& operator<<(std::ostream&, const std::vector<Value>&);

static unsigned int ind;

static void indent(std::ostream& os = std::cout);

#endif