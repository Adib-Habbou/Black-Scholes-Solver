/**
 * @file diff_finies.h
 * @brief Déclarations de la classe abstraite DifferencesFinies et de ses classes concrètes CrankNicholson et Implicite
 */

#ifndef DIFF_FINIES_H
#define DIFF_FINIES_H

#include "edp.h" // Pour la déclaration de la classe EDP

#include <vector> // Pour std::vector
#include <iostream> // Pour std::cout et std::endl

/**
 * @brief Méthode qui résout un système linéaire de la forme A * sol = b en utilisant une décomposition LU
 * @param x Vecteur représentant la sur-diagonale de la matrice
 * @param x Vecteur représentant la diagonale de la matrice
 * @param x Vecteur représentant la sous-diagonale de la matrice
 * @param b Vecteur du système linéaire
 * @return Vecteur solution sol du système linéaire
 */
std::vector<double> algoThomas(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::vector<double>& b);

/**
 * @brief Classe abstraite représentant une méthode de différences finies pour résoudre une équation différentielle
 */
class DifferencesFinies 
{
    protected:
        EDP& edp_;  // Référence vers l'objet EDP à résoudre
        int M_;     // Nombre de pas de temps
        int N_;     // Nombre de pas d'espace
        double dt_; // Pas de temps
        double dS_; // Pas d'espace
        std::vector<double>& t_; // Valeurs de temps t pour lesquelles on calcule la solution
        std::vector<double>& S_; // Valeurs de l'actif S pour lesquelles on calcule la solution

    public:
        /**
         * @brief Constructeur de la classe DifferencesFinies
         * @param edp Référence vers l'objet EDP à résoudre
         * @param M Nombre de pas de temps
         * @param N Nombre de pas d'espace
         * @param S Valeurs de l'actif S pour lesquelles on calcule la solution
         * @param t Valeurs de temps t pour lesquelles on calcule la solution
         */
        DifferencesFinies(EDP& edp, int M, int N, std::vector<double>& S, std::vector<double>& t);

        /**
        * @brief Getter pour l'objet EDP associé à cette instance de DifferencesFinies
        * @return Référence vers l'objet EDP associé à cette instance de DifferencesFinies
        */
        EDP& getEdp() { return edp_; }

        /**
        * @brief Getter pour le nombre de pas de temps associé à cette instance de DifferencesFinies
        * @return Nombre de pas de temps associé à cette instance de DifferencesFinies
        */
        double getM() { return M_; }

        /**
        * @brief Getter pour le nombre de pas d'espace associé à cette instance de DifferencesFinies
        * @return Nombre de pas d'espace associé à cette instance de DifferencesFinies
        */
        double getN() { return N_; }
};

/**
 * @brief Classe concrète qui implémente la méthode de Crank Nicholson pour résoudre l'EDP complète de Black Scholes
 */
class CrankNicholson : public DifferencesFinies 
{
    public:
        /**
         * @brief Constructeur de la classe CrankNicholson
         * @param edp EDP complète à résoudre
         * @param S Valeurs de l'actif S pour lesquelles on calcule la solution
         * @param t Valeurs du temps t pour lesquelles on calcule la solution
         */
        CrankNicholson(EDPComplete& edp, std::vector<double>& S, std::vector<double>& t);

        /**
         * @brief Méthode qui résout l'EDP complète en utilisant la méthode de Crank Nicholson
         * @return Matrice des valeurs de la solution de l'EDP complète aux différentes valeurs de S et t
         */
        std::vector<std::vector<double>> solve();
};

/**
 * @brief Classe concrète qui implémente la méthode Implicite pour résoudre l'EDP réduite de Black Scholes
 */
class Implicite : public DifferencesFinies 
{
    public:
        /**
         * @brief Constructeur de la classe Implicite
         * @param edp EDP réduite à résoudre
         * @param S Valeurs de l'actif S pour lesquelles on calcule la solution
         * @param t Valeurs du temps t pour lesquelles on calcule la solution
         */
        Implicite(EDPReduite& edp, std::vector<double>& S, std::vector<double>& t);

        /**
         * @brief Méthode qui résout l'EDP réduite en utilisant la méthode Implicite
         * @return Matrice des valeurs de la solution de l'EDP réduite aux différentes valeurs de S et t
         */
        std::vector<std::vector<double>> solve();
};

#endif  // DIFF_FINIES_H
