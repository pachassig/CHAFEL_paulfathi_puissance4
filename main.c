#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

int main(void)
{
    int grille[6][7];
    int joueur;
    int colonne_jouee;
    int hauteur;
    int jeu_termine;
    int rejouer = 1;

    while (rejouer == 1)
    {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                grille[i][j] = 0;
            }
        }
        joueur = 1;
        colonne_jouee;
        hauteur;
        jeu_termine = 0;


        sfVideoMode mode = { 500, 500, 32 };
        sfRenderWindow* window;
        sfEvent event;

        /* Create the main window */
        window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
        if (!window)
        {
            return -1;
        }

        srand((unsigned int)time(NULL));

        /* Start the game loop */
        while (sfRenderWindow_isOpen(window))
        {
            /* Process events */
            while (sfRenderWindow_pollEvent(window, &event))
            {
                /* Close window : exit */
                if (event.type == sfEvtClosed)
                {
                    sfRenderWindow_close(window);
                }

                if (event.type == sfEvtMouseButtonPressed && !jeu_termine)
                {
                    int x = event.mouseButton.x;

                    colonne_jouee = x / (500 / 7); // adapte à ta fenêtre

                    if (colonne_jouee >= 0 && colonne_jouee < 7 &&
                        grille[0][colonne_jouee] == 0)
                    {
                        // faire tomber le pion
                        for (int i = 5; i >= 0; i--)
                        {
                            if (grille[i][colonne_jouee] == 0)
                            {
                                grille[i][colonne_jouee] = joueur;
                                hauteur = i;
                                break;
                            }
                        }



                        // vérifications victoire
                        //horizontal
                        int suite = 1;

                        for (int i = 1; i < 4; i++) {
                            if (colonne_jouee + i < 7 &&
                                grille[hauteur][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }

                        for (int i = 1; i < 4; i++) {
                            if (colonne_jouee - i >= 0 &&
                                grille[hauteur][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }

                        if (suite >= 4) {
                            printf("Le Joueur %d gagne\n", joueur);
                            jeu_termine = 1;
                        }

                        suite = 1;

                        // vertical
                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 &&
                                grille[hauteur + i][colonne_jouee] == joueur)
                                suite++;
                            else break;
                        }

                        if (suite >= 4) {
                            printf("Le Joueur %d gagne\n", joueur);
                            jeu_termine = 1;
                        }

                        suite = 1;

                        // diagonale 1
                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 && colonne_jouee + i < 7 &&
                                grille[hauteur + i][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }

                        for (int i = 1; i < 4; i++) {
                            if (hauteur - i >= 0 && colonne_jouee - i >= 0 &&
                                grille[hauteur - i][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }

                        if (suite >= 4) {
                            printf("Le Joueur %d gagne\n", joueur);
                            jeu_termine = 1;
                        }

                        suite = 1;

                        // diagonale 2
                        for (int i = 1; i < 4; i++) {
                            if (hauteur - i >= 0 && colonne_jouee + i < 7 &&
                                grille[hauteur - i][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }

                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 && colonne_jouee - i >= 0 &&
                                grille[hauteur + i][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }

                        if (suite >= 4) {
                            printf("Le Joueur %d gagne\n", joueur);
                            jeu_termine = 1;
                        }

                        // changement de joueur
                        if (!jeu_termine)
                            joueur = (joueur == 1) ? 2 : 1;
                        system("cls");
                            printf("C'est le tour du joueur %d\n", joueur);
                    }
                }

            }
            


            /* Clear the screen */
            sfRenderWindow_clear(window, sfBlack);

            sfCircleShape* pion = sfCircleShape_create();
            sfCircleShape_setRadius(pion, 25);

            int taille_case = 500 / 7;

            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    sfCircleShape_setPosition(pion, (sfVector2f) {
                        j* taille_case + 10,
                            i* taille_case + 10
                    });

                    if (grille[i][j] == 1)
                        sfCircleShape_setFillColor(pion, sfRed);
                    else if (grille[i][j] == 2)
                        sfCircleShape_setFillColor(pion, sfYellow);
                    else
                        sfCircleShape_setFillColor(pion, sfWhite);

                    sfRenderWindow_drawCircleShape(window, pion, NULL);
                }
            }


            /* Update the window */
            sfRenderWindow_display(window);

            if (jeu_termine) {
                do
                {
                    printf("Voulez-vous rejouer ? (0 pour non, 1 pour oui)");
                    scanf("%d", &rejouer);
                } while (rejouer != 0 && rejouer != 1);
                if (rejouer == 1) {
                    sfRenderWindow_close(window);
                }
                else {
                    return joueur;
                }
            }
        }

        /* Cleanup resources */
        sfRenderWindow_destroy(window);
    }


}