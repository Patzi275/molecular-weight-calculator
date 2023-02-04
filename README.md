# Molecular Weight Calculator 
This repository contains a C program that calculates the molecular weight of a chemical formula. The program takes a string input representing a chemical formula and returns the corresponding molecular weight.
> Please note that the program does not check the validity of the chemical formula from a chemistry perspective (e.g., number of atoms).

## Usage  
The program uses the `molecular_weight` function to calculate the molecular weight of a chemical formula. The function takes a character array as an input, where the character array represents the chemical formula.

The program also uses a helper function, `element_weight`, to retrieve the weight of an element from the database.txt file.

## Files  
The repository contains the following files:
- **molecular_weight.h**: header file that declares the molecular_weight and element_weight functions.
- **molecular_weight.c**: source file that implements the molecular_weight and element_weight functions.
- **database.txt**: text file that contains the weights of elements in the periodic table.
- **main.c**: example file that demonstrates how to use the molecular_weight function.

## Error Handling
In the case of an error, the program prints an error message to the standard output and returns -1.   
Possible error scenarios are:
- Unable to open the database.txt file.
- The element symbol or subformula is not found in the database.txt file.

## Limitations
The program does not check the validity of the chemical formula from a chemistry perspective (e.g., number of atoms).
