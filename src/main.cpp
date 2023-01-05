/**
 * @file main.cpp
 * @brief Fichier principal contenant la fonction main()
 *
 * Ce fichier contient la fonction main() du programme, qui permet de résoudre l'EDP Complete et l'EDP Réduite pour différentes options 
 * (put et call) en utilisant les méthodes de différences finies Implicite et le schéma de Crank Nicholson
 */

#include "diff_finies.h" // Pour les déclarations de la classe DifferencesFinies
#include "sdl.h" // Pour les déclarations de la classe Sdl

const int SCREEN_WIDTH = 640; // Nombre de pixel sur la largeur de l'écran
const int SCREEN_HEIGHT = 480; // Nombre de pixel sur la hauteur de l'écran

const std::vector<Uint8> red = {255, 0, 0}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur rouge
const std::vector<Uint8> green = {0, 255, 0}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur verte
const std::vector<Uint8> blue = {0, 0, 255}; // Vecteur de trois entiers non signés de 8 bits représentant la couleur bleu

/**
 * @brief Fonction main du programme
 *
 * Cette fonction définit les paramètres de l'EDP Complete et de l'EDP Réduite, ainsi que les valeurs du temps et de l'actif S pour lesquelles on calcule la solution
 * Elle crée également des instances des classes EDP Complete, EDP Réduite, Put et Call, et appelle les méthodes de résolution de l'EDP Complete et de l'EDP Réduite 
 * Enfin, elle affiche les solutions obtenues
 *
 * @return 0 si l'exécution s'est bien déroulée, autre chose sinon
 */
