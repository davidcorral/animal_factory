#include <memory>
#include <string>
#include <pybind11/pybind11.h>

#include "cage.h"
#include "animal.h"
#include "balto.h"
#include "animal_factory.h"

namespace py = pybind11;

// -----------------------------------------------------------------------------

class PyAnimal : public Animal 
{
public:
    using Animal::Animal;// Inherit constructors

    /* Trampoline (need one for each virtual function) */
    std::string 
    typeName() const override
    { 
        PYBIND11_OVERLOAD(std::string, 
            Animal,   /* Parent class */
            typeName, /* Name of function in C++ (must match Python name) */
                      /* Argument(s) */
        );
    };
    
    /* Trampoline (need one for each virtual function) */
    bool
    hasLegs() const override 
    { 
        PYBIND11_OVERLOAD_PURE( 
            bool,    /* Return type */  
            Animal,  /* Parent class */
            hasLegs, /* Name of function in C++ (must match Python name) */
                     /* Argument(s) */
        );
    };

    /* Trampoline (need one for each virtual function) */
    bool
    hasWings() const override
    {
        PYBIND11_OVERLOAD_PURE(
            bool, /* Return type */
            Animal,      /* Parent class */
            hasWings,    /* Name of function in C++ (must match Python name) */
                         /* Argument(s) */
        );
    };
    /* Trampoline (need one for each virtual function) */
    std::string
    name() const override
    {
        PYBIND11_OVERLOAD_PURE(
            std::string, /* Return type */
            Animal,      /* Parent class */
            name,        /* Name of function in C++ (must match Python name) */
                         /* Argument(s) */
        );
    };
};

class PyDog : public Dog 
{
public:
    using Dog::Dog; // Inherit constructors
    
    /* Trampoline (need one for each virtual function) */
    std::string 
    typeName() const override 
    { 
        PYBIND11_OVERLOAD(
            std::string, /* Return type */
            Dog,         /* Parent class */
            typeName     /* Name of function in C++ (must match Python name) */
        );
    };

    /* Trampoline (need one for each virtual function) */
    bool 
    hasLegs() const override 
    { 
        PYBIND11_OVERLOAD_PURE(
            bool,    /* Return type */
            Dog,     /* Parent class */
            hasLegs, /* Name of function in C++ (must match Python name) */
        );
    };

    /* Trampoline (need one for each virtual function) */
    bool 
    hasWings() const override 
    {
        PYBIND11_OVERLOAD_PURE(
            bool,     /* Return type */
            Dog,      /* Parent class */
            hasWings, /* Name of function in C++ (must match Python name) */
        );
    };  
    std::string 
    name() const override 
    { 
        PYBIND11_OVERLOAD_PURE(
            std::string, /* Return type */
            Dog,         /* Parent class */
            name,        /* Name of function in C++ (must match Python name) */
        ); 
    };
};

class PyBalto : public Balto
{
public:
    using Balto::Balto; // Inherit constructors
    
    std::string 
    typeName() const override { PYBIND11_OVERLOAD( std::string, Balto, typeName ); };

    bool 
    hasLegs() const override { PYBIND11_OVERLOAD_PURE( bool,  Balto,  hasLegs ); };

    bool 
    hasWings() const override { PYBIND11_OVERLOAD_PURE( bool, Balto,  hasWings ); };

    std::string
    name() const override { PYBIND11_OVERLOAD_PURE( std::string, Balto,  name ); };
};

// -----------------------------------------------------------------------------

PYBIND11_MODULE(animal_factory_lib, module) 
{
    py::class_<Animal, PyAnimal, Animal::Ptr> animal(module, "Animal");
    animal.def(py::init<>());
    animal.def("typeName", &Animal::typeName);
    animal.def("hasLegs", &Animal::hasLegs);
    animal.def("hasWings", &Animal::hasWings);
    animal.def("name", &Animal::name);
    animal.def("asDog", &Animal::asDog, py::return_value_policy::reference_internal);

    py::class_<Dog, PyDog, Dog::Ptr, Animal> dog(module, "Dog");
    dog.def(py::init<>());
    dog.def("typeName", &Dog::typeName);
    dog.def("hasLegs", &Dog::hasLegs);
    dog.def("hasWings", &Dog::hasWings);
    dog.def("name", &Dog::name);
    dog.def("bark", &Dog::bark);

    py::class_<Balto, PyBalto, Balto::Ptr, Dog> balto(module, "Balto");
    balto.def(py::init<>());
    balto.def("typeName", &Balto::typeName);
    balto.def("hasLegs", &Balto::hasLegs);
    balto.def("hasWings", &Balto::hasWings);
    balto.def("name", &Balto::name);
    balto.def("bark", &Balto::bark);

    py::class_<Cage> cage(module, "Cage");
    cage.def(py::init<>());
    cage.def("addAnimal", &Cage::addAnimal);
    cage.def("numAnimals", &Cage::numAnimals);
    cage.def("__getitem__", (Animal* (Cage::*)(const size_t)) &Cage::operator[] );
    cage.def("__getitem__", (const Animal* (Cage::*)(const size_t) const) &Cage::operator[] );

    py::class_<AnimalFactory> animal_factory(module, "AnimalFactory");
    animal_factory.def(py::init<>());
    animal_factory.def("count", &AnimalFactory::count);
    animal_factory.def("isRegistered", &AnimalFactory::isRegistered);
    animal_factory.def("registerAnimal", 
        (bool (AnimalFactory::*)(const std::string&, py::object)) 
        &AnimalFactory::registerAnimal);
    animal_factory.def("createAnimal", &AnimalFactory::createAnimal);//, py::return_value_policy::take_ownership);
    animal_factory.def("createScriptedAnimal", &AnimalFactory::createScriptedAnimal);
}