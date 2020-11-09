# AccelerationEvalTest

This small project demonstrates the anticipated algorithm to evaluate acceleration samples according to
the customer's needs.

## Build dependencies

- C and C++ compiler (Ubuntu: sudo apt intall build-dependencies)
- CMake (Ubuntu: sudo apt install cmake)

## Build instructions (without unittests)

1. enter the directory of this source tree
2. run CMake:
```
cmake .
```
3. build the binaries:
```
make
```
4. run the binary:
```
./src/acceleration-eval-test
```

The expected output shall be this:
```
Initializing with first sample, rising edge on latch enable:
  currentSample=[x= 0.00,y= 0.00,z= 1.00]
  maxPlaneYZ=   [x= 0.00,y= 0.00,z= 1.00]
  maxPlaneXZ=   [x= 0.00,y= 0.00,z= 1.00]
  maxPlaneXY=   [x= 0.00,y= 0.00,z= 1.00]
Adding more samples while latch is enabled...
Current state:
  currentSample=[x= 0.00,y= 0.00,z= 1.10]
  maxPlaneYZ=   [x=-0.40,y=-0.21,z= 0.90]
  maxPlaneXZ=   [x=-0.40,y=-0.21,z= 0.90]
  maxPlaneXY=   [x= 0.00,y= 0.00,z= 1.10]
Adding more samples while latch is NOT enabled...
Current state:
  currentSample=[x= 0.50,y=-0.40,z= 0.80]
  maxPlaneYZ=   [x=-0.40,y=-0.21,z= 0.90]
  maxPlaneXZ=   [x=-0.40,y=-0.21,z= 0.90]
  maxPlaneXY=   [x= 0.00,y= 0.00,z= 1.10]
Initializing second measurement cycle with first sample, rising edge on latch enable:
  currentSample=[x= 0.20,y=-0.10,z= 0.94]
  maxPlaneYZ=   [x= 0.20,y=-0.10,z= 0.94]
  maxPlaneXZ=   [x= 0.20,y=-0.10,z= 0.94]
  maxPlaneXY=   [x= 0.20,y=-0.10,z= 0.94]
Adding more samples while latch is enabled...
Current state:
  currentSample=[x= 0.00,y= 0.00,z= 1.00]
  maxPlaneYZ=   [x= 0.20,y=-0.10,z= 0.94]
  maxPlaneXZ=   [x= 0.20,y=-0.10,z= 0.94]
  maxPlaneXY=   [x= 0.00,y= 0.00,z= 1.00]
```

## Build instructions (with unittests)

1. enter the directory of this source tree
2. run CMake:
```
cmake -DWITH_UNITTESTS=True .
```
3. build the binaries:
```
make gtest
```
4. run the binary:
```
./gtest
```

The expected output shall be this:
```
Running main() from gtest_main.cc
[==========] Running 9 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 9 tests from AccelerationEvaluationTest
[----------] 9 tests from AccelerationEvaluationTest (0 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 9 tests.
```
