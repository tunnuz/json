#ifndef JSON_HH
#define JSON_HH

#include <vector>
#include <iostream>
#include <map>
#include <stack>


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

class Object
{
public:

    Object();
    
    Object(const Object& o);
    
    Object& operator=(const Object& o);

    Value& operator[] (const std::string& key);

    std::map<std::string, Value>::const_iterator begin() const;

    std::map<std::string, Value>::const_iterator end() const;
    
    std::pair<std::map<std::string, Value>::iterator, bool> insert(const std::pair<std::string, Value>& v);

    size_t size() const;

protected:

    std::map<std::string, Value> _object;
};

class Array
{
public:

    Array();
    
    Array(const Array& o);
    
    Array& operator=(const Object& o);

    Value& operator[] (const int i);

    std::vector<Value>::const_iterator begin() const;

    std::vector<Value>::const_iterator end() const;

    void push_back(const Value& n);

    size_t size() const;

protected:

    std::vector<Value> _array;

};

class Value
{
public:
    
    Value();
    
    Value(const int& i);
    
    Value(const float& f);
    
    Value(const bool& b);
    
    Value(const std::string& s);
        
    Value(const Object& o);
    
    Value(const Array& o);

    Value& operator=(const Value& e);
    
    ValueType type() const
    {
        return type_t;
    }
            
    float           float_v;
    int             int_v;
    bool            bool_v;
    std::string     string_v;
    Object          object_v;
    Array           array_v;
    ValueType       type_t;
};
    
std::ostream& operator<<(std::ostream&, const Value&);

std::ostream& operator<<(std::ostream&, const Object&);

std::ostream& operator<<(std::ostream&, const Array&);

static unsigned int ind;

static unsigned int count;

static std::stack<Value> list_s;

static std::stack<std::pair<std::string, Value> > assign_list_s;

static void indent(std::ostream& os = std::cout);

#endif