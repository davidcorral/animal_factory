#pragma once

#include <memory>
#include <string>

class Dog;
// -----------------------------------------------------------------------------

class Animal
{
public:
    typedef std::shared_ptr<Animal> Ptr;

    virtual ~Animal(){}
    /// 
    virtual std::string 
    typeName() const { return "animal"; };    
    ///
    virtual 
    bool hasLegs() const = 0;
    ///
    virtual
    bool hasWings() const = 0;
    ///
    virtual std::string
    name() const = 0;
    ///
    Dog&
    asDog();
};

class Dog: public Animal
{
public:
    typedef std::shared_ptr<Dog> Ptr;

    using Animal::Animal;
    virtual ~Dog(){}
    
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
    name() const override = 0;

    std::string
    bark() const { return "woof"; };
};

class Balto: public Dog
{
public:
    typedef std::shared_ptr<Balto> Ptr;

    using Dog::Dog;
    virtual ~Balto(){}
     
    ///
    std::string
    name() const override { return "Balto"; };
    ///
    static Animal::Ptr
    creator(){ return std::make_shared<Balto>(); };
};

Dog&
Animal::asDog(){ return *dynamic_cast<Dog*>(this); };