from animal_factory import Animal
from animal_factory import Dog
from animal_factory import Cage
from animal_factory import AnimalFactory

class Cat(Animal):

	def __init__(self):
		Animal.__init__(self) # Without this, undefined behavior may occur if the C++ portions are referenced.
	
	def typeName(self):
		return 'cat'	

	def hasLegs(self):
		return True
	def hasWings(self):
		return False
	def name(self):
		return 'Siouxsie'

	@staticmethod
	def creator():
		return Cat()

if __name__ == '__main__':	

	# register animal
	animal_factory = AnimalFactory()
	animal_factory.registerAnimal('cat', Cat.creator)
	assert(animal_factory.count() == 2)
	
	# create new animals
	cat = animal_factory.createAnimal('cat')
	assert(cat.typeName() == "cat")
	assert(cat.hasLegs() == True)
	assert(cat.hasWings() == False)
	assert(cat.name() == 'Siouxsie')

	dog = animal_factory.createAnimal('dog')
	assert(dog.typeName() == "dog")	
	assert(dog.hasLegs() == True)
	assert(dog.hasWings() == False)
	assert(dog.name() == 'Balto')

	# cage the animals
	cage = Cage()
	cage.addAnimal(cat)
	cage.addAnimal(dog)
	assert(cage.numAnimals() == 2)
	
	for i in range(cage.numAnimals()):
		animal = cage[i]
		