#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMBER_OF_COMMANDS 8

/// FONCTION DE SAISIE DE PHRASE //////////////////////////////////////////

char* Saisie_phrase (char* console)
{
    // Declaration des variables

    char* instruction_utilisateur=NULL;
    size_t longueur=0;

    // Affichage a l'ecran

    printf("%s",console);
    fflush (stdin);

    // On récupère la saisie

    getline (&instruction_utilisateur, &longueur, stdin);
    instruction_utilisateur[strlen(instruction_utilisateur)-1] = '\0';

    // On renvoie la chaine qu'on a récupéré

    return instruction_utilisateur;
}

/// FONCTION DE RECUPERATION COMMANDE UTILISATEUR /////////////////////////

char commande_utilisateur (char* ligne)
{
    // Déclaration des variables

    char* saisie_commande= NULL;
    int j=0;

    // Allocation dynamique

    saisie_commande = malloc(sizeof(char)*strlen(ligne));

    // On récupère la commande utilisateur et on la stocke

    do
    {
        saisie_commande[j]=ligne[j];
        j++;

    } while (ligne[j]!= ' ' && ligne[j]!= '\0');

    saisie_commande[j]='\0';

    // On renvoie la commande que l'on a stocké

    return saisie_commande;

    // On oublie pas de libérer la mémoire alloué au début du sous-programme

    free (saisie_commande);
}

/// FONCTION DE CHANGEMENT DE REPERTOIRE //////////////////////////////////////

void changer_repertoire(char* nom_repertoire)
{
    // Declaration des variables

    int changer_repertoire=0;

    // On recupère le repertoire d'arrivé voulu

    changer_repertoire=chdir(nom_repertoir);

    // Si la saisie utilisateur est incorrecte

    if (changer_repertoire == -1)

    {
        printf ("impossible d'accéder a votre requête\n");
    }

}


void montrer_repertoire()
{
    // Declaration des variables

    char repertoire[1024];
    char* type= NULL;
    int repertoire_vide=0;
    DIR* Repertoire;
    struc dirent *fichier_rep;

    // Affichage

    if (getcwd(repertoire, sizeof(repertoire))!=NULL)

    {
        //on affiche la liste a l'ecran

        printf("Repertoire actuellement ouvert: %s", repertoire);
    }

    else
    {
        // On affiche un message d'erreur

        printf("impossible d'acceder à votre requête");
    }

    // On ouvre le repertoir

    Repertoir=opendir(repertoir);

    printf("Contenu %s:\nTYPE\t    NOM\n\n", repertoire);

    if (Repertoire)
    {
        while((fichier_dir=readdir(repertoire)) != NULL)
		{
			if(fichier_dir->d_type == 8)type = "Ficher\t  ";
			if(fichier_dir->d_type == 4)type = "Repertoire ";
			printf("%s |%s\n",type, fichier_rep->d_name);
			repertoire_vide = 1;
		}
		closedir(repertoire);

		if(repertoire_vide==0)
        {
            printf("%s: Repertoire vide\n",repertoire);
        }

        else

        {
            // On affiche un message d'erreur

        printf("impossible d'acceder à votre requête");
        }
    }
}


