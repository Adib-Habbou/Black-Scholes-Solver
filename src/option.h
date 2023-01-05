/**
 * @file option.h
 * @brief Déclarations de la classe abstraite Option et de ses classes concrètes Put et Call
 */

#ifndef OPTION_H
#define OPTION_H

#include <algorithm> // Pour std::max
#include <cmath> // Pour std::exp

/**
 * @brief Classe abstraite représentant une option
 */
class Option 
{
    protected:
        double K_;  // Strike de l'option
        double T_;  // Temps terminal de l'option
        double L_;  // Valeur terminal de l'option
        double r_;  // Taux d'intérêt du marché
        double sigma_;  // Volatilité de l'actif

    public:
        /**
        * @brief Constructeur de la classe Option
        * @param K Strike de l'option
        * @param T Temps terminal de l'option
        * @param L Valeur terminal de l'option
        * @param r Taux d'intérêt du marché
        * @param sigma Volatilité de l'actif
        */
        Option(double K, double T, double L, double r, double sigma);

        /**
        * @brief Getter du strike de l'option
        * @return Valeur du strike de l'option
        */
        double getK() const { return K_; }

        /**
        * @brief Getter du temps terminal de l'option
        * @return Valeur du temps terminal de l'option
        */
        double getT() const { return T_; }

        /**
        * @brief Getter de la valeur terminal de l'option
        * @return Valeur de la valeur terminal de l'option
        */
        double getL() const { return L_; }

        /**
        * @brief Getter du taux d'intérêt du marché
        * @return Valeur du taux d'intérêt du marché
        */
        double getR() const { return r_; }

        /**
        * @brief Getter de la volatilité de l'actif
        * @return Valeur de la volatilité de l'actif
        */
        double getSigma() const { return sigma_; }

        /**
        * @brief Méthode virtuelle pure qui retourne le payoff de l'option pour une valeur donnée de l'actif
        * @param S Valeur de l'actif en temps t
        * @param t Valeur du temps t
        * @return Payoff de l'option put pour la valeur de l'actif S au temps t
        */
        virtual double payoff(double S, double t) const = 0;
};

/**
 * @brief Classe concrète représentant une option put
 */
class Put : public Option 
{
    public:
        /**
        * @brief Constructeur de la classe Put
        * @param K Strike de l'option
        * @param T Temps terminal de l'option
        * @param L Valeur terminal de l'option
        * @param r Taux d'intérêt du marché
        * @param sigma Volatilité de l'actif
        */
        Put(double K, double T, double L, double r, double sigma);

        /**
        * @brief Implémentation de la méthode virtuelle pure payoff
        * @param S Valeur de l'actif en temps t
        * @param t Valeur du temps t
        * @return Payoff de l'option put pour la valeur de l'actif S au temps t
        */
        double payoff(double S, double t) const override;
};

/**
 * @brief Classe concrète représentant une option call
 */
class Call : public Option 
{
    public:
        /**
        * @brief Constructeur de la classe Call
        * @param K Strike de l'option
        * @param T Temps terminal de l'option
        * @param L Valeur terminal de l'option
        * @param r Taux d'intérêt du marché
        * @param sigma Volatilité de l'actif
        */
        Call(double K, double T, double L, double r, double sigma);

        /**
        * @brief Implémentation de la méthode virtuelle pure payoff
        * @param S Valeur de l'actif en temps t
        * @param t Valeur du temps t
        * @return Payoff de l'option call pour la valeur de l'actif S au temps t
        */
        double payoff(double S, double t) const override;
};

#endif  // OPTION_H
