#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#define Nombre_commande 8
char* Saisiephrase(char* console)
{
    //Declaration des variables

    char* instruction_utilisateur=NULL;
    size_t longueur=0;

    //Affichage a l'ecran

    printf("%s",console);
    fflush (stdin);

    // On récupère la saisie

    getline (&instruction_utilisateur, &longueur, stdin);
    instruction_utilisateur[strlen(instruction_utilisateur)-1] = '\0';

    // On renvoie la chaine qu'on a récupéré

    return instruction_utilisateur;
}

// FONCTION DE RECUPERATION COMMANDE UTILISATEUR /////////////////////////

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

// SAISIE DE PARAMETRE PAR L'UTILISATEUR //////////////////////////////////////

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

// FONCTION DE CHANGEMENT DE REPERTOIRE //////////////////////////////////////

void changer_repertoire(char* nom_repertoire)
{
    // Declaration des variables

    int changer_repertoire=0;

    // On recupère le repertoire d'arrivé voulu

    changer_repertoire=chdir(nom_repertoire);
	printf("operation effectuee \n");

    // Si la saisie utilisateur est incorrecte

    if (changer_repertoire == -1)

    {
        printf ("impossible d'accéder a votre requête\n");
    }

}

// FONCTION POUR MONTRER LE REPERTOIRE //////////////////////////////////////

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
			if(fichier_rep->d_type == 8)type = "Ficher\t  ";
			if(fichier_rep->d_type == 4)type = "Repertoire ";
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

// CHANGEMENT DE CONSOLE //////////////////////////////////////////////


void changer_console(char** console)
{
    // Declaration des variables

    char repertoire_actif[1024];

    // changement du prompt de la console

    if (getcwd(repertoire_actif, sizeof(repertoire_actif))!=NULL)
    {
        // Alors on change le prompt

        *console = strcat(repertoire_actif, ":-$");
    }

    // Sinon on affiche un message d'erreur

    else

    {
        // Affichage console

        printf("Impossible d'acceder a votre requête \n");
    }

}

// FONCTION POUR RENOMMER LES FICHIERS ////////////////////////////////

void RenommerFichier(char* nom2)
{
	//Declaration des variables
	char* p1 = NULL;
	char* p2 = NULL;

	//boolean (type int) autorisant ou pas de renommer
	int renomme = 0;

	p1 = commande_utilisateur(nom2);
	p2 = Saisie_parametre(nom2,strlen(p1)+1);

	//si les noms des deux fichier sont differents

	if(strcmp(p1,p2)!=0)
	{
		//on renomme
		renomme = rename(p1, p2);
		printf("Operation effectuee \n");

		if(renomme == -1)printf("Operation impossible erreur \n");
	}

	else

	{
		printf("Operation impossible : old_filename et new_filename identiques\n");
	}
}

// FONCTION DE SUPPRESSION DE FICHIERS //////////////////////////////

//fonction permettant de supprimer un fichier

void SupprimerFichier(char* nomF)
{
	//declaration variable d’erreur
	int erreur = 0;

	erreur = remove(nomF);
	printf("C'est fait");
	//si l’opération n’a pas pu etre effectué on affiche un message

	if(erreur == -1){
		printf("Impossible de finir l’opération 😕 \n");
		}
}

// FONCTION MONTRANT LE CONTENU D'UN REPERTOIRE
void montrer_contenu(char* parametre)
{
	DIR* dir;
	struct dirent* fileindir;
	dir = opendir(parametre);
	int Vide = 0, poulet = 0;
	char* type = NULL;
	if(dir)
	{
		while((fileindir=readdir(dir)) != NULL)
		{

			if(strcmp(fileindir->d_name,".")!=0 && strcmp(fileindir->d_name,"..")!=0)
			{
				if(poulet == 0)printf("Content of %s:\nTYPE\t    NOM\n\n ", parametre);
				if(fileindir->d_type == 8)type = "FILE\t  ";
				if(fileindir->d_type == 4)type = "DIRECTORY ";
				printf("%s |%s\n",type, fileindir->d_name);
				Vide = 1;
				poulet = 1;
			}
		}
		closedir(dir);
		if(Vide==0)printf("%s: Dossier vide. \n ",parametre);
	}
	else printf("Impossible d’acceder à votre requête : Le fichier ou le dossier n’existe pas.");
}


// MENU /////////////////////////////////

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
	}
}

int main(int argc, char* argv[])
{
	char* pcommande_usueur = NULL;
	char* parametree = NULL;
	char* pcommande = NULL;
	char* canardaffiche = {">>"};
	char* possibleCommands[] = {"exit","cd","Lister_RepC","changePrompt","Lister","supprimer","renommer"};
	int j = 0, commandexistante = 0;
	while(1)
	{
		pcommande_usueur = Saisiephrase(canardaffiche);
		pcommande = commande_utilisateur(pcommande_usueur);
		parametree = Saisie_parametre(pcommande_usueur, strlen(pcommande)+1);
		for(j = 0; j < Nombre_commande; j++)
		{
			if(!strcmp(pcommande,possibleCommands[j]))
			{
				Menu_execution_programme(j+1, parametree, &canardaffiche);
				commandexistante = 1;
			}
		}
		if(commandexistante == 0)printf("'%s' Commande non reconnu, retente ta chance ;)\n", pcommande);
		pcommande_usueur = NULL;
		parametree = NULL;
		pcommande = NULL;
		j = 0;
		commandexistante = 0;
	}
}
