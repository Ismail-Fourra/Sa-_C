#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>
#define MAX_ETUDIANTS 100
#define MAX_NOM 30

typedef struct {
    char nom[MAX_NOM];
    int groupe;
} Etudiant;

Etudiant etudiants[MAX_ETUDIANTS];
int nbEtudiants = 0;
char input[MAX_NOM];
int groupe;

int verification(Etudiant etudiants[], int* nbEtudiants, char nom[], int groupe) {
    for (int i = 0; i < *nbEtudiants; ++i) {
        if (strcmp(etudiants[i].nom, nom) == 0 && etudiants[i].groupe == groupe) {
            printf("Nom incorrect, il existe déjà un etudiant portant ce nom dans ce groupe.\n");
            return 0;
        }
    }

    strcpy(etudiants[*nbEtudiants].nom, nom);
    etudiants[*nbEtudiants].groupe = groupe;
    (*nbEtudiants)++;
    return 1;
}

void inscription() {
    char commande[12];
    printf("Entrez une commande ici (inscription) suivi d'un nom et d'un numero de groupe : ");
    scanf("%s %s %d", commande, input, &groupe);

    if (verification(etudiants, &nbEtudiants, input, groupe)) {
        printf("Inscription realisee (%d)\n", nbEtudiants);
    }
}

typedef struct {
    int id_etu;
    int jour;
    char demi_journee[3];
} Absence;

Absence absence[MAX_ETUDIANTS];
int nbAbsences = 0;

int verification_abs(int id_etu, int jour, char* demi_journee) {
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

    absence[nbAbsences].id_etu = id_etu;
    absence[nbAbsences].jour = jour;
    strcpy(absence[nbAbsences].demi_journee, demi_journee);
    nbAbsences++;
    return 1;
}

void absence_enrengistrement() {
    int id_etu, jour;
    char demi_journee[3];
    printf("Entrez l'identifiant, le jour, et la demi-journee (am/pm)");
    scanf("%d %d %s", &id_etu, &jour, demi_journee);

    if (verification_abs(id_etu, jour, demi_journee)) {
        printf("Absence enrengistree [%d]\n", nbAbsences);
    }
}

int main() {
    printf("Veuillez entrer une commande : exit pour quitter\n");
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

    } while (1);

    return 0;
}
