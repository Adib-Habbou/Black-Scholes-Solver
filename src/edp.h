/**
 * @file edp.h
 * @brief Déclarations de la classe abstraite EDP et de ses classes concrètes EDPComplète et EDPRéduite
 */

#ifndef EDP_H
#define EDP_H

#include "option.h" // Pour la déclaration de la classe Option

/**
 * @brief Classe abstraite représentant une équation différentielle aux dérivées partielles pour une option
 */
class EDP
{
    protected:
        const Option& option_;  // Option associée à l'EDP
            
    public:
        /**
        * @brief Constructeur de la classe EDP
        * @param option Option associée à l'EDP
        */
        EDP(const Option& option);

        /**
        * @brief Getter de l'option associée à l'EDP
        * @return Référence constante vers l'option associée à l'EDP
        */
        const Option& getOption() const { return option_; }
};

/**
 * @brief Classe concrète représentant l'EDP complète
 */
class EDPComplete : public EDP 
{
    public:
        /**
        * @brief Constructeur de la classe EDPComplete
        * @param option Option associée à l'EDP
        */
        EDPComplete(const Option& option);
};

/**
 * @brief Classe concrète représentant l'EDP réduite
 */
class EDPReduite : public EDP 
{
    public:
        /**
        * @brief Constructeur de la classe EDPReduite
        * @param option Option associée à l'EDP
        */
        EDPReduite(const Option& option);
};

#endif  // EDP_H
