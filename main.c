#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

int main(void)
{
/*    sfVideoMode mode = { 500, 500, 32 };
    sfRenderWindow* window;
    sfEvent event;

    /* Create the main window */
    /*window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
    if (!window)
    {
        return -1;
    }

    srand((unsigned int)time(NULL));*/

    /* Start the game loop */
    /*while (sfRenderWindow_isOpen(window))
    {*/
        /* Process events */
        /*while (sfRenderWindow_pollEvent(window, &event))
        {*/
            /* Close window : exit */
            /*if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }

        }*/


        /* Clear the screen */
        /*sfRenderWindow_clear(window, sfBlack);

        //Ici pour afficher de nouvelles choses


        /* Update the window */
        /*sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    /*sfRenderWindow_destroy(window);*/





    //Crée la grille
    int grille[6][7]; // ligne - colonne
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            grille[i][j] = 0;
        }
    }

    int joueur = 1;
    int colonne_jouee;
    int hauteur;

    do

    {
        system("cls");
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (grille[i][j] == 0) {
                    printf("| ");
                }
                else {
                    printf("|%d", grille[i][j]);
                }
            }
            printf("|\n");
        }
        printf("---------------\n ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", i + 1);
        }
        printf("\n");

        

        //tour d'un joueur
        do {
            printf("Dans quel colonne jouer ?\n");
            scanf("%d", &colonne_jouee);
        } while (grille[0][colonne_jouee - 1] != 0);

        

        for (int i = 6; i >= 0; i--) {
            if (grille[i][colonne_jouee - 1] == 0) {
                grille[i][colonne_jouee - 1] = joueur;
                hauteur = i; // grille[hauteur][colonne_jouee] est la pièce que je viens de poser
                break;
            }
        }


        //vérification victoire
        //vérif horizontal
        int suite = 1;
        for (int i = 1; i < 4; i++) {
            if (colonne_jouee + i < 7 && (grille[hauteur][colonne_jouee + i - 1] == joueur)) {
                if (grille[hauteur][colonne_jouee + i] == joueur) {
                    suite += 1;
                }
            }
            if (colonne_jouee - i >= 0 && (grille[hauteur][colonne_jouee - i + 1] == joueur)) {
                if (grille[hauteur][colonne_jouee - i] == joueur) {
                    suite += 1;
                }
            }
            else {
                continue;
            }
        }

        if (suite >= 4) {
            printf("Le joueur %d a gagne !", joueur);
            if (joueur == 1){
                return 1;
            }
            else {
                return 2;
            }
        }

        //vérif vertical
        suite = 1;
        for (int i = 1; i < 4; i++) {
            if (hauteur + i < 6 && (grille[hauteur + i - 1][colonne_jouee] == joueur)) {
                if (grille[hauteur + i][colonne_jouee] == joueur) {
                    suite += 1;
                }
            }
            if (hauteur - i >= 0 && (grille[hauteur - i + 1][colonne_jouee] == joueur)) {
                if (grille[hauteur - i][colonne_jouee] == joueur) {
                    suite += 1;
                }
            }
            else {
                continue;
            }
        }
        if (suite >= 4) {
            printf("Le joueur %d a gagne !", joueur);
            return joueur;
        }
        //vérif diagonale 1
        suite = 1;
        for (int i = 1; i < 4; i++) {
            if (hauteur + i < 6 && colonne_jouee - i >= 0 && (grille[hauteur + i - 1][colonne_jouee - i + 1] == joueur)) {
                if (grille[hauteur + i][colonne_jouee - i] == joueur) {
                    suite += 1;
                }
            }
            if (hauteur - i >= 0 && colonne_jouee + i < 7 && (grille[hauteur - i + 1][colonne_jouee + i - 1] == joueur)) {
                if (grille[hauteur - i][colonne_jouee + i] == joueur) {
                    suite += 1;
                }
            }
            else {
                continue;
            }
        }
        if (suite >= 4) {
            printf("Le joueur %d a gagne !", joueur);
            return joueur;
        }

        //vérif diagonale 2
        suite = 1;
        for (int i = 1; i < 4; i++) {
            if (hauteur - i >= 0 && colonne_jouee - i >= 0 && (grille[hauteur - i + 1][colonne_jouee - i + 1] == joueur)) {
                if (grille[hauteur - i][colonne_jouee - i] == joueur) {
                    suite += 1;
                }
            }
            if (hauteur + i < 6 && colonne_jouee + i < 7 && (grille[hauteur + i + 1][colonne_jouee + i - 1] == joueur)) {
                if (grille[hauteur + i][colonne_jouee + i] == joueur) {
                    suite += 1;
                }
            }
            else {
                continue;
            }
        }
        if (suite >= 4) {
            printf("Le joueur %d a gagne !", joueur);
            return joueur;
        }


        //vérification nulle
        bool tableau_plein = true;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (grille[i][j] == 0) {
                    tableau_plein = false;
                    break;
                }
            }
        }


        //changement de tour
        if (joueur == 1) {
            joueur = 2;
        }
        else {
            joueur = 1;
        }

        if (tableau_plein == true) {
            printf("La partie est nulle.");
            return 3;
        }

    }while (true);


    return 1;
}
