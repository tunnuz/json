#include "json_st.hh"

using namespace std;

Value::Value() : type_t(NIL) {}

Value::Value(const int& i) : int_v(i), type_t(INT) { }

Value::Value(const float& f) : float_v(f), type_t(FLOAT) { }

Value::Value(const bool& b) : bool_v(b), type_t(BOOL) { }

Value::Value(const std::string& s) : string_v(s), type_t(STRING) { }

Value::Value(const Object& o) : object_v(o), type_t(OBJECT) { }

Value::Value(const Array& o) : array_v(o), type_t(ARRAY) { }

Object::Object() { }

Object::~Object() { }

Object::Object(const Object& o) : _object(o._object) { }

Object& Object::operator=(const Object& o)
{
    _object = o._object;
}

Value& Object::operator[] (const std::string& key)
{
    return _object[key];
}

std::pair<std::map<std::string, Value>::iterator, bool> Object::insert(const std::pair<std::string, Value>& v)
{
    return _object.insert(v);
}

std::map<std::string, Value>::const_iterator Object::begin() const
{
    return _object.begin();
}

std::map<std::string, Value>::const_iterator Object::end() const
{
    return _object.end();
}

size_t Object::size() const
{
    return _object.size();
}

Array::Array() { }

Array::~Array() { }

Array::Array(const Array& a)
{
    _array = a._array;
}

Array& Array::operator=(const Array& a)
{
    _array = a._array;
}


Value& Array::operator[] (size_t i)
{
    return _array[i];
}

std::vector<Value>::const_iterator Array::begin() const
{
    return _array.begin();
}

std::vector<Value>::const_iterator Array::end() const
{
    return _array.end();
}

size_t Array::size() const
{
    return _array.size();
}

void Array::push_back(const Value& v)
{
    _array.push_back(v);
}

void indent(ostream& os)
{
    for (unsigned int i  = 0; i < ind; i++)
        os << "\t";
}

ostream& operator<<(ostream& os, const Value& v)
{    
    switch(v.type())
    {
        /** Base types */
        
        case INT:
        os << (int)v;
        break;
        
        case FLOAT:
        os << (float)v;
        break;
        
        case BOOL:
        os << ((bool)v ? "true" : "false");
        break;
        
        case NIL:
        os << "null";
        break;
        
        case STRING:
        os << '"' << (string)v << '"';                
        break;
        
        /** Compound types */
        
        case ARRAY:
        os << (Array)v;                
        break;
        
        case OBJECT:
        os << (Object)v;                
        break;
        
    }
    return os;
}

std::ostream& operator<<(ostream& os, const Object& o)
{    
    os << "{" << endl;
    ind++;
    for (auto e = o.begin(); e != o.end();)
    {
        indent(os);
        os << '"' << e->first << '"' << ": " << e->second;
        if (++e != o.end())
            os << ",";
        os << endl;
    }    
    ind--;
    indent(os);
    os << "}";
}

std::ostream& operator<<(ostream& os, const Array& a)
{
    os << "[" << endl;
    ind++;
    for (auto e = a.begin(); e != a.end();)
    {
        indent(os);
        os << (*e);
        if (++e != a.end())
            os << ",";
        os << endl;
    }    
    ind--;
    indent(os);
    os << "]";
}
