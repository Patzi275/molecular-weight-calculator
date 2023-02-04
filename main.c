#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "molecular_weight.h"

#define MAX 25

void test_element_weight() {
    assert(fabs(element_weight("H") - 1.0079) < 0.001);
    assert(fabs(element_weight("Na") - 22.9897) < 0.001);
    assert(element_weight("WWW") == -1);
    assert(element_weight("eL") == -1);
}

void test_molecular_weight() {
    assert(fabs(molecular_weight("H2O") - 18.015) < 0.01);
    assert(fabs(molecular_weight("NaCl") - 58.44) < 0.01);
    assert(fabs(molecular_weight("C6H12O6") - 180.18) < 0.01);
    assert(fabs(molecular_weight("C6(H12O6)4") - 504.522) < 0.01);
    assert(molecular_weight("H3(O2") == -1);
    assert(molecular_weight("4Sa") == -1);
}

int main()
{
    //test_element_weight();
    //test_molecular_weight();
    
    int choice;
    float mw;
    char formula[MAX];

    do
    {
        printf("Enter the formula:\n");
        printf("--> ");
        scanf("%s", formula);
        mw = molecular_weight(formula);
        if (mw == -1)
            printf("Invalid !");
        else
            printf("The molecular weight of %s is %f g/mol\n\n", formula, mw);
        
    } while (1);

    return 0;
}
