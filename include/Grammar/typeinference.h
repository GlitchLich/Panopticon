#ifndef TYPEINFERENCE_H
#define TYPEINFERENCE_H

#include <string>
#include <deque>
#include <unordered_map>
#include "include/core/types.h"
#include "parse_ast.h"
#include <sstream>

namespace panopticon
{

namespace typing
{



void init();

//TypeDef
class TypeDef
{
public:
    TypeDef() {}
    enum Type{TYPE_VAR,TYPE_OP};
    virtual Type type() const = 0;
    virtual std::string get_name() = 0;
    virtual std::string print_string() = 0;
};

TypeDef* analyze(ExprAST* expr);

typedef std::vector<TypeDef*> TypeVec;

//TypeOperator
class TypeOperator : public TypeDef
{
public:
    enum SubType{Product,Sum,Function,Primitive};
    TypeOperator(std::string name, TypeVec types, SubType sub_type) :
        name(name),
        types(types),
        sub_type(sub_type)
    {

    }

    Type type() const {return TypeDef::TYPE_OP;}

//    virtual () const = 0;
    virtual std::string print_string() = 0;

    std::string get_name()
    {
        return name;
    }
    TypeVec types;
    SubType sub_type;
protected:
    std::string name;

};

class SumOperator : public TypeOperator
{
public:
    SumOperator(std::string name, TypeVec types) :
        TypeOperator(name,types,TypeOperator::Sum)
    {

    }

//    SubType sub_type() const {return TypeOperator::Sum;}
    std::string print_string()
    {
        std::stringstream ss;
        ss << "( " << name << " = ";
        for(int i=0;i<types.size();++i)
        {
            ss << types.at(i)->print_string();
            if(i<types.size() -1)
            {
                ss << "| ";
            }
        }
        ss << ") ";

        return ss.str();
    }
};

class ProductOperator : public TypeOperator
{
public:
    ProductOperator(std::string name, TypeVec types) :
        TypeOperator(name,types,TypeOperator::Product)
    {

    }

//    SubType sub_type() const {return TypeOperator::Product;}
    std::string print_string()
    {
        std::stringstream ss;
        ss << "( " << name << " = ";
        for(int i=0;i<types.size();++i)
        {
            ss << types.at(i)->print_string();
            if(i<types.size() -1)
            {
                ss << " ";
            }
        }
        ss << ") ";

        return ss.str();
    }
};

class FunctionOperator : public TypeOperator
{
public:
    FunctionOperator(std::string name, TypeVec types) :
        TypeOperator(name,types,TypeOperator::Function)
    {
        assert(types.size() == 2);
    }

//    SubType sub_type() const {return TypeOperator::Function;}
    std::string print_string()
    {
        std::stringstream ss;
        ss << types.at(0)->print_string();
        ss << " -> ";
        ss << types.at(1)->print_string();

        return ss.str();
    }
};

class PrimitiveOperator : public TypeOperator
{
public:
    PrimitiveOperator(std::string name,panopticon::Type optic_type) :
        TypeOperator(name,TypeVec(),TypeOperator::Primitive),
        optic_type(optic_type)
    {
        assert(types.size() == 0);
    }

//    SubType sub_type() const {return TypeOperator::Primitive;}
    std::string print_string()
    {
        std::stringstream ss;
        ss << name;
        return ss.str();
    }

    panopticon::Type optic_type;
};

//TypeVariable
extern int next_variable_id;// = 0;
extern char next_variable_name;// = 'a';

char get_next_variable_name();

class TypeVariable : public TypeDef
{
public:
    TypeVariable() :
        instantiated(false)
    {
        id = next_variable_id;
        next_variable_id++;
    }

    Type type() const {return TypeDef::TYPE_VAR;}

    std::string get_name()
    {
        if(name.empty())
        {
            instantiated = true;
            name.push_back(next_variable_name);
            next_variable_name = get_next_variable_name();
        }
        return name;
    }

    std::string print_string()
    {
        std::stringstream ss;
        ss << "TypeVariable(" << get_name() << ")";
        return ss.str();
    }

    bool instantiated;

private:
    int id;
    std::string name;
};

}

}

#endif // TYPEINFERENCE_H
