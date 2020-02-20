//Fait par Lopes Michaël et Garic Luca
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//Prototypes Fonction
void triTableauDecroissant(int n, int Tache[]);
int bornMax (int Tache[], int n);
float bornMoy (int Tache[], int m, int n);
float ratioTotal (int Tache[], int n, int result, int m);
void affichage (int Tache[], int n, int resultLSA, int resultLPT, int m);
int lsa (int Tache[], int Machine[], int m, int n);
int lpt (int Tache[], int Machine[],int m, int n);
int valeurRandom (int min, int max);
void mode1 (int Tache[], int m, int Machine[], int n);
void mode2 (int Tache[], int m, int Machine[], int n);
void mode3 (int m, int n, int k, int min, int max, int Tache[], int Machine[]);

//Algorithme qui permet de résoudre le problème Min Makespan
int main () {
	//Lexique
	int rep = 0;
	int stop = 0;
	int m; //Nb machine
	int Tache[500000]; //Tableau des tâches
	int n; //Nb tâche
	int k; //Nb exemple différent
	int min; //Durée min des tâches
	int max; //Durée max des tâches
	int Machine[500000]; //Tableau des machines

	//Corps de l'algorithme
	system("clear");
	printf("Bienvenue sur le programme de Michaël Lopes et Luca Garic, permettant de résoudre le problème Min Makespan. \n");
	printf("Ce programme utilise 2 algorithmes. Il y a le LSA(List Scheduling Algorithm) et le LPT(Largest Processing Time). \n");
	printf("======================================================Menu====================================================== \n");
	printf("Veuiller séléctionner votre choix : (1, 2, 3 ou 4). \n");
	printf("(1) : Mode 1. \n");
	printf("(2) : Mode 2. \n");
	printf("(3) : Mode Random. \n");
	printf("(4) : Quitter. \n");

	do {
		scanf("%d", &rep);
		switch (rep) {
			case 1 :
				//Fonction de mode 1
				printf("Vous avez choisi le mode 1. \n");
				do {
					printf("Veuillez saisir un nombre de machine (minimum 1). \n");
					scanf("%d", &m);
				} while (m < 1);
				mode1(Tache, m, Machine, n);
			break;

			case 2 :
				//Fonction de mode 2
				printf("Vous avez choisi le mode 2. \n");
				do {
					printf("Veuillez saisir un nombre de machine (minimum 1). \n");
					scanf("%d", &m);
				} while (m < 1);
				mode2(Tache, m, Machine, n);
			break;

			case 3 :
				//Fonction random de mode 3
				printf("Vous avez choisi le mode 3 (mode random). \n");
				do {
					printf("Veuillez saisir un nombre de machine (minimum 1). \n");
					scanf("%d", &m);
				} while (m < 1);
				do {
					printf("Veuillez saisir un nombre de tâche (minimum à 1). \n");
					scanf("%d", &n);
				} while (n < 1);
				do {
					printf("Veuillez saisir le nombre d'exemple différent (minimum 1). \n");
					scanf("%d", &k);
				} while (k < 1);
				do {
					do {
						printf("Veuillez saisir la borne minimum (minimum 1). \n");
						scanf("%d", &min);
					} while (min < 1);
					do {
						printf("Veuillez saisir la borne maximum (minimum 1). \n");
						scanf("%d", &max);
					} while (max < 1);
				} while (min > max);
				mode3(m, n, k, min, max, Tache, Machine);
			break;

			case 4 :
				printf("\n Merci et à la prochaine ! ^-^ \n");
			break;
		}
		stop = 1;
	} while (rep < 0 || rep > 4 || stop == 0);
}

//Réalisation du mode 1
void mode1 (int Tache[], int m, int Machine[], int n) {
	for (int i = 0; i < (m * (m - 1)); i++) {
		Tache[i] = 1; //Toute les tâches à 1 sauf la dernière
	}
	Tache[m * (m - 1)] = m; //La dernière tâche correspond au nombre de machine
	/*Texte de vérification
	printf("MODE 1 \n");
	for (int i = 0; i < (m * (m - 1) + 1); i++) {
		printf("La tache n°%d à une durée de %d. \n", i + 1, Tache[i]);
	}*/
	n = m * (m - 1) + 1; //Calcul du nombre de tâche
	//Affichage LSA et LPT
	int resultLSA = lsa(Tache, Machine, m, n);
	int resultLPT = lpt(Tache, Machine, m, n);
	affichage(Tache, n, resultLSA, resultLPT, m);
}

