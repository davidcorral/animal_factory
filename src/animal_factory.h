#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "animal.h"
#include "balto.h"

// -----------------------------------------------------------------------------

class AnimalFactory
{
public:

    AnimalFactory()
    {
        // add built-in animal
        registerAnimal("balto", Balto::creator);
    };

    size_t
    count() const 
    { 
        return m_registered_animals.size() + 
               m_registered_scripted_animals.size();
    };

    bool
    isRegistered(const std::string& animal_name) const
    {
        return (m_registered_animals.count(animal_name) ||
                m_registered_scripted_animals.count(animal_name));
    };

    bool
    registerAnimal(const std::string& animal_name, py::object creator)
    {
        if (isRegistered(animal_name))
            return false;

        m_registered_scripted_animals[animal_name] = creator;
        return true;
    };

    bool
    registerAnimal(const std::string& animal_name, Animal::Ptr (*creator)(void) )
    {
        if (isRegistered(animal_name))
            return false;

        m_registered_animals[animal_name] = creator;
        return true;
    };

    Animal::Ptr
    createAnimal(const std::string& animal_name)
    {
        if (m_registered_animals.count(animal_name))
        {
            return m_registered_animals[animal_name]();
        }

        return nullptr;
    };

    py::object
    createScriptedAnimal(const std::string& animal_name)
    {
        if (m_registered_scripted_animals.count(animal_name))
        {
            return m_registered_scripted_animals[animal_name]();
        };
        return py::object();
    };

private:
    std::map<std::string, Animal::Ptr (*)(void) > m_registered_animals;
    std::map<std::string, py::object > m_registered_scripted_animals;
};
