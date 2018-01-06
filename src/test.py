from animal_factory import Animal
from animal_factory import Dog
from animal_factory import Cage

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
	def create():
		return Cat()

if __name__ == '__main__':	

	# register animal
	cage = Cage()
	cage.registerAnimal('cat', Cat.create)

	# create new animal
	cat = cage.createAnimal('cat')
	assert(cat.typeName() == "cat")
	assert(cat.hasLegs() == True)
	assert(cat.hasWings() == False)
	assert(cat.name() == 'Siouxsie')

	dog = cage.createAnimal('dog')
	assert(dog.typeName() == "dog")	
	assert(dog.hasLegs() == True)
	assert(dog.hasWings() == False)
	assert(dog.name() == 'Balto')