//Réalisation du mode 2
void mode2 (int Tache[], int m, int Machine[], int n) {
	int j = 1;
	for (int i = 0; i < 2 * m + 1; i++) {
		if (i < 3) { //Les 3 premières tâches prennent la valeur de m
			Tache[i] = m;
		} else { //Puis les 2 tâches suivant prennent la valeur m + 1
			Tache[i] = m + j;
			i = i + 1;
			Tache[i] = m + j;
			j = j + 1;
		}
	}
	/*Texte de vérification
	for (int i = 0; i < 2 * m + 1; i++) {
		printf("La tâche n°%d à une valeur de %d. \n", i + 1, Tache[i]);
	}*/
	n = 2 * m + 1; //Calcul du nombre de tâche
	//Affichage LSA et LPT
	int resultLSA = lsa(Tache, Machine, m, n);
	int resultLPT = lpt(Tache, Machine, m, n);
	affichage(Tache, n, resultLSA, resultLPT, m);
}

///////////////////////////////////EN PLEIN DEVELOPPEMENT///////////////////////////////////
//Réalisation du mode 3
void mode3 (int m, int n, int k, int min, int max, int Tache[], int Machine[]) {
	int j = 1;
	int i;
	srand(time(NULL)); //Initialisation de rand
	float sommeRatioLSA = 0;
	float sommeRatioLPT = 0;
	float ratioLSA = 0;
	float ratioLPT = 0;
	int resultLSA = 0;
	int resultLPT = 0;
	float RatioLSATotal = 0;
	float RatioLPTTotal = 0;

	//Définir le nom du fichier
	char titre[100];
	printf("Veuillez saisir un nom de fichier (sans l'extension et max 100) : \n");
	scanf("%s", titre);
	char *extension = ".txt";   
	strcat(titre, extension); //Concaténer le nom saisi par utilisateur avec l'extension*/

	//Création et ouverture du fichier
	FILE* fichier = NULL;
	fichier = fopen(titre, "w+");

	for (j = 1; j <= k; j++) { //Boucle parcourant le nb d'exemple différent
		for (i = 0; i < n; i++) {
			Tache[i] = valeurRandom(min, max); //Génere une valeur comprise entre min et max
		}
		/*printf("Pour %d machines, voici l'exemple n°%d. \n", m, j);
		for (i = 0; i < n; i++) {
			printf("La tâche n°%d à une durée de %d. \n", i + 1, Tache[i]);
		}*/
		resultLSA = lsa(Tache, Machine, m, n);
		resultLPT = lpt(Tache, Machine, m, n);
		ratioLSA = ratioTotal(Tache, n, resultLSA, m);
		//printf("TEST Ratio LSA n°%d est : %f \n", i, ratioLSA);
		ratioLPT = ratioTotal(Tache, n, resultLPT, m);
		//printf("TEST Ratio LPT n°%d est : %f \n", i, ratioLPT);
		sommeRatioLSA = sommeRatioLSA + ratioLSA;
		//printf("TEST Ratio LSA TOTAL n°%d est : %f \n", i, sommeRatioLSA);
		sommeRatioLPT = sommeRatioLPT + ratioLPT;
		//printf("TEST Ratio LPT TOTAL n°%d est : %f \n", i, sommeRatioLPT);

		//Ecriture des informations à chaque boucle
		int bornInfMax = bornMax(Tache, n); //Récupération de la borne max
		float bornInfMoy = bornMoy(Tache, m, n); //Récupération de la borne moy
		fprintf(fichier,"Exemple N° %d \n", j);
		fprintf(fichier,"Voici les résultats attendu :\n");
		fprintf(fichier,"Borne inférieur ''maximum'' = %d \n", bornInfMax);
		fprintf(fichier,"Borne inférieur ''moyenne'' = %f \n", bornInfMoy);
		fprintf(fichier,"Résultat LSA = %d \n", resultLSA);
		fprintf(fichier,"Somme Ratio LSA total = %f \n", sommeRatioLSA);
		fprintf(fichier,"Résultat LPT = %d \n", resultLPT);
		fprintf(fichier,"Somme Ratio LPT total = %f \n", sommeRatioLPT);
		fprintf(fichier, "================================================= \n");
	}

	//Calcul du ratio total LSA et LPT
	RatioLSATotal = sommeRatioLSA / (float)k;
	RatioLPTTotal = sommeRatioLPT / (float)k;
	//printf("RatioLSATotal : %f, RatioLPTTotal : %f \n", RatioLSATotal, RatioLPTTotal);

	//Ecriture des moyennes total
	fprintf(fichier,"Ratio moyen LSA : %f \n", RatioLSATotal);
	fprintf(fichier,"Ratio moyen LPT : %f \n", RatioLPTTotal);
	fclose(fichier); //Fermeture du fichier

}

//Génére nombre entre borne min et max pour mode random
int valeurRandom (int min, int max) {
	int r = 0;
	r = rand()%((max + 1) - min) + min;
	return r;
}

