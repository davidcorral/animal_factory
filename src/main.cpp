#include <memory>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

template <typename DogBase, typename Base>
class TPyDog : public DogBase
{
public:
    using DogBase::DogBase; // Inherit constructors
    
    std::string 
    typeName() const override { PYBIND11_OVERLOAD( std::string, DogBase, typeName ); };

    bool 
    hasLegs() const override { PYBIND11_OVERLOAD_PURE( bool,  DogBase,  hasLegs ); };

    bool 
    hasWings() const override { PYBIND11_OVERLOAD_PURE( bool, DogBase,  hasWings ); };

    std::string
    name() const override { PYBIND11_OVERLOAD_PURE( std::string, DogBase,  name ); };

    static void
    createClass(py::module& class_module, const std::string& class_name)
    {
        py::class_<DogBase, TPyDog<DogBase, Base>, std::shared_ptr<DogBase>, Base> dog_base(class_module, class_name.c_str());
        dog_base.def(py::init<>());
        dog_base.def("typeName", &DogBase::typeName);
        dog_base.def("hasLegs", &DogBase::hasLegs);
        dog_base.def("hasWings", &DogBase::hasWings);
        dog_base.def("name", &DogBase::name);
        dog_base.def("bark", &DogBase::bark);
    }
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
    
    TPyDog<Dog, Animal>::createClass(module, "Dog");
    TPyDog<Balto, Dog>::createClass(module, "Balto");

    py::class_<Cage> cage(module, "Cage");
    cage.def(py::init<>());
    cage.def("addAnimal", &Cage::addAnimal);
    cage.def("numAnimals", &Cage::numAnimals);
    cage.def("__getitem__", (Animal* (Cage::*)(const size_t)) &Cage::operator[] );
    cage.def("__getitem__", (const Animal* (Cage::*)(const size_t) const) &Cage::operator[] );
    cage.def("animals", &Cage::animals);
    
    py::class_<AnimalFactory> animal_factory(module, "AnimalFactory");
    animal_factory.def(py::init<>());
    animal_factory.def("numRegisteredAnimals", &AnimalFactory::numRegisteredAnimals);
    animal_factory.def("isRegistered", &AnimalFactory::isRegistered);
    animal_factory.def("registerAnimal", 
        (bool (AnimalFactory::*)(const std::string&, py::object)) 
        &AnimalFactory::registerAnimal);
    animal_factory.def("createAnimal", &AnimalFactory::createAnimal);//, py::return_value_policy::take_ownership);
    animal_factory.def("createScriptedAnimal", &AnimalFactory::createScriptedAnimal);
}