#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

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
        // initialisation de la grille
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                grille[i][j] = 0;

        joueur = 1;
        jeu_termine = 0;

        sfVideoMode mode = { 500, 500, 32 };
        sfRenderWindow* window;
        sfEvent event;

        window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
        if (!window)
            return -1;

        srand((unsigned int)time(NULL));

        while (sfRenderWindow_isOpen(window))
        {
            while (sfRenderWindow_pollEvent(window, &event))
            {
                if (event.type == sfEvtClosed)
                    sfRenderWindow_close(window);

                if (event.type == sfEvtMouseButtonPressed && !jeu_termine)
                {
                    int x = event.mouseButton.x;
                    colonne_jouee = x / (500 / 7);

                    if (colonne_jouee >= 0 && colonne_jouee < 7 && grille[0][colonne_jouee] == 0)
                    {
                        // trouver la ligne finale
                        int ligne_finale = 5;
                        while (ligne_finale >= 0 && grille[ligne_finale][colonne_jouee] != 0)
                            ligne_finale--;

                        int taille_case = 500 / 7;
                        float y_pion = 0;       // position verticale actuelle
                        float vitesse = 10.0f;  // pixels par frame

                        // animation de la chute
                        while (y_pion < ligne_finale * taille_case)
                        {
                            sfRenderWindow_clear(window, sfBlack);

                            // dessiner tous les pions déjà placés
                            sfCircleShape* pion = sfCircleShape_create();
                            sfCircleShape_setRadius(pion, 25);

                            for (int i = 0; i < 6; i++)
                            {
                                for (int j = 0; j < 7; j++)
                                {
                                    sfCircleShape_setPosition(pion, (sfVector2f) { j* taille_case + 10, i* taille_case + 10 });
                                    if (grille[i][j] == 1)
                                        sfCircleShape_setFillColor(pion, sfRed);
                                    else if (grille[i][j] == 2)
                                        sfCircleShape_setFillColor(pion, sfYellow);
                                    else
                                        sfCircleShape_setFillColor(pion, sfWhite);

                                    sfRenderWindow_drawCircleShape(window, pion, NULL);
                                }
                            }

                            // dessiner le pion qui tombe
                            sfCircleShape_setPosition(pion, (sfVector2f) { colonne_jouee* taille_case + 10, y_pion });
                            sfCircleShape_setFillColor(pion, (joueur == 1) ? sfRed : sfYellow);
                            sfRenderWindow_drawCircleShape(window, pion, NULL);
                            sfCircleShape_destroy(pion);

                            sfRenderWindow_display(window);
                            y_pion += vitesse;
                            sfSleep(sfMilliseconds(20)); // petite pause pour l'animation
                        }

                        // une fois en bas, mettre à jour la grille
                        grille[ligne_finale][colonne_jouee] = joueur;
                        hauteur = ligne_finale;

                        // Vérifications victoire

                        int suite = 1;

                        // horizontal
                        for (int i = 1; i < 4; i++) {
                            if (colonne_jouee + i < 7 && grille[hauteur][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }
                        for (int i = 1; i < 4; i++) {
                            if (colonne_jouee - i >= 0 && grille[hauteur][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }
                        if (suite >= 4) jeu_termine = 1;

                        // vertical
                        suite = 1;
                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 && grille[hauteur + i][colonne_jouee] == joueur)
                                suite++;
                            else break;
                        }
                        if (suite >= 4) jeu_termine = 1;

                        // diagonale \
                        suite = 1;
                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 && colonne_jouee + i < 7 && grille[hauteur + i][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }
                        for (int i = 1; i < 4; i++) {
                            if (hauteur - i >= 0 && colonne_jouee - i >= 0 && grille[hauteur - i][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }
                        if (suite >= 4) jeu_termine = 1;

                        // diagonale /
                        suite = 1;
                        for (int i = 1; i < 4; i++) {
                            if (hauteur - i >= 0 && colonne_jouee + i < 7 && grille[hauteur - i][colonne_jouee + i] == joueur)
                                suite++;
                            else break;
                        }
                        for (int i = 1; i < 4; i++) {
                            if (hauteur + i < 6 && colonne_jouee - i >= 0 && grille[hauteur + i][colonne_jouee - i] == joueur)
                                suite++;
                            else break;
                        }
                        if (suite >= 4) jeu_termine = 1;

                        system("cls");
                        if (jeu_termine)
                            printf("Le Joueur %d gagne !\n", joueur);

                        // changement de joueur
                        if (!jeu_termine) {
                            joueur = (joueur == 1) ? 2 : 1;
                            printf("C'est le tour du joueur %d\n", joueur);
                        }
                    }
                }
            }

            // affichage régulier des pions
            sfRenderWindow_clear(window, sfBlack);
            sfCircleShape* pion = sfCircleShape_create();
            sfCircleShape_setRadius(pion, 25);
            int taille_case = 500 / 7;
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    sfCircleShape_setPosition(pion, (sfVector2f) { j* taille_case + 10, i* taille_case + 10 });
                    if (grille[i][j] == 1)
                        sfCircleShape_setFillColor(pion, sfRed);
                    else if (grille[i][j] == 2)
                        sfCircleShape_setFillColor(pion, sfYellow);
                    else
                        sfCircleShape_setFillColor(pion, sfWhite);

                    sfRenderWindow_drawCircleShape(window, pion, NULL);
                }
            }
            sfCircleShape_destroy(pion);
            sfRenderWindow_display(window);

            if (jeu_termine)
            {
                do
                {
                    printf("Voulez-vous rejouer ? (0 pour non, 1 pour oui) ");
                    scanf("%d", &rejouer);
                } while (rejouer != 0 && rejouer != 1);

                if (rejouer == 1)
                    sfRenderWindow_close(window);
                else
                    return 0;
            }
        }

        sfRenderWindow_destroy(window);
    }

    return 0;
}