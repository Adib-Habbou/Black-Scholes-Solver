/**
 * @file sdl.cpp
 * @brief Implémentation de la classe Sdl
 */

#include "sdl.h" // Pour la déclaration de la classe Sdl
 
/**
 * @brief Initialise la fenêtre SDL
 * @param title Titre de la fenêtre
 * @param width Largeur de la fenêtre en pixels
 * @param height Hauteur de la fenêtre en pixels
 * @return Pointeur vers la fenêtre SDL créée, ou nullptr en cas d'erreur
 */
SDL_Window* init_window(const std::string& title, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cout << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return window;
}

/**
 * @brief Initialise le renderer SDL
 * @param window Fenêtre SDL à utiliser pour le renderer
 * @return Pointeur vers le renderer SDL créé, ou nullptr en cas d'erreur
 */
SDL_Renderer* init_renderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (renderer == nullptr)
    {
        std::cout << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return renderer;
}

/**
* @brief Détruit le renderer et le window
*/
void cleanup(SDL_Renderer* renderer, SDL_Window* window)
{
    // Détruire le renderer
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    // Détruire la fenêtre
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

/**
 * @brief Constructeur par défaut
 */
Sdl::Sdl() : renderer_(nullptr), window_(nullptr) {} // Initialisation de renderer_ et window_ avec nullptr

/**
 * @brief Constructeur
 * @param renderer Renderer SDL à utiliser pour dessiner les courbes
 * @param window Window SDL à utiliser pour dessiner les courbes
 */
Sdl::Sdl(SDL_Renderer* renderer, SDL_Window* window) : renderer_(renderer), window_(window) {}

/**
 * @brief Affiche une courbe dans la fenêtre
 * @param V Matrice contenant les coordonnées de la courbe (chaque ligne représente un point de la courbe et doit contenir : la coordonnée x et la coordonnée y)
 * @param color Couleur de la courbe, sous la forme d'un vecteur de trois entiers non signés de 8 bits
 */
void Sdl::draw_curve(const std::vector<std::vector<double>>& V, const std::vector<Uint8>& color)
{
    // Calculer les dimensions de la fenêtre
    int window_width = 640;
    int window_height = 480;

    // Définir les marges (en pixels) autour de la courbe
    const int margin = 20;

    // Calculer les dimensions de la zone de dessin (en pixels)
    const int draw_width = window_width - 2 * margin;
    const int draw_height = window_height - 2 * margin;

    // Calculer les bornes de l'axe des x et des y (en unités de la courbe)
    double xmin = V[0][0];
    double xmax = V[0][0];
    double ymin = V[0][1];
    double ymax = V[0][1];
    for (const auto& point : V)
    {
        xmin = std::min(xmin, point[0]);
        xmax = std::max(xmax, point[0]);
        ymin = std::min(ymin, point[1]);
        ymax = std::max(ymax, point[1]);
    }

    // Calculer les échelles de l'axe des x et des y (en pixels/unité)
    const double xscale = static_cast<double>(draw_width) / (xmax - xmin);
    const double yscale = static_cast<double>(draw_height) / (ymax - ymin);

    // Définir la couleur de la courbe
    SDL_SetRenderDrawColor(renderer_, color[0], color[1], color[2], 255);

    // Tracer la courbe
    for (std::size_t i = 1; i < V.size(); ++i)
    {
        // Calculer les coordonnées en pixels des points de la courbe
        int x1 = static_cast<int>(margin + (V[i - 1][0] - xmin) * xscale);
        int y1 = static_cast<int>(window_height - margin - (V[i - 1][1] - ymin) * yscale);
        int x2 = static_cast<int>(margin + (V[i][0] - xmin) * xscale);
        int y2 = static_cast<int>(window_height - margin - (V[i][1] - ymin) * yscale);

        // Tracer une ligne entre les points de la courbe
        SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
    }
}

/**
 * @brief Met à jour le renderer
 */
void Sdl::show()
{
    SDL_RenderPresent(renderer_);
}