//Algorithme LSA
int lsa (int Tache[], int Machine[], int m, int n) {
	for (int i = 0; i < m; i++) { //Permet de remettre le tableau des machines à 0
		Machine[i] = 0;
	}
	for (int i = 0; i < n; i++) { //i avance jusqu'au nb total de tâche
		int min = 0;
		for (int j = min + 1; j < m; j++) { //j avance jusqu'au nb total de machines
			if (Machine[j] < Machine[min]) { //Determine l'indice de la valeur la + petite du tab
				min = j;
			}
		}
		Machine[min] = Machine[min] + Tache[i]; //Ajoute la tâche à la valeur de l'indice le + petit 
	}
	/*Texte de vérification
	printf("MODE LSA puis LPT\n");
	for (int j = 0; j < m; j++) {
		printf("La machine n°%d à une durée de %d. \n", j + 1, Machine[j]);
	}*/

	//Récupération du Résultat LSA
	int resultLSA = Machine[0];
	for (int i = 1; i < n; i++) { //i vance jusqu'au nb total de tâche
		if (Machine[i] > resultLSA) { //Récupère la valeur la + petite dans tab des machines
			resultLSA = Machine[i];
		}
	}
	return resultLSA;
}

//Algorithme LPT
int lpt (int Tache[], int Machine[],int m, int n) {
	for (int i = 0; i < m; i++) { //Permet de remettre le tableau des machines à 0
		Machine[i] = 0;
	}
	triTableauDecroissant(n, Tache); //Trie le tableau des tâches par ordre décroissant
	int resultLPT = lsa(Tache, Machine, m, n); //Calcul du résultat LPT en réutilisant le lsa
	return resultLPT;
}

//Fonction qui trie un tableau par ordre décroissant
//Fait grâce à l'aide d'internet (https://openclassrooms.com/forum/sujet/tri-decroissant-d-un-tableau-72637)
void triTableauDecroissant(int n, int Tache[]) {
	int permut = 0;
	for(n = n; n != 0; n--) {
		for(int i = 0; i < n; i++) { //i avance pour parcourir tout le tableau des tâches
			if(Tache[i] < Tache[i+1]) {
				permut = Tache[i];
				Tache[i] = Tache[i+1];
				Tache[i+1] = permut;
			}
		}
	}
	/*Texte de vérification
	for(i = 0; i < n; i++) {
		printf("Le nouveau tableau est, ligne n°%d : %d \n", i + 1, Tache[i]);
	}*/
}

//Définir la bornes inférieur maximum
int bornMax (int Tache[], int n) {
	int bornInfMax = Tache[0]; //Donne la valeur de la première case du tableau
	for (int i = 1; i < n; i++) { //i avance à partir de la deuxième case (gagne 1 tour)
		if (Tache[i] > bornInfMax) { //Si valeur de Tache[i] inférieur à valeur bornInfMax, 
			bornInfMax = Tache[i]; //alors borInfMax prend la valeur de Tache[i]
		}
	}
	return bornInfMax;
}

//Définir la bornes inférieur moyenne
float bornMoy (int Tache[], int m, int n) {
	float bornInfMoy = 0;
	for (int i = 0; i < n; i++) { //i avance permettant la récupération de toutes les tâches
		bornInfMoy = bornInfMoy + Tache[i]; //Somme de toutes les tâches
	}
	bornInfMoy = bornInfMoy / m; //Divise par le nb de machine donne la moyenne
	return bornInfMoy;
}

//Calcul le ratio total
float ratioTotal (int Tache[], int n, int result, int m) {
	int borne;
	float ratio;
	int bornInfMax = bornMax(Tache, n); //Récupération de la borne max
	float bornInfMoy = bornMoy(Tache, m, n); //Récupération de la borne moy
	if (bornInfMoy >= bornInfMax) {
		borne = bornInfMoy; //Si borne moy > ou = egal à borne max alors borne = borne moy
	} else {
		borne = bornInfMax; //Sinon borne = borne max
	}
	ratio = (float)result / (float)borne; //Calcul ratio en divisant somme total par borne ayant + grand valeur
	return ratio;
}

//Fonction permettant l'afficha de toutes les informations demander
void affichage (int Tache[], int n, int resultLSA, int resultLPT, int m) {
	int bornInfMax = bornMax(Tache, n); //Récupération de la borne max
	float bornInfMoy = bornMoy(Tache, m, n); //Récupération de la borne moy
	float ratioLSA = ratioTotal(Tache, n, resultLSA, m); //Calcul du ratio LSA
	float ratioLPT = ratioTotal(Tache, n, resultLPT, m); //Calcul du ratio LPT

	printf("Voici les résultats attendu :\n");
	printf("Borne inférieur ''maximum'' = %d \n", bornInfMax);
	printf("Borne inférieur ''moyenne'' = %f \n", bornInfMoy);
	printf("Résultat LSA = %d \n", resultLSA);
	printf("Ratio LSA = %f \n", ratioLSA);
	printf("Résultat LPT = %d \n", resultLPT);
	printf("Ratio LPT = %f \n", ratioLPT);
}