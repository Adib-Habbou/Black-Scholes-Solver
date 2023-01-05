#include <iostream>
#include <vector>
#include "sdl.h"

const int SCREEN_WIDTH = 640; // Nombre de pixel sur la largeur de l'écran
const int SCREEN_HEIGHT = 480; // Nombre de pixel sur la hauteur de l'écran

const std::vector<Uint8> red = {255, 0, 0}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur rouge
const std::vector<Uint8> blue = {0, 0, 255}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur bleu
const std::vector<Uint8> green = {0, 255, 0}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur verte

int main()
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return 1;
    }

    // Création de la fenêtre 1
    SDL_Window* window_1 = init_window("Fenêtre 1", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer 1
    SDL_Renderer* renderer_1 = init_renderer(window_1);
    
    // Création de la fenêtre 2
    SDL_Window* window_2 = init_window("Fenêtre 2", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer 2
    SDL_Renderer* renderer_2 = init_renderer(window_2);

    // Créer une instance de la classe Sdl
    Sdl sdl_1(renderer_1, window_1);

    // Créer une instance de la classe Sdl
    Sdl sdl_2(renderer_2, window_2);

    // Attendre la fermeture de la fenêtre
    bool quit_1 = false;
    bool quit_2 = false;
    SDL_Event event;
    
    while (!(quit_1 && quit_2))
    {
        // Récupérer les événements SDL
        while (SDL_PollEvent(&event))
        {
            // Vérifier si l'utilisateur a cliquer sur la croix X
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                // Déterminer sur quelle fenêtre l'utilisateur a cliquer sur la croix X
                if (SDL_GetWindowID(window_1) == event.window.windowID)
                {
                    cleanup(renderer_1, window_1);
                    quit_1 = true;
                }

                if (SDL_GetWindowID(window_2) == event.window.windowID)
                {
                    cleanup(renderer_2, window_2);
                    quit_2 = true;
                }
            }
        }

        // Préparer les données de la courbe à tracer
        std::vector<std::vector<double>> red_curve_1 = {{0, 0}, {1, 1}, {2, 4}, {3, 9}, {4, 16}};

        // Préparer les données de la courbe à tracer
        std::vector<std::vector<double>> blue_curbe_1 = {{0, 0}, {3, 3}, {4, 8}, {7, 11}, {9, 18}};

        // Tracer la courbe
        sdl_1.draw_curve(red_curve_1, green);

        // Tracer la courbe
        sdl_1.draw_curve(blue_curbe_1, blue);

        // Mettre à jour le renderer
        sdl_1.show();

        // Préparer les données de la courbe à tracer
        std::vector<std::vector<double>> red_curve_2 = {{0, 0}, {4, 6}, {7, 4}, {5, 9}, {2, 6}};

        // Préparer les données de la courbe à tracer
        std::vector<std::vector<double>> blue_curbe_2 = {{0, 0}, {2, 3}, {5, 5}, {6, 10}, {10, 13}};

        // Tracer la courbe
        sdl_2.draw_curve(red_curve_2, green);

        // Tracer la courbe
        sdl_2.draw_curve(blue_curbe_2, blue);

        // Mettre à jour le renderer
        sdl_2.show();
    }

    // Quitter le SDL
    SDL_Quit();
    
    return 0;
}
