#pragma once

#include <memory>
#include <string>

class Dog;
// -----------------------------------------------------------------------------

class Animal
{
public:
    typedef std::shared_ptr<Animal> Ptr;

    virtual ~Animal() = default;
    /// 
    virtual std::string 
    typeName() const { return "animal"; };    
    ///
    virtual bool 
    hasLegs() const = 0;
    ///
    virtual bool 
    hasWings() const = 0;
    ///
    virtual std::string
    name() const = 0;
};

class Dog: public Animal
{
public:
    typedef std::shared_ptr<Dog> Ptr;

    using Animal::Animal;
    virtual ~Dog() = default;
    
    /// 
    std::string 
    typeName() const override { return "dog"; };    
    ///
    bool
    hasLegs() const override { return true; };    
    ///
    bool
    hasWings() const override { return false; };  
    ///
    std::string
    bark() const { return "woof"; };
};