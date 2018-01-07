import unittest

from animal_factory import Animal
from animal_factory import Dog
from animal_factory import Cage
from animal_factory import AnimalFactory
from animal_factory.cat import Cat

class TestFactory(unittest.TestCase):

    #@unittest.skip('...')
    def test_factory(self):

        factory = AnimalFactory()

        # factory comes with a builtin dog
        self.assertEqual(factory.count(), 1)
        self.assertTrue(factory.isRegistered('dog'))

        # add cat
        self.assertTrue(factory.registerAnimal('cat', Cat.creator))
        self.assertTrue(factory.isRegistered('cat'))
        self.assertEqual(factory.count(), 2)

        # create cat
        cat = factory.createAnimal('cat')
        self.assertEqual(cat.typeName(), "cat")
        self.assertTrue(cat.hasLegs())
        self.assertFalse(cat.hasWings())
        self.assertEqual(cat.name(), 'Siouxsie')

        # create dog
        dog = factory.createAnimal('dog')
        self.assertEqual(dog.typeName(),"dog")
        self.assertTrue(dog.hasLegs())
        self.assertFalse(dog.hasWings())
        self.assertEqual(dog.name(), 'Balto')
        #dog.bark()

        # cage the animals
        cage = Cage()
        cage.addAnimal(cat)
        cage.addAnimal(dog)
        self.assertEqual(cage.numAnimals(), 2)

    def test_dog(self):

        factory = AnimalFactory()
        self.assertTrue(factory.isRegistered('dog'))

        dog = factory.createAnimal('dog')

        # NOTE: this is less than ideal
        self.assertFalse(isinstance(dog, Dog))
        self.assertTrue(isinstance(dog.asDog(), Dog))
        self.assertEqual(dog.asDog().bark(), 'woof')
        
if __name__ == '__main__':
    unittest.main()
    