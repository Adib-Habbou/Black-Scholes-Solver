/**
 * @file sdl.h
 * @brief Déclaration de la classe Sdl
 */

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <vector> // Pour std::vector
#include <string> // Pour std::string
#include <algorithm>  // Pour std::max et std::min
#include <iostream> // Pour std::cout et std::endl
#include <limits> // Pour std::numeric_limits

/**
* @brief Initialise la fenêtre SDL
* @param title Titre de la fenêtre
* @param width Largeur de la fenêtre en pixels
* @param height Hauteur de la fenêtre en pixels
* @return Pointeur vers la fenêtre SDL créée, ou nullptr en cas d'erreur
*/
SDL_Window* init_window(const std::string& title, int width, int height);

/**
* @brief Initialise le renderer SDL
* @param window Fenêtre SDL à utiliser pour le renderer
* @return Pointeur vers le renderer SDL créé, ou nullptr en cas d'erreur
*/
SDL_Renderer* init_renderer(SDL_Window* window);

/**
* @brief Détruit le renderer et le window
*/
void cleanup(SDL_Renderer* renderer, SDL_Window* window);

/**
 * @brief Classe permettant d'afficher des courbes dans une fenêtre SDL
 */
class Sdl
{
    private:
        SDL_Renderer* renderer_; // Renderer SDL utilisé pour dessiner les courbes
        SDL_Window* window_; // Window SDL utilisé pour dessiner les coubres

    public:
        /**
        * @brief Constructeur par défaut
        */
        Sdl();

        /**
        * @brief Constructeur
        * @param renderer Renderer SDL à utiliser pour dessiner les courbes
        * @param window Window SDL à utiliser pour dessiner les courbes
        */
        Sdl(SDL_Renderer* renderer, SDL_Window* window);

        /**
        * @brief Destructeur
        */
        ~Sdl() { cleanup(renderer_, window_); };

        /**
        * @brief Affiche une courbe dans la fenêtre
        * @param x Vecteur correspondant aux abscisses
        * @param y Vecteur correspondant aux odronnées
        * @param color Couleur de la courbe, sous la forme d'un vecteur de trois entiers non signés de 8 bits
        */
        void draw_curve(const std::vector<double>& x, const std::vector<double>& y, const std::vector<Uint8>& color);

        /**
        * @brief Met à jour le renderer
        */
        void show();
};

#endif // SDL_H