int main()
{    
    /********** Définition des paramètres **********/

    // Définition des paramètres de l'EDP de Black Scholes
    const double T = 1;
    const double r = 0.1;
    const double sigma = 0.1;
    const double K = 100;
    const double L = 300;
    const double M = 1000;
    const double N = 1000;
    const double dt = T / M;
    const double dS = L / N;

    // Définition des valeurs du temps t pour lesquelles on calcule la solution
    std::vector<double> t(M+1);
    for (int i = 0; i <= M; i++)
    {
        t[i] = i * dt;
    }

    // Définition des valeurs de l'actif S pour lesquelles on calcule la solution
    std::vector<double> S(N+1);
    for (int j = 0; j <= N; j++)
    {
        S[j] = j * dS;
    }

    /********** Instanciation des options put et call **********/

    // Création d'une instance de l'option put
    Put option_put(K, T, L, r, sigma);

    // Création d'une instance de l'option call
    Call option_call(K, T, L, r, sigma);

    /********** Instanciation des équations aux dérivées partielles **********/

    // Création d'une instance de l'EDP Complete pour un put
    EDPComplete edp_complete_put(option_put);

    // Création d'une instance de l'EDP Complete pour un call
    EDPComplete edp_complete_call(option_call);
    
    // Création d'une instance de l'EDP Réduite pour un put
    EDPReduite edp_reduite_put(option_put);

    // Création d'une instance de l'EDP Réduite pour un call
    EDPReduite edp_reduite_call(option_call);

    /********** Résolution des équations aux dérivées partielles pour un put **********/
    
    // Résolution de l'EDP Complete avec la méthode de Crank Nicholson pour un put
    CrankNicholson solver_complete_put(edp_complete_put, S, t);
    std::vector<std::vector<double>> solution_complete_put = solver_complete_put.solve();

    // Résolution de l'EDP Réduite avec la méthode Implicite pour un put
    Implicite solver_reduite_put(edp_reduite_put, S, t);
    std::vector<std::vector<double>> solution_reduite_put = solver_reduite_put.solve();

    // Calcul de l'erreur entre l'EDP Complete et l'EDP Réduite pour un put pour C(0,.)
    std::vector<double> error_put(solution_complete_put[0].size());
    for (size_t j = 0; j < solution_complete_put[0].size(); j++)
    {
        error_put[j] = solution_complete_put[0][j] - solution_reduite_put[0][j];
    }

    /********** Résolution des équations aux dérivées partielles pour un call **********/

    // Résolution de l'EDP Complete avec la méthode de Crank Nicholson pour un call
    CrankNicholson solver_complete_call(edp_complete_call, S, t);
    std::vector<std::vector<double>> solution_complete_call = solver_complete_call.solve();

    // Résolution de l'EDP Réduite avec la méthode Implicite pour un call
    Implicite solver_reduite_call(edp_reduite_call, S, t);
    std::vector<std::vector<double>> solution_reduite_call = solver_reduite_call.solve();

    // Calcul de l'erreur entre l'EDP Complete et l'EDP Réduite pour un call pour C(0,.)
    std::vector<double> error_call(solution_complete_call[0].size());
    for (size_t j = 0; j < solution_complete_call[0].size(); j++)
    {
        error_call[j] = solution_complete_call[0][j] - solution_reduite_call[0][j];
    }

    /********** Affichage des solutions et des erreurs matriciellement **********/
    /*
    // Affichage de la solution de l'EDP Complete pour un put
    std::cout << "Solution de l'EDP Complete pour un put :" << std::endl;
    for (size_t i = 0; i < solution_complete_put.size(); i++)
    {
        for (size_t j = 0; j < solution_complete_put[i].size(); j++)
        {
            std::cout << solution_complete_put[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Affichage de la solution de l'EDP Réduite pour un put
    std::cout << "Solution de l'EDP Réduite pour un put :" << std::endl;
    for (size_t i = 0; i < solution_reduite_put.size(); i++)
    {
        for (size_t j = 0; j < solution_reduite_put[i].size(); j++)
        {
            std::cout << solution_reduite_put[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Affichage de l'erreur pour un put pour C(0,.)
    std::cout << "Erreur pour un put pour C(0,.) :" << std::endl;
    for (size_t j = 0; j < solution_complete_put[0].size(); j++)
    {
        std::cout << error_put[j] << " ";
    }
    std::cout << std::endl << std::endl;

    // Affichage de la solution de l'EDP Complete pour un call
    std::cout << "Solution de l'EDP Complete pour un call :" << std::endl;
    for (size_t i = 0; i < solution_complete_call.size(); i++)
    {
        for (size_t j = 0; j < solution_complete_call[i].size(); j++)
        {
            std::cout << solution_complete_call[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Affichage de la solution de l'EDP Réduite pour un call
    std::cout << "Solution de l'EDP Réduite pour un call :" << std::endl;
    for (size_t i = 0; i < solution_reduite_call.size(); i++)
    {
        for (size_t j = 0; j < solution_reduite_call[i].size(); j++)
        {
            std::cout << solution_reduite_call[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Affichage de l'erreur pour un call pour C(0,.)
    std::cout << "Erreur pour un call pour C(0,.) :" << std::endl;
    for (size_t j = 0; j < solution_complete_call[0].size(); j++)
    {
        std::cout << error_call[j] << " ";
    }
    std::cout << std::endl << std::endl;
    */

    /********** Affichage des solutions et des erreurs avec SDL **********/

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return -1;
    }

    // Création de la fenêtre pour l'affichage du put
    SDL_Window* window_put = init_window("Solution de l'EDP de Black Scholes pour un Put", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer pour l'affichage du put
    SDL_Renderer* renderer_put = init_renderer(window_put);

    // Création de la fenêtre pour l'affichage de l'erreur pour un put
    SDL_Window* window_error_put = init_window("Erreur entre les solutions des EDP de Black Scholes pour un Put", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer pour l'affichage du error_put
    SDL_Renderer* renderer_error_put = init_renderer(window_error_put);

    // Création de la fenêtre pour l'affichage du call
    SDL_Window* window_call = init_window("Solution de l'EDP de Black Scholes pour un Call", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer pour l'affichage du call
    SDL_Renderer* renderer_call = init_renderer(window_call);

    // Création de la fenêtre pour l'affichage de l'erreur pour un call
    SDL_Window* window_error_call = init_window("Erreur entre les solutions des EDP de Black Scholes pour un Call", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du renderer pour l'affichage du error_call
    SDL_Renderer* renderer_error_call = init_renderer(window_error_call);

    // Création d'une instance de la classe Sdl pour l'affichage du put
    Sdl sdl_put(renderer_put, window_put);

    // Création d'une instance de la classe Sdl pour l'erreur entre l'EDP Complete et l'EDP Réduite pour un put
    Sdl sdl_error_put(renderer_error_put, window_error_put);

    // Création d'une instance de la classe Sdl pour l'affichage du call
    Sdl sdl_call(renderer_call, window_call);

    // Création d'une instance de la classe Sdl pour l'erreur entre l'EDP Complete et l'EDP Réduite pour un call
    Sdl sdl_error_call(renderer_error_call, window_error_call);

    // Déclaration des paramètres pour la gestion de la fermeture des fenêtres
    bool quit_put = false;
    bool quit_error_put = false;
    bool quit_call = false;
    bool quit_error_call = false;
    SDL_Event event;

    // Gestion de la fermeture des fenêtres
    while (!(quit_put && quit_error_put && quit_call && quit_error_call))
    {
        // Récupération des événements SDL
        while (SDL_PollEvent(&event))
        {
            // Si l'utilisateur souhaite fermer une fenêtre c'est à dire s'il a cliqué sur X
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                // Si l'utilisateur souhaite fermer la fenêtre des solutions pour un put
                if (SDL_GetWindowID(window_put) == event.window.windowID)
                {
                    cleanup(renderer_put, window_put); // Nettoyage de la fenêtre
                    quit_put = true;
                }

                // Si l'utilisateur souhaite fermer la fenêtre des erreurs pour un put
                if (SDL_GetWindowID(window_error_put) == event.window.windowID)
                {
                    cleanup(renderer_error_put, window_error_put); // Nettoyage de la fenêtre
                    quit_error_put = true;
                }

                // Si l'utilisateur souhaite fermer la fenêtre des solutions pour un call
                if (SDL_GetWindowID(window_call) == event.window.windowID)
                {
                    cleanup(renderer_call, window_call); // Nettoyage de la fenêtre
                    quit_call = true;
                }

                // Si l'utilisateur souhaite fermer la fenêtre des erreur pour un call
                if (SDL_GetWindowID(window_error_call) == event.window.windowID)
                {
                    cleanup(renderer_error_call, window_error_call); // Nettoyage de la fenêtre
                    quit_error_call = true;
                }
            }
        }

        // Affichage de la courbe de la solution de l'EDP Complete pour un put
        sdl_put.draw_curve(t, solution_complete_put[0], green);

        // Affichage de la courbe de la solution de l'EDP Réduite pour un put
        sdl_put.draw_curve(t, solution_reduite_put[0], blue);

        // Affichage la fenêtre SDL
        sdl_put.show();

        // Affichage de la courbe de l'erreur entre l'EDP Complete et l'EDP Réduite pour un put
        sdl_error_put.draw_curve(t, error_put, red);

        // Affichage la fenêtre SDL
        sdl_error_put.show();

        // Affichage de la courbe de la solution de l'EDP Complete pour un call
        sdl_call.draw_curve(t, solution_complete_call[0], green);

        // Affichage de la courbe de la solution de l'EDP Réduite pour un call
        sdl_call.draw_curve(t, solution_reduite_call[0], blue);

        // Affichage la fenêtre SDL
        sdl_call.show();

        // Affichage de la courbe de l'erreur entre l'EDP Complete et l'EDP Réduite pour un call
        sdl_error_call.draw_curve(t, error_call, red);

        // Afficher la fenêtre SDL
        sdl_error_call.show();
    }

    // Fermeture de SDL
    SDL_Quit();
    
    return 0;
}
