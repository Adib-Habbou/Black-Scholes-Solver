/**
 * @file diff_finies.cpp
 * @brief Implémentation de la classe abstraite DifferencesFinies et de ses classes concrètes CrankNicholson et Implicite
 */

#include "diff_finies.h" // Pour la déclaration de la classe DifferencesFinies

/**
 * @brief Méthode qui résout un système linéaire de la forme A * sol = b en utilisant l'algorithme de Thomas
 * @param x Vecteur représentant la sous-diagonale de la matrice
 * @param y Vecteur représentant la diagonale de la matrice
 * @param z Vecteur représentant la sur-diagonale de la matrice
 * @param b Vecteur du système linéaire
 * @return Vecteur solution sol du système linéaire
 */
std::vector<double> algoThomas(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::vector<double>& b)
{
    // Taille du système
    int n = b.size();

    // Vecteurs temporaires utilisés par l'algorithme de Thomas
    std::vector<double> c(n);
    std::vector<double> d(n);

    // On effectue la décomposition LU de la matrice A en utilisant l'algorithme de Thomas
    c[0] = z[0] / y[0];
    d[0] = b[0] / y[0];
    for (int i = 1; i < n; i++)
    {
        c[i] = z[i] / (y[i] - x[i] * c[i-1]);
        d[i] = (b[i] - x[i] * d[i-1]) / (y[i] - x[i] * c[i-1]);
    }

    // Vecteur sol de la solution du système A * sol = b
    std::vector<double> sol(n);

    // On résout le système A * sol = b en utilisant la décomposition LU
    sol[n-1] = d[n-1];
    for (int i = n-2; i >= 0; i--)
    {
        sol[i] = d[i] - c[i] * sol[i+1];
    }

    return sol;
}

/**
* @brief Constructeur de la classe DifferencesFinies
* @param edp Référence vers l'objet EDP à résoudre
* @param M Nombre de pas de temps
* @param N Nombre de pas d'espace
* @param S Valeurs de l'actif S pour lesquelles on calcule la solution
* @param t Valeurs de temps t pour lesquelles on calcule la solution
 */
DifferencesFinies::DifferencesFinies(EDP& edp, int M, int N, std::vector<double>& S, std::vector<double>& t) : edp_(edp), M_(M), N_(N), t_(t), S_(S)
{
    // Calcul du pas de temps et du pas d'espace
    dt_ = edp_.getOption().getT() / M_;
    dS_ = edp_.getOption().getL() / N_;
}

/**
* @brief Constructeur de la classe CrankNicholson
* @param edp EDP complète à résoudre
* @param S Valeurs de l'actif S pour lesquelles on calcule la solution
* @param t Valeurs du temps t pour lesquelles on calcule la solution
 */
CrankNicholson::CrankNicholson(EDPComplete& edp, std::vector<double>& S, std::vector<double>& t) : DifferencesFinies(edp, t.size()-1, S.size()-1, S, t) {}

/**
* @brief Méthode qui résout l'EDP complète en utilisant la méthode de Crank Nicholson
* @return Matrice des valeurs de la solution de l'EDP complète aux différentes valeurs de S et t
 */
std::vector<std::vector<double>> CrankNicholson::solve()
{
    // On récupère les paramètres de l'EDP
    double r = getEdp().getOption().getR();
    double sigma = getEdp().getOption().getSigma();
    double M = getM();
    double N = getN();

    // On initialise les vecteurs de la matrice tridiagonale
    std::vector<double> x(N+1);
    std::vector<double> y(N+1);
    std::vector<double> z(N+1);

    // On calcule les coefficients x, y et z
    for (int j = 0; j <= N; j++)
    {
        x[j] = dt_ * ((j+1) / (2 * dS_) * (r - sigma * sigma / dS_));
        y[j] = dt_ * (1.0 / dt_ + sigma * sigma * (j+1) * (j+1) / (dS_ * dS_) + r);
        z[j] = dt_ * (-(j+1) / (2 * dS_) * (r + sigma * sigma / dS_));
    }

    // On initialise la matrice C avec les conditions aux bords et terminale
    std::vector<std::vector<double>> C(N+1, std::vector<double>(M+1));
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            C[i][j] = getEdp().getOption().payoff(S_[j], t_[i]);
        }
    }

    // On calcule les valeurs de C en utilisant la méthode de Crank Nicholson
    for (int i = M-1; i >= 0; i--)
    {
        std::vector<double> solution = algoThomas(x, y, z, C[i+1]);
        for (int j = 1; j < N; j++)
        {
            C[i][j] = solution[j];
        }
    }

    return C;
}

/**
* @brief Constructeur de la classe Implicite
* @param edp EDP réduite à résoudre
* @param S Valeurs de l'actif S pour lesquelles on calcule la solution
* @param t Valeurs du temps t pour lesquelles on calcule la solution
 */
Implicite::Implicite(EDPReduite& edp, std::vector<double>& S, std::vector<double>& t) : DifferencesFinies(edp, t.size()-1, S.size()-1, S, t) {}

/**
* @brief Méthode qui résout l'EDP réduite en utilisant la méthode Implicite
* @return Matrice des valeurs de la solution de l'EDP réduite aux différentes valeurs de S et t
 */
std::vector<std::vector<double>> Implicite::solve()
{
    // On récupère les paramètres de l'EDP
    double sigma = getEdp().getOption().getSigma();
    double M = getM();
    double N = getN();

    // On calcule le coefficient lambda
    double lambda = (sigma * sigma * dt_) / (2 * dS_ * dS_);

    // On initialise les vecteurs de la matrice tridiagonale
    std::vector<double> x(N+1);
    std::vector<double> y(N+1);
    std::vector<double> z(N+1);

    // On calcule les coefficients x, y et z
    for (int j = 0; j <= N; j++)
    {
        x[j] = lambda;
        y[j] = 1 - 2 * lambda;
        z[j] = lambda;
    }

    // On initialise la matrice C avec les conditions aux bords et terminale
    std::vector<std::vector<double>> C(N+1, std::vector<double>(M+1));
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            C[i][j] = getEdp().getOption().payoff(S_[j], t_[i]);
        }
    }

    // On calcule les valeurs de C en utilisant la méthode Implicite
    for (int i = M-1; i >= 0; i--)
    {
        // On résout le système linéaire P1 * C[i] = C[i+1]
        std::vector<double> solution = algoThomas(x, y, z, C[i+1]);
        for (int j = 1; j < N; j++)
        {
            C[i][j] = solution[j];
        } 
    }

    return C;
}
