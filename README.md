# Animal Factory - pybind11 example

Simple factory example with pybind11, using inheritance and virtual functions.
The wrapped classes can be extended and added to factory from python.

## Dependencies ##
+ [pybind11](https://github.com/pybind/pybind11)

## How to Build ##
```bash
mkdir build
cd build
cmake ..
make install
```

## Run the tests ##
    cd dist
    python test.py
