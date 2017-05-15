#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>


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

char* commande_utilisateur (char* ligne)
{
    // Déclaration des variables

    char* saisie_commande= NULL;
    int j=0;

    // Allocation dynamique

    saisie_commande=malloc(sizeof(char)*strlen(ligne));

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

/// SAISIE DE PARAMETRE PAR L'UTILISATEUR //////////////////////////////////////

char* Saisie_parametre(char* ligne, int premiere_ligne)

{
    // Declaration des variables

    char* parametre= malloc(sizeof(char)*strlen(ligne));
    int j=0;


    if (premiere_ligne < strlen (ligne)-1)
    {
        do
        {
            parametre[j]=ligne[premiere_ligne];
            premiere_ligne++;
            j++;

        } while (ligne[premiere_ligne] != '\0');
    }

    // On retourne le paramètre

    return parametre;

    // On oublie pas de libérer la mémoire alloué précedemment

    free(parametre);
}

/// FONCTION DE CHANGEMENT DE REPERTOIRE //////////////////////////////////////

void changer_repertoire(char* nom_repertoire)
{
    // Declaration des variables

    int changer_repertoire=0;

    // On recupère le repertoire d'arrivé voulu

    changer_repertoire=chdir(nom_repertoire);

    // Si la saisie utilisateur est incorrecte

    if (changer_repertoire == -1)

    {
        printf ("impossible d'accéder a votre requête\n");
    }

}

/// FONCTION POUR MONTRER LE REPERTOIRE //////////////////////////////////////

void montrer_repertoire()
{
    // Declaration des variables

    char repertoire[1024];
    char* type= NULL;
    int repertoire_vide=0;
    DIR* Repertoire;
    struct dirent *fichier_rep;

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

    Repertoire=opendir(repertoire);

    printf("Contenu %s:\nTYPE\t    NOM\n\n", repertoire);

    if (Repertoire)
    {
        while((fichier_rep=readdir(repertoire)) != NULL)
		{
			if(fichier_dir->d_type == 8)type = "Ficher\t  ";
			if(fichier_dir->d_type == 4)type = "Repertoire ";
			printf("%s |%s\n",type,fichier_rep->d_name);
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

/// CHANGEMENT DE CONSOLE //////////////////////////////////////////////


void changer_console(char** console)
{
    // Declaration des variables

    char repertoire_actif[1024];

    // changement du prompt de la console

    if (getcwd(repertoire_actif, sizeof(repertoire_actif))!=NULL)
    {
        // Alors on change le prompt

        *console = strcap(repertoire_actif, ":-$");
    }

    // Sinon on affiche un message d'erreur

    else

    {
        // Affichage console

        printf("Impossible d'acceder a votre requête");
    }

}

/// FONCTION POUR RENOMMER LES FICHIERS ////////////////////////////////

void RenommerFichier(char* nom2)
{
	//Declaration des variables
	char* p1 = NULL;
	char* p2 = NULL;

	//boolean autorisant ou pas de renommer
	bool renomme = 0;

	p1 = commande_utilisateur(nom2);
	p2 = Saisie_parametre(nom2,strlen(p1)+1);

	//si les noms des deux fichier sont differents

	if(strcmp(p1,p2)!=0)
	{
		//on renomme
		renomme = rename(p1, p2);

		if(renomme == -1)printf("Operation impossible erreur \n");
	}

	else

	{
		printf("Operation impossible : old_filename et new_filename identiques\n");
	}
}

/// FONCTION DE SUPPRESSION DE FICHIERS //////////////////////////////

//fonction permettant de supprimer un fichier

void SupprimerFichier(char* nomF)
{
	//declaration variable d’erreur
	bool erreur = 0;

	erreur = remove(param);
	//si l’opération n’a pas pu etre effectué on affiche un message

	if(erreur == -1){
		printf("Impossible de finir l’opération 😕 \n");
		}
}


/// MENU /////////////////////////////////

void Menu_execution_programme(int programmesaisie, char* parametre, char** afficheur)
{
	switch(programmesaisie)
	{
		case 1:
			kill(getpid(),SIGINT);
			break;
		case 2:
			changer_repertoire(parametre);
			break;
		case 3:
			montrer_repertoire(parametre);
			break;
		case 4:
			changer_console(afficheur);
			break;
		case 5:
			montrer_contenu(parametre);
			break;
		case 6:
			SupprimerFichier(parametre);
			break;
		case 7:
			RenommerFichier(parametre);
			break;
		default:
			help();
			break;
	}
}


