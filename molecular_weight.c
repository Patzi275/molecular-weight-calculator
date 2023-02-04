#include "molecular_weight.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ERR_MESSAGE(x) printf("ERREUR : %s\n", x)

float element_weight(char* element)
{
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        ERR_MESSAGE("Unable to open database.txt");
        return -1;
    }
    
    float weight = 0;
    char name[3] = "___";
    while(fscanf(file, "%s %f", name, &weight) != EOF){
        if(strcmp(name, element) == 0){
            fclose(file);
            return weight;
        }
    }
    fclose(file);
    return -1;
}

/**
 * Get the weight of an element from the database file
 * 
 * @param element: a character array containing the element symbol
 * @return the weight of the element, or -1 if not found
 */
float molecular_weight(char* formula)
{
    int formula_length = strlen(formula),  // length of the formula string
        mul = 1,                           // multiplicity of an element in the formula
        i = 0, j = 0;                      // iterators
    char element[3] = "";                  // variable to store an element symbol
    float mol_weight = 0,            // variable to store the final result
        ele_weight = 0;                // variable to store the weight of an element
    
    // loop through the formula string
    while (i < formula_length) {
        j = i;
        mul = 1;
        memset(element, 0, sizeof element);
        
        // handle element symbols with length 2 (e.g., Na)
        if (islower(formula[j + 1])) {
            element[0] = formula[j++];
            element[1] = formula[j];
        } else {
            element[0] = formula[j];
        }
        
        // handle elements inside parentheses (e.g., (Na)2)
        if (formula[j] == '(') {
            int k = 1;
            int z = 0;
            char subformula[10] = "";
            while (k != 0) {
                subformula[z++] = formula[++j];
                if (formula[j] == '(') k++;
                else if (formula[j] == ')') k--;
            }
            ele_weight = molecular_weight(subformula);
            if (ele_weight == -1) {
                char msg[30];
                sprintf(msg, "\"%s\" is not in the database", subformula);
                ERR_MESSAGE(msg);
            }
            i = j;
        } else {
            ele_weight = element_weight(element);
        }
        
        // handle multiplicities (e.g., Na2)
        if (isdigit(formula[j + 1])) {
            mul = (int) strtol(&formula[j + 1], NULL, 10);
        }
        
        // add the weight of the current element to the molecular weight
        mol_weight += mul * ele_weight;
        
        // move to the next element in the formula
        i = j + 1;
    }
    
    return mol_weight;
}
