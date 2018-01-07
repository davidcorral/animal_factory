import os
import unittest

if __name__ == '__main__':
      
    this_dir  = os.path.dirname(__file__)
    tests_dir = os.path.join(this_dir, 'tests')

    # create suite(s)
    loader = unittest.TestLoader()
    test_suite = loader.discover(tests_dir)

    # run tests
    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(test_suite)
    