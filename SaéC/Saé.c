#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>

// enum
#define MAX_ETUDIANTS 100
#define MAX_NOM 30
#define DEMI_JOURNEE 3

// définir les groupes
typedef struct {
    char nom[MAX_NOM];
    int groupe;
    int nbEtudiants;
    Etudiant etudiants[MAX_ETUDIANTS];
} Etudiant;

//definir absences
typedef struct {
    int id_etu;
    int jour;
    char demi_journee[DEMI_JOURNEE];
    Absence absence[MAX_ETUDIANTS];
    int nbAbsences;
} Absence;

char input[MAX_NOM];

/*
Etudiant etudiants[MAX_ETUDIANTS];
int nbEtudiants = 0;
char input[MAX_NOM];
int groupe;*/

int verification(Etudiant etudiants[], int* nbEtudiants, char nom[], int groupe) {
    Etudiant e;
    for (int i = 0; i < *nbEtudiants; ++i) {
        if (strcmp(e.etudiants[i].nom, e.nom) == 0 &&  e.etudiants[i].groupe == e.groupe) {
            printf("Nom incorrect, il existe deja un etudiant portant ce nom dans ce groupe.\n");
            return 0;
        }
    }
  
   // on ajoute aux tableaux les valeurs entrées
    strcpy(e.etudiants[*nbEtudiants].nom, nom);
    etudiants[*nbEtudiants].groupe = groupe;
    (*nbEtudiants)++;
    return 1; //return 1 : le programme SORT de la fonction
}              //return 0 : tout s'est bien passé

void inscription() {
    char commande[12];
 
    scanf("%s %d", &input, &groupe);

    if (verification(etudiants, &nbEtudiants, input, groupe)) {
        printf("Inscription realisee (%d)\n", nbEtudiants);
    }
}



int verification_abs(int id_etu, int jour, char* demi_journee) {
    Absence a;
    a.nbAbsences = 0; 
    if (id_etu < 1 || id_etu > nbEtudiants) {
        printf("Identifiant Incorrect\n");
        return 1;
    }
    if (jour < 1 || jour > 40) {
        printf("Date incorrecte\n");
        return 0;
    }

    if (strcmp(demi_journee, "am") != 0 && strcmp(demi_journee, "pm") != 0) {
        printf("Demi-journee incorrecte\n");
        return 0;
    }

    for (int i = 0; i < nbAbsences; ++i) {
        if (absence[i].id_etu == id_etu && absence[i].jour == jour && strcmp(absence[i].demi_journee, demi_journee) == 0) {
            printf("Absence deja connue\n");
            return 0;
        }
    }

    // on ajoute aux tableaux les valeurs entrées
    a.absence[nbAbsences].id_etu = id_etu;
    a.absence[nbAbsences].jour = jour;
    strcpy(a[nbAbsences].demi_journee, demi_journee);
    nbAbsences++;
    return 1;
}

void absence_enrengistrement() {
    int id_etu, jour;
    char demi_journee[3];
  
    scanf("%d %d %s", &id_etu, &jour, demi_journee);

    if (verification_abs(id_etu, jour, demi_journee)) {
        printf("Absence enrengistree [%d]\n", a.nbAbsences);
    }
}

int main() {
  
    char commande[12];

    do {
        scanf("%s", commande);
        if (strcmp(commande, "exit") == 0) {
            break;
        }

        if (strcmp(commande, "inscription") == 0) {
            inscription();
        }

        if (strcmp(commande, "absence") == 0) {
            absence_enrengistrement();
        }

    } while (strcmp(commande, "exit") != 0);

    return 0;
}

typedef struct {
   
}

void justification();
int id_abs, jour;
char justif[51];
scanf("%d %d %s", id_abs, jour, justif);




