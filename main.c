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
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                grille[i][j] = 0;

        joueur = 1;
        jeu_termine = 0;

        sfVideoMode mode = { 500, 500, 32 };
        sfRenderWindow* window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
        if (!window)
            return -1;


     
        
        sfTexture* texture_j1 = sfTexture_createFromFile("j1.png", NULL);
        sfTexture* texture_j2 = sfTexture_createFromFile("j2.png", NULL);

        sfSprite* sprite_j1 = sfSprite_create();
        sfSprite_setTexture(sprite_j1, texture_j1, sfTrue);
		sfSprite_scale(sprite_j1, (sfVector2f) { 0.5f, 0.5f });
        sfSprite_setPosition(sprite_j1, (sfVector2f) { -35, 0 });
        sfSprite* sprite_j2 = sfSprite_create();
        sfSprite_setTexture(sprite_j2, texture_j2, sfTrue);
        sfSprite_scale(sprite_j2, (sfVector2f) { 0.5f, 0.5f });
		sfSprite_setPosition(sprite_j1, (sfVector2f) { -35, 0 });
        while (sfRenderWindow_isOpen(window))
        {
            sfEvent event;

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
                        int ligne_finale = 5;
                        while (ligne_finale >= 0 && grille[ligne_finale][colonne_jouee] != 0)
                            ligne_finale--;

                        int taille_case = 500 / 7;
                        float y_pion = 0;
                        float vitesse = 10.0f;

                        while (y_pion < ligne_finale * taille_case)
                        {
                            sfRenderWindow_clear(window, sfBlack);

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

                            sfCircleShape_setPosition(pion, (sfVector2f) { colonne_jouee* taille_case + 10, y_pion });
                            sfCircleShape_setFillColor(pion, (joueur == 1) ? sfRed : sfYellow);
                            sfRenderWindow_drawCircleShape(window, pion, NULL);

                            sfCircleShape_destroy(pion);
                            sfRenderWindow_display(window);

                            y_pion += vitesse;
                            sfSleep(sfMilliseconds(20));
                        }

                        grille[ligne_finale][colonne_jouee] = joueur;
                        hauteur = ligne_finale;

                        int suite = 1;

                        // horizontal
                        for (int i = 1; i < 4; i++)
                            if (colonne_jouee + i < 7 && grille[hauteur][colonne_jouee + i] == joueur) suite++; else break;
                        for (int i = 1; i < 4; i++)
                            if (colonne_jouee - i >= 0 && grille[hauteur][colonne_jouee - i] == joueur) suite++; else break;
                        if (suite >= 4) jeu_termine = 1;

                        // vertical
                        suite = 1;
                        for (int i = 1; i < 4; i++)
                            if (hauteur + i < 6 && grille[hauteur + i][colonne_jouee] == joueur) suite++; else break;
                        if (suite >= 4) jeu_termine = 1;

                        // diagonales
                        suite = 1;
                        for (int i = 1; i < 4; i++)
                            if (hauteur + i < 6 && colonne_jouee + i < 7 && grille[hauteur + i][colonne_jouee + i] == joueur) suite++; else break;
                        for (int i = 1; i < 4; i++)
                            if (hauteur - i >= 0 && colonne_jouee - i >= 0 && grille[hauteur - i][colonne_jouee - i] == joueur) suite++; else break;
                        if (suite >= 4) jeu_termine = 1;

                        suite = 1;
                        for (int i = 1; i < 4; i++)
                            if (hauteur - i >= 0 && colonne_jouee + i < 7 && grille[hauteur - i][colonne_jouee + i] == joueur) suite++; else break;
                        for (int i = 1; i < 4; i++)
                            if (hauteur + i < 6 && colonne_jouee - i >= 0 && grille[hauteur + i][colonne_jouee - i] == joueur) suite++; else break;
                        if (suite >= 4) jeu_termine = 1;

                        if (!jeu_termine)
                            joueur = (joueur == 1) ? 2 : 1;
                    }
                }
            }

            sfRenderWindow_clear(window, sfBlack);

            if (!jeu_termine)
            {
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
            }
            else
            {
                // 🎉 Affichage écran victoire
                if (joueur == 1)
                    sfRenderWindow_drawSprite(window, sprite_j1, NULL);
                else
                    sfRenderWindow_drawSprite(window, sprite_j2, NULL);
            }

            sfRenderWindow_display(window);

            // attendre clic si victoire
            if (jeu_termine)
            {
                sfEvent e;
                int attente = 1;
                while (attente)
                {
                    while (sfRenderWindow_pollEvent(window, &e))
                    {
                        if (e.type == sfEvtClosed)
                            sfRenderWindow_close(window);

                        if (e.type == sfEvtMouseButtonPressed || e.type == sfEvtKeyPressed)
                            attente = 0;
                    }
                }

                printf("Rejouer ? (1 oui / 0 non) : ");
                scanf("%d", &rejouer);

                sfRenderWindow_close(window);
            }
        }

        sfSprite_destroy(sprite_j1);
        sfSprite_destroy(sprite_j2);
        sfTexture_destroy(texture_j1);
        sfTexture_destroy(texture_j2);
        sfRenderWindow_destroy(window);
    }

    return 0;
}