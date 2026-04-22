# OpenMP HPC Assignments
This repository contains implementations of fundamental parallel programming concepts using OpenMP.

## Topics Covered
- Parallel for loops
- Reduction operations
- Race condition debugging
- Numerical integration (Pi computation)
- Iterative solvers (Jacobi method)
- Optimization (Least Squares with Gradient Descent)
- Parallel image processing (PPM animation)

## Structure
1. BugReduction – Fixing reduction race condition
2. BugParFor – Correct parallel loop usage
3. Pi – Parallel numerical integration
4. Axisb (Jacobi) – Solving linear systems
5. LeastSquares – Linear regression using gradient descent
6. CarAnimation – Parallel image shifting and animation

## Compilation
Make sure you have GCC with OpenMP support installed.

    make        # build all
    make pi     # build specific target
    make clean  # remove binaries

## Requirements
- GCC with OpenMP support (`gcc --version`)
- G++ for C++ targets
- Linux/WSL (recommended)

## Usage
    ./bugreduction
    ./pipar
    ./axisb
    ./carpar        # requires car.ppm in 06_CarAnimation/

## Notes
- `car.ppm` must be placed in `06_CarAnimation/` before running the car target