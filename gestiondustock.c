#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>

typedef struct
{

    char article[30];
    char refstock[30];
    int prix;
    int quantite;

} stock;

typedef struct
{

    char article[30];
    char refstock[30];
    int prix;
    int quantite;

} move;

// toute les fonctions utiliser

void introd(); // introduction

void init();

void ajout(stock *s,char *nomFichier ); // 1

void affich(stock *s,char *nomFichier ); // 2

void supp(stock *s,char *nomFichier ); // 3

void recherche(stock *s,char *nomFichier ); // 4

void modif(stock *s,char *nomFichier ); // 5


int main()
{

    stock s;
    move m;

    int choix, t;
    char *nomDossier = "project SI";
    char *nomFichier = "stock.txt";
    init(nomDossier,nomFichier);

    printf("\n\n              Bienvenu dans la gestion de stock de votre entreprise         \n\n");

    while (choix != 6)
    {

        introd();

        t = 0;
        printf("\n    voyez entrez votre choix de commande     \n");

        fflush(stdin); // permet de vider et lire la valeur saisi

        scanf("%d", &choix);

        system("cls");
        do
        {
            if (choix == 1) // ajout
            {
                ajout(&s,nomFichier );
            }

            else if (choix == 2) // affich
            {
                affich(&s,nomFichier);
            }

            else if (choix == 3) // SUPP
            {
                supp(&s,nomFichier);
            }

            else if (choix == 4) // recherche
            {
                recherche(&s,nomFichier);
            }

            else if (choix == 5) // modif
            {
                modif(&s,nomFichier);
            }

            printf("\n pour continuez cliquer sur 0 sinon 1 \n");
            scanf("%d", &t);

        } while (t == 0);

        system("cls");

    } // fin while

    if (choix == 6)
    {

        printf("\n Aurevoir et a bientot \n");
    }
}

void introd()
{

    printf("        Cher utilisateur                                                      \n\n");

    printf("        voici la liste des modes :                                            \n\n");

    printf("                 1.Ajout d'article                                  \n");
    printf("                 2.Afficher les articles                            \n");
    printf("                 3.Supprimer des articles                           \n");
    printf("                 4.Rechercher un ou plusieurs articles              \n");
    printf("                 5.Modifier un ou deux attributs d un article       \n");
    printf("                 6.Exit                                             \n");
}



void init(char* nomDossier,char* nomFichier) {

    char chemin[100];

    sprintf(chemin, "%s\\%s", nomDossier, nomFichier);

    // Vérifier l'existence du dossier
    DWORD attributs = GetFileAttributes(nomDossier);
    if (attributs != INVALID_FILE_ATTRIBUTES && (attributs & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("Le dossier existe déjà.\n");
        return;
    }

    // Vérifier l'existence du fichier
    if (GetFileAttributes(chemin) != INVALID_FILE_ATTRIBUTES) {
        printf("Le fichier existe déjà.\n");
        return;
    }

    // Créer le dossier
    if (CreateDirectory(nomDossier, NULL)) {
        printf("Dossier créé avec succès.\n");
    } else {
        printf("Erreur lors de la création du dossier.\n");
        return;
    }

    // Créer le fichier
    FILE *fichier = fopen(chemin, "w");

    if (fichier != NULL) {
        printf("Fichier créé avec succès.\n");
        fclose(fichier);
    } else {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }
}

// 1
void ajout(stock *s,char *nomFichier )
{

    int c = 0;

    FILE *f = fopen("project SI/stock.txt", "a");

    if (f != NULL)
    {

        printf("\n\n\n\tEntrez la reference du stock: ");
        scanf("%s", s->refstock);

        printf("\tEntrez l article: ");
        scanf("%s", s->article);

        printf("\tEntrez le prix unitaire: ");
        scanf("%d", &s->prix);

        printf("\tEntrez la quantite: ");
        scanf("%d", &s->quantite);

        fprintf(f, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);

        c = 1;
    }

    else
    {
        printf("\nerreur");
    }

    fclose(f);

    if (c == 1)
    {
        printf("\najout avec succes");
    }

    else
    {
        printf("\nERREUR");
    }
}

// 2
void affich(stock *s,char *nomFichier )
{

    FILE *f = fopen("project SI/stock.txt", "r");

    if (f != NULL)
    {

        while (fscanf(f, "%s %s %d %d", s->refstock, s->article, &s->prix, &s->quantite) != EOF)
        {

            printf("\n______________________________\n");
            printf("\nla reference du stock est %s\n", s->refstock);
            printf("\nl'article  est %s \n", s->article);
            printf("\nle prix unitaire est %d\n", s->prix);
            printf("\nla quantite est %d\n", s->quantite);
            printf("\n______________________________\n");
        }
    }

    else
    {
        printf("erreur");
    }

    fclose(f);
}

// 3
void supp(stock *s,char *nomFichier )
{

    char r[30];
    int p = 0;

    FILE *f = fopen("project SI/stock.txt", "r");
    FILE *g = fopen("project SI/temp.txt", "w");

    rewind(f);

    if (f == NULL && g == NULL)
    {
        printf(" ERREUR ");
    }

    printf("\n\n\tEntrez la reference: ");
    scanf("%s", r);

    while (fscanf(f, "%s %s %d %d", s->refstock, s->article, &s->prix, &s->quantite) != EOF)
    {

        if (strcmp(s->refstock, r) != 0)
        {

            fprintf(g, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);
        }
        else
        {
            p = 1;
        }
    }
    if (p == 1)
    {
        printf("\n Article supprimer avec succes ");
    }
    else
    {
        printf("\n l'article n'existe pas ");
    }
    fclose(f);
    fclose(g);
    remove("project SI/stock.txt");
    rename("project SI/temp.txt", "project SI/stock.txt");
}

// 4
void recherche(stock *s,char *nomFichier )
{

    char r[30];

    FILE *f = fopen("project SI/stock.txt", "r");

    rewind(f);

    printf("\n\n\tEntrez la reference: ");
    scanf("%s", r);

    while (!feof(f))
    {

        fscanf(f, "%s %s %d %d", s->refstock, s->article, &s->prix, &s->quantite);

        if (strcmp(s->refstock, r) == 0)
        {

            printf("\nla reference du stock est %s\n", s->refstock);
            printf("\nl'article  est %s \n", s->article);
            printf("\nle prix unitaire est %d\n", s->prix);
            printf("\nla quantite est %d\n", s->quantite);

            break;
            fclose(f);
        }
    }

    if (feof(f) != 0)
    {
        fclose(f);
        printf("la reference n'existe pas \n");
    }
}

// 5
void modif(stock *s,char *nomFichier )
{

    char r[30];
    int choose, q, c = 0, k = 0;
    int prixn;

    FILE *f = fopen("project SI/stock.txt", "r");
    FILE *g = fopen("project SI/temp.txt", "w");

    rewind(f);

    printf("\n\n\tEntrez la reference: ");
    scanf("%s", r);

    printf("\n       que voulez vous modifier ?           \n\n");

    printf("         1.prix unitaire      \n");
    printf("         2.quantite           \n");
    printf("         3.les deux           \n\n");

    scanf("%d", &choose);

    while (fscanf(f, "%s %s %d %d", s->refstock, s->article, &s->prix, &s->quantite) != EOF)
    {

        if (strcmp(s->refstock, r) == 0)
        {
            k = 0;
            c = 1;
            while (k == 0)
            {
                if (choose == 1)
                {
                    printf(" donnez le nouveau prix \n");
                    scanf("%d", &prixn);

                    s->prix = prixn;

                    fprintf(g, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);

                    printf("\nref : %s article : %s prix modifier: %d quantite : %d\n", s->refstock, s->article, s->prix, s->quantite);

                    k = 1;
                }

                else if (choose == 2)
                {
                    printf(" donnez la nouvelle quantite \n");
                    scanf("%d", &q);

                    s->quantite = q;

                    fprintf(g, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);

                    printf("\nref : %s article : %s prix : %d quantite modifier : %d\n", s->refstock, s->article, s->prix, s->quantite);

                    k = 1;
                }

                else if (choose == 3)
                {
                    printf(" donnez le nouveau prix \n");
                    scanf("%d", &prixn);
                    printf(" donnez la nouvelle quantite \n");
                    scanf("%d", &q);

                    s->prix = prixn;
                    s->quantite = q;

                    fprintf(g, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);

                    printf("\nref : %s article : %s prix modifier: %d quantite modifier : %d\n", s->refstock, s->article, s->prix, s->quantite);

                    k = 1;
                }
            }
        }
        else
        {
            fprintf(g, "%-20s%-20s%-10d%-10d\n", s->refstock, s->article, s->prix, s->quantite);
        }
    }

    fclose(f);
    fclose(g);
    remove("project SI/stock.txt");
    rename("project SI/temp.txt", "project SI/stock.txt");

    if (c == 1)
    {
        printf("\nmodification avec succes\n");
    }
    else
    {
        printf("\nla reference n'exite pas \n");
    }
}

