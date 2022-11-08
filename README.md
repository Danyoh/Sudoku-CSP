# CSPSudoku
Create a CSP model of the puzzle Sudoku  
## Introduction
We will use the AC-3 algorithm to solve the puzzle Sudoku.  
## Problem Definition
Variables: 81 cells of the grid
Domains: 1-9
Constraints:
* Each cell must have a value
* Each row must not have the same values
* Each column must not have the same values
* Each 3x3 square must not have the same values
Binary constraints:
* Two cells in the same row, column or 3x3 square cannot have the same value

### Input
The input is a sudoku puzzle file with the name `input.txt` in the same directory as `sudoku.cpp`.
