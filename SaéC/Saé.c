#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// D�finition des constantes avec enum
typedef enum {
    MAX_ETUDIANTS = 100,
    MAX_NOM = 30,
    MAX_ABSENCES = 100,
    DEMI_JOURNEE = 3,
    NOMBRE_MAX_J_SEMESTRE = 40,
    TAILLE_MAX_COMMANDE = 31,
} Constantes;

// D�finition de la structure Etudiant
typedef struct {
    char nom[MAX_NOM];
    int groupe;
    int id_etu;
} Etudiant;

// D�finition de la structure Absence
typedef struct {
    int id_etu;  // Identifiant de l'�tudiant
    int jour;    // Jour d'absence (1-40)
    char demi_journee[DEMI_JOURNEE]; // "am" ou "pm"
} Absence;

// V�rification de l'existence d'un �tudiant
int verification(Etudiant etudiants[MAX_ETUDIANTS], int nbEtudiants, char nom[], int groupe) {
    for (int i = 0; i < nbEtudiants; ++i) {
        if (strcmp(etudiants[i].nom, nom) == 0 && etudiants[i].groupe == groupe) {
            printf("Nom incorrect, il existe deja un etudiant portant ce nom dans ce groupe.\n");
            return 0; // L'�tudiant existe d�j�
        }
    }
    return 1; // �tudiant non trouv�
}

// Fonction d'inscription d'un �tudiant
void inscription(Etudiant etudiants[], int* nbEtudiants) {
    char nom[MAX_NOM];
    int groupe;

    scanf("%s %d", nom, &groupe);

    if (verification(etudiants, *nbEtudiants, nom, groupe)) {
        strcpy(etudiants[*nbEtudiants].nom, nom);
        etudiants[*nbEtudiants].groupe = groupe;
        etudiants[*nbEtudiants].id_etu = *nbEtudiants + 1;  // Ajout d'un identifiant unique
        (*nbEtudiants)++;
        printf("Inscription realisee (%d)\n", *nbEtudiants);
    }
}

// V�rification d'une absence
int verification_abs(Absence absences[], int nbAbsences, int id_etu, int jour, char* demi_journee, int nbEtudiants) {
    if (id_etu < 1 || id_etu > nbEtudiants) {
        printf("Identifiant incorrect\n");
        return 0; // Identifiant incorrect
    }
    if (jour < 1 || jour > 40) {
        printf("Date incorrecte\n");
        return 0; // Date incorrecte
    }
    if (strcmp(demi_journee, "am") != 0 && strcmp(demi_journee, "pm") != 0) {
        printf("Demi-journee incorrecte\n");
        return 0; // Demi-journ�e incorrecte
    }

    for (int i = 0; i < nbAbsences; ++i) {
        if (absences[i].id_etu == id_etu && absences[i].jour == jour && strcmp(absences[i].demi_journee, demi_journee) == 0) {
            printf("Absence deja enregistree\n");
            return 0; // Absence d�j� enregistr�e
        }
    }

    return 1;
}

// Enregistrement d'une absence
void absence_enregistrement(Absence absences[], int* nbAbsences, int nbEtudiants) {
    int id_etu, jour;
    char demi_journee[DEMI_JOURNEE];

    scanf("%d %d %s", &id_etu, &jour, demi_journee);

    if (verification_abs(absences, *nbAbsences, id_etu, jour, demi_journee, nbEtudiants)) {
        absences[*nbAbsences].id_etu = id_etu;
        absences[*nbAbsences].jour = jour;
        strcpy(absences[*nbAbsences].demi_journee, demi_journee);
        (*nbAbsences)++;
        printf("Absence enregistree [%d]\n", *nbAbsences);
    }
}

// Trier les �tudiants par groupe
void trierEtudiantsParGroupe(Etudiant etudiants[], int nbEtudiants) {
    for (int i = 0; i < nbEtudiants - 1; ++i) {
        for (int j = 0; j < nbEtudiants - i - 1; ++j) {
            if (etudiants[j].groupe > etudiants[j + 1].groupe) {
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
}

// Trier les �tudiants par nom
void trierEtudiantsParNom(Etudiant etudiants[], int nbEtudiants) {
    for (int i = 0; i < nbEtudiants - 1; ++i) {
        for (int j = 0; j < nbEtudiants - i - 1; ++j) {
            if (strcmp(etudiants[j].nom, etudiants[j + 1].nom) > 0) {
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
}

// Afficher la liste des �tudiants et leurs absences
// Afficher la liste des �tudiants tri�e par groupe puis par nom
void afficherEtudiants(int jour, Etudiant etudiants[], Absence absences[], int nbEtudiants, int nbAbsences) {
    if (jour < 1) {
        printf("Date incorrecte\n");
        return;
    }

    if (nbEtudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    // Trier les �tudiants par groupe
    trierEtudiantsParGroupe(etudiants, nbEtudiants);

    // Trier les �tudiants par nom au sein de chaque groupe
    int debutGroupe = 0;
    for (int i = 1; i <= nbEtudiants; ++i) {
        // Si on a atteint la fin du groupe ou la fin de la liste d'�tudiants
        if (i == nbEtudiants || etudiants[i].groupe != etudiants[debutGroupe].groupe) {
            trierEtudiantsParNom(&etudiants[debutGroupe], i - debutGroupe);  // Tri par nom des �tudiants du groupe
            debutGroupe = i;  // Passer au groupe suivant
        }
    }

    // Afficher les �tudiants et leurs absences
    for (int i = 0; i < nbEtudiants; ++i) {
        int totalAbsencesAceJour = 0;

        for (int j = 0; j < nbAbsences; ++j) {
            if (absences[j].id_etu == etudiants[i].id_etu && absences[j].jour <= jour) {
                totalAbsencesAceJour++;
            }
        }

        // Afficher les informations de l'�tudiant
        printf("(%d) %-20s %-8d %-10d\n", etudiants[i].id_etu, etudiants[i].nom, etudiants[i].groupe, totalAbsencesAceJour);
    }
}


// Fonction principale
int main() {
    Etudiant etudiants[MAX_ETUDIANTS];
    Absence absences[MAX_ABSENCES];
    int nbEtudiants = 0;
    int nbAbsences = 0;
    char commande[TAILLE_MAX_COMMANDE];
    int jour;

    do {
        scanf("%s", commande);

        if (strcmp(commande, "exit") == 0) {
            break;
        }

        if (strcmp(commande, "inscription") == 0) {
            inscription(etudiants, &nbEtudiants);
        }

        if (strcmp(commande, "absence") == 0) {
            absence_enregistrement(absences, &nbAbsences, nbEtudiants);
        }

        if (strcmp(commande, "etudiants") == 0) {
            scanf("%d", &jour);
            afficherEtudiants(jour, etudiants, absences, nbEtudiants, nbAbsences);
        }

    } while (strcmp(commande, "exit") != 0);

    return 0;
}