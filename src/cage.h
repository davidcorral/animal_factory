#include <memory>
#include <map>
#include <vector>
#include <string>

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "animal.h"

class Cage
{
public:

    Cage()
    {
        // register built-in
        registerAnimal("dog", Balto::creator);
    };

    void
    registerAnimal(const std::string& animal_type, py::object creator)
    {
        m_registered_scripted_animals[animal_type] = creator;
    };

    void
    registerAnimal(const std::string& animal_type, Animal::Ptr (*creator)(void) )
    {
        m_registered_animals[animal_type] = creator;
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

    // -------------------------------------------------------------------------
    /// Number of animals in cage
    size_t
    numAnimals() const { return m_animals.size(); };    
    /// Adds animal to cage
    void
    addAnimal( Animal::Ptr animal ) { m_animals.push_back(animal); };
    /// Gets animal from cage
    Animal*
    getAnimal( const size_t index ) { return m_animals[index].get(); };
    
private:
    std::map<std::string, Animal::Ptr (*)(void) > m_registered_animals;
    std::map<std::string, py::object > m_registered_scripted_animals;
    std::vector< Animal::Ptr >         m_animals;
};
