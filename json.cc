#include "json.hh"

using namespace std;

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
        os << v.int_v;
        break;
        
        case FLOAT:
        os << v.float_v;
        break;
        
        case BOOL:
        os << (v.bool_v ? "true" : "false");
        break;
        
        case STRING:
        os << '"' << v.string_v << '"';                
        break;
        
        /** Compound types */
        
        case ARRAY:
        os << v.array_v;                
        break;
        
        case OBJECT:
        os << v.object_v;                
        break;
        
    }
    return os;
}

std::ostream& operator<<(ostream& os, const map<string, Value>& o)
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

std::ostream& operator<<(ostream& os, const vector<Value>& a)
{
    os << "[" << endl;
    ind++;
    for (auto e = a.begin(); e != a.end();)
    {
        indent(os);
        os << *e;
        if (++e != a.end())
            os << ",";
        os << endl;
    }    
    ind--;
    indent(os);
    os << "]";
}
