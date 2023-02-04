#include "masse_molaire.h"
#define erreur(x) printf("ERREUR : "); printf(x); printf("\n")

/*
Exemple of formula:
	- C4H10
	- C2(Cl3H10)2
	- He20((HClO2)3)100Na
*/


/**
* To get the element weight from the file database.
* @param element a character table that contain the element
* @return The weight the element is founded, and -1 else
*/
float element_weight(char* element)
{
	FILE* file = fopen("database.txt", "r");
	float weight = 0;
	char name[3] = "___";
	while(fscanf(file, "%s %f", name, &weight) != EOF){
		if(strcmp(name, element) == 0){
			fclose(file);
			return weight;
		}
	}
	return -1;
}

/**
* Used to calculate a formula weight.
* @param formula a character table that contain the formula
* @return The molecular weight of the formula or -1 if these is an error
*/
float moleculdar_weight(char* formular)
{

	char atome[3] = ""; //important d'initiliser sinon valeur aleatoire parmi les char qui le compose

	int i ,	           //itérareur
		j = 0,        //itérateur substituant i
		longueur = strlen(formular), //taille de la chaine
		mul = 1;                    //Occurence de la molécule

	float masse_atomique = 0,
		masse = 0;

	int nbrpo = 0,                //nombre de parentheses ouvertes
		nbrpf = 0,               //nombre de parentheses fermées
		molecule = 0;           //Pour verifier que la chaine contient une molécule

	for(i=0; i<longueur ; i++)
	{
		if(formular[i]=='(')
			nbrpo++;
		else if(formular[i]==')')
			nbrpf++;
	}

	if(nbrpo != nbrpf && nbrpo != 0)
		return 0;

	for(i = 0; i < longueur; i++)
	{
		atome[1] = NULL;
		mul = 1;
		j = i;
		molecule = 0;

		if(isupper(formular[i]))
		{

			if(islower(formular[i+1]))
			{
				j = i;
				atome[0] = formular[j++];
				atome[1] = formular[j];
				if(isdigit(formular[j+1]))
				{
					j++;
                    //formular[i] est apparement une valeur et non le pointeur / seul le tableau au complet constitue le pointeur :
					mul = atof(&formular[j]);
				}
			}
			else if (!islower(formular[i+1]))
			{
				j = i;
				atome[0] = formular[j];
				if(isdigit(formular[j+1]))
				{
					j++;
					mul = atof(&formular[j]);
				}
			}
		}
		else if(formular[i] == '(' )
		{
			j = i+1;
			int k = 1;
			int z = 0;
			char formuleI[10] = "";

			while(k != 0)
			{
				formuleI[z++] = formular[j++];
				if(formular[j] == '(') k++;
				else if (formular[j] == ')') k--;
			}

			masse_atomique = mmm(formuleI);
			molecule = 1;
			if(isdigit(formular[j+1]))
			{
				j++;
				mul = atof(&formular[j]);
			}
		}
		i = j;

		if(molecule == 0)
			masse_atomique = mma(&atome);

		if(masse_atomique == 0)
			return 0;

		masse += masse_atomique * mul;
	}

	return masse;
}

/*****************************************************************************************/
