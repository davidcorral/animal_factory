#pragma once

#include <memory>
#include <string>

#include "animal.h"

class Balto: public Dog
{
public:
    typedef std::shared_ptr<Balto> Ptr;

    using Dog::Dog;
    virtual ~Balto() = default;
    ///
    std::string
    name() const override { return "Balto"; };  
    ///
    static Animal::Ptr
    creator(){ return std::make_shared<Balto>(); };
};
