#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "animal.h"

// -----------------------------------------------------------------------------

class AnimalFactory
{
public:

    AnimalFactory()
    {
        // add built-in animal
        registerAnimal("dog", Balto::creator);
    };

    size_t
    count() const 
    { 
        return m_registered_animals.size() + 
               m_registered_scripted_animals.size();
    };

    bool
    isRegistered(const std::string& animal_type) const
    {
        return (m_registered_animals.count(animal_type) ||
                m_registered_scripted_animals.count(animal_type));
    };

    bool
    registerAnimal(const std::string& animal_type, py::object creator)
    {
        if (isRegistered(animal_type))
            return false;

        m_registered_scripted_animals[animal_type] = creator;
        return true;
    };

    bool
    registerAnimal(const std::string& animal_type, Animal::Ptr (*creator)(void) )
    {
        if (isRegistered(animal_type))
            return false;

        m_registered_animals[animal_type] = creator;
        return true;
    };

    py::object
    createAnimal(const std::string& animal_type)
    {
        if (m_registered_animals.count(animal_type))
        {
            return py::cast(m_registered_animals[animal_type]());
        }
        else if (m_registered_scripted_animals.count(animal_type))
        {
            return m_registered_scripted_animals[animal_type]();
        };

        return py::object();
    };

private:
    std::map<std::string, Animal::Ptr (*)(void) > m_registered_animals;
    std::map<std::string, py::object > m_registered_scripted_animals;
};
