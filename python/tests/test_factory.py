import logging
import unittest

from animal_factory import Animal
from animal_factory import Dog
from animal_factory import Balto
from animal_factory import Cage
from animal_factory import AnimalFactory
from animal_factory.siouxsie import Siouxsie

class TestFactory(unittest.TestCase):

    # @unittest.skip('...')
    def test_factory(self):

        factory = AnimalFactory()

        # factory comes with a builtin dog called balto
        self.assertEqual(factory.count(), 1)
        self.assertTrue(factory.isRegistered('balto'))

        # add siouxsie
        self.assertTrue(factory.registerAnimal('siouxsie', Siouxsie.creator))
        self.assertTrue(factory.isRegistered('siouxsie'))
        self.assertEqual(factory.count(), 2)

        # create siouxsie
        siouxsie = factory.createScriptedAnimal('siouxsie')
        self.assertTrue(isinstance(siouxsie, Animal))
        self.assertTrue(isinstance(siouxsie, Siouxsie))
        self.assertEqual(siouxsie.typeName(), "cat")
        self.assertTrue(siouxsie.hasLegs())
        self.assertFalse(siouxsie.hasWings())
        self.assertEqual(siouxsie.name(), 'Siouxsie')
        self.assertEqual(siouxsie.meow(), 'meow')

        # create dog
        balto = factory.createAnimal('balto')
        self.assertTrue(isinstance(balto, Animal))
        self.assertTrue(isinstance(balto, Dog))
        self.assertTrue(isinstance(balto, Balto))
        self.assertEqual(balto.typeName(),"dog")
        self.assertTrue(balto.hasLegs())
        self.assertFalse(balto.hasWings())
        self.assertEqual(balto.name(), 'Balto')
        self.assertEqual(balto.bark(), 'woof')

        # cage the animals
        cage = Cage()
        cage.addAnimal(siouxsie)
        cage.addAnimal(balto)
        self.assertEqual(cage.numAnimals(), 2)

    # @unittest.skip('...')
    def test_cat(self):
        
        siouxsie = Siouxsie()
        self.assertEqual(siouxsie.typeName(), "cat")
        self.assertTrue(siouxsie.hasLegs())
        self.assertFalse(siouxsie.hasWings())
        self.assertEqual(siouxsie.name(), 'Siouxsie')
        self.assertEqual(siouxsie.meow(), 'meow')
        
    # @unittest.skip('...')
    def test_dog(self):

        factory = AnimalFactory()
        self.assertTrue(factory.isRegistered('balto'))

        balto = factory.createAnimal('balto')
        self.assertTrue(isinstance(balto, Dog))
        self.assertTrue(hasattr(balto, 'bark'))
        self.assertEqual(balto.bark(), 'woof')
        
if __name__ == '__main__':
    unittest.main()
    