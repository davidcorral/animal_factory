#pragma once

#include <memory>
#include <vector>

#include "animal.h"

class Cage
{
public:

    size_t
    numAnimals() const { return m_animals.size(); };    
    ///
    void
    addAnimal( Animal::Ptr animal ) { m_animals.push_back(animal); };
    ///
    Animal&
    operator[](const size_t index) { return *m_animals[index]; };
    ///
    const Animal&
    operator[](const size_t index) const { return *m_animals[index]; };
    
private:
    std::vector< Animal::Ptr > m_animals;
};
