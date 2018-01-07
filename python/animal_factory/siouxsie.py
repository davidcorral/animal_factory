from animal_factory import Animal

class Siouxsie(Animal):

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

    def meow(self):
        return 'meow'

    @staticmethod
    def creator():
        return Siouxsie()
