#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>

// Constantes
#define MAX_ETUDIANTS 100
#define MAX_NOM 30
#define MAX_ABSENCES 100

// Définition de la structure Etudiant
typedef struct {
    char nom[MAX_NOM];
    int groupe;
} Etudiant;

// Définition de la structure Absence
typedef struct {
    int id_etu;  // Identifiant de l'etudiant
    int jour;    // Jour d'absence (1-40)
    char demi_journee[3]; // "am" ou "pm"
} Absence;

// Vérification de l'existence d'un etudiant
int verification(Etudiant etudiants[], int nbEtudiants, char nom[], int groupe) {
    for (int i = 0; i < nbEtudiants; ++i) {
        if (strcmp(etudiants[i].nom, nom) == 0 && etudiants[i].groupe == groupe) {
            printf("Nom incorrect, il existe deja un etudiant portant ce nom dans ce groupe.\n");
            return 0; // L'étudiant existe déjà
        }
    }
    return 1; // Étudiant non trouvé
}

// Fonction d'inscription d'un etudiant
void inscription(Etudiant etudiants[], int* nbEtudiants) {
    char nom[MAX_NOM];
    int groupe;

    scanf("%s %d", nom, &groupe);

    if (verification(etudiants, *nbEtudiants, nom, groupe)) {
        strcpy(etudiants[*nbEtudiants].nom, nom);
        etudiants[*nbEtudiants].groupe = groupe;
        (*nbEtudiants)++;
        // Affichage minimal
        printf("Inscription realisee(%d)\n", *nbEtudiants);
    }
}

// Vérification d'une absence
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
        return 0; // Demi-journée incorrecte
    }

    for (int i = 0; i < nbAbsences; ++i) {
        if (absences[i].id_etu == id_etu && absences[i].jour == jour && strcmp(absences[i].demi_journee, demi_journee) == 0) {
            printf("Absence deja enregistree\n");
            return 0; // Absence déjà enregistrée
        }
    }

    return 1;
}


void absence_enregistrement(Absence absences[], int* nbAbsences, int nbEtudiants) {
    int id_etu, jour;
    char demi_journee[3];

    scanf("%d %d %s", &id_etu, &jour, demi_journee);

    if (verification_abs(absences, *nbAbsences, id_etu, jour, demi_journee, nbEtudiants)) {
        absences[*nbAbsences].id_etu = id_etu;
        absences[*nbAbsences].jour = jour;
        strcpy(absences[*nbAbsences].demi_journee, demi_journee);
        (*nbAbsences)++;

        printf("Absence enregistree [%d]\n", *nbAbsences);
    }
}

void afficher_liste_etudiants(Etudiant etudiants[], Absence absences[], int nbEtudiants, int nbAbsences, int jour) {
    if (jour < 1) {
        printf("Date Incorrect\n");
        return;
    }

    if (nbEtudiants == 0) {
        printf("Aucun Inscrit");
        return;
    }

    for (int i = 0; i < nbEtudiants - 1; ++i) {
        for (int j = 0; j < nbEtudiants - i - 1; ++j) {
            if (etudiants[j].groupe > etudiants[j + 1].groupe) {
                int tmpGroupe = etudiants[j].groupe;
                etudiants[j].groupe = etudiants[j + 1].groupe;
                etudiants[j + 1].groupe = tmpGroupe;
                if (etudiants[j].groupe == etudiants[j].groupe) {

                    

                }
            }
        }
    }

               


    for (int i = 0; i < nbEtudiants; ++i) {
        int total_absences = 0;
        for (int j = 0; j < nbAbsences; ++j) {
            if (absences[j].id_etu == i + 1 && absences[j].jour <= jour) {
                total_absences++;
            }
        }


    }
        

    }


// Fonction principale
int main() {
    Etudiant etudiants[MAX_ETUDIANTS];
    Absence absences[MAX_ABSENCES];
    int nbEtudiants = 0;
    int nbAbsences = 0;
    char commande[31];
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
            afficher_liste_etudiants(etudiants, absences, nbEtudiants, nbAbsences, jour);
        }

    } while (strcmp(commande, "exit") != 0);

    return 0;
}