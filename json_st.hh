#ifndef JSON_ST_HH
#define JSON_ST_HH

#include <iostream>
#include <map>
#include <vector>
#include <stack>

/** Possible JSON type of a value (array, object, bool, ...). */
enum ValueType
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    OBJECT,
    ARRAY
};

// Forward declaration
class Value;

/** A JSON object, i.e., a container whose keys are strings, this
is roughly equivalent to a Python dictionary, a PHP's associative
array, a Perl or a C++ map (depending on the implementation). */
class Object
{
public:

    /** Constructor. */
    Object();
    
    /** Copy constructor. 
        @param o object to copy from
    */
    Object(const Object& o);
    
    /** Assignment operator. 
        @param o object to copy from
    */
    Object& operator=(const Object& o);
    
    /** Destructor. */
    ~Object();

    /** Subscript operator, access an element by key.
        @param key key of the object to access
    */
    Value* operator[] (const std::string& key) const;

    /** Retrieves the starting iterator (const).
        @remark mainly for printing
    */
    std::map<std::string, Value*>::const_iterator begin() const;

    /** Retrieves the ending iterator (const).
        @remark mainly for printing
    */
    std::map<std::string, Value*>::const_iterator end() const;
    
    /** Retrieves the starting iterator */
    std::map<std::string, Value*>::iterator begin();

    /** Retrieves the ending iterator */
    std::map<std::string, Value*>::iterator end();
    
    /** Inserts a field in the object.
        @param v pair <key, value> to insert
        @return an iterator to the inserted object
    */
    std::pair<std::map<std::string, Value>::iterator, bool> insert(std::pair<std::string, Value*>* v);

    /** Size of the object. */
    size_t size() const;

protected:

    /** Inner container. */
    std::map<std::string, Value*> _object;
};

/** A JSON array, i.e., an indexed container of elements. It contains
JSON values, that can have any of the types in ValueType. */
class Array
{
public:

    /** Constructor. */
    Array();
    
    /** Copy constructor. 
        @param o the object to copy from
    */
    Array(const Array& a);
    
    /** Assignment operator. 
        @param a array to copy from
    */
    Array& operator=(const Array& a);

    /** Subscript operator, access an element by index. 
        @param i index of the element to access
    */
    Value* operator[] (size_t i);
    
    /** Subscript operator, access an element by index. Const.
        @param i index of the element to access
    */
    const Value* operator[] (size_t i) const;

    /** Retrieves the starting iterator (const).
        @remark mainly for printing
    */
    std::vector<Value*>::const_iterator begin() const;

    /** Retrieves the ending iterator (const).
        @remark mainly for printing
    */
    std::vector<Value*>::const_iterator end() const;

    /** Retrieves the starting iterator. */
    std::vector<Value*>::iterator begin();

    /** Retrieves the ending iterator */
    std::vector<Value*>::iterator end();

    /** Inserts an element in the array.
        @param n (a pointer to) the value to add
    */
    void push_back(Value* n);
    
    /** Size of the array. */
    size_t size() const;

protected:

    /** Inner container. */
    std::vector<Value*> _array;

};

/** A JSON value. Can have either type in ValueTypes. */
class Value
{
public:
    
    /** Default constructor. */
    Value();
    
    /** Constructor from pointer to int. */
    Value(int* i);
    
    /** Constructor from pointer to float. */
    Value(float* f);
    
    /** Constructor from pointer to bool. */
    Value(bool* b);
    
    /** Constructor from pointer to string. */
    Value(std::string* s);
        
    Value(Object* o);
    
    Value(Array* o);

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