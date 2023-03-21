# rubix-cube

## Description

https://github.com/UWTRubiksSolver/RubiksAlgorithm

Robot Rubik Cube Solver for University of Washington Tacoma IEEE club project 2023. Iterating upon pervious years efforts trying to improve the performance and abilities of the solver.

The frontend controls all Arduino actions including motors, lights, and cameras. To control motors we fetch a string from the Serial that contains the moveSet written by the backend that contains the list of moves to solve the cube. After setting up all the stepper and directional pins for the 6 motors it loops through all moves until completion.

The backend solves the cube by taking in the cubes state from a text file then solves the cube using a method. For each step in the method we can use algorithims to easily find the solve order. For each move we push the choice to a vector to store the solve order. After completeion the solve order is output to Serial port.

## Problems

1. Solving Method

Previous method seems to be the [Beginners Method](https://ruwix.com/the-rubiks-cube/how-to-solve-the-rubiks-cube-beginners-method/) which is a simple but inefficent solving method. [CFOP](https://jperm.net/3x3/cfop) can can dramatically reduce move count but will require more memory for algorithms.

2. Unclean code

Readability is vital for maintenance and the previous project is difficult to follow with long if chains, strange cube interfacing, and deep nestings.

3. Memory

The entire project runs locally on the Arduino so having efficent data structures is important so that there is space for algorithims.

4. Input

Currently the starting state of the cube needs to be manually inputted, using camera(s) could be a great feature to add.

## Resources

Previous: https://github.com/UWTRubiksSolver/RubiksAlgorithm

Notation: https://jperm.net/3x3/moves

Method: https://jperm.net/3x3/cfop
