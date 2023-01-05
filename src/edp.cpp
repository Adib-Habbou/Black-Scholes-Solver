/**
 * @file edp.cpp
 * @brief Implémentation de la classe abstraite EDP et de ses classes concrètes EDPComplete et EDPReduite
 */

#include "edp.h" // Pour la déclaration de la classe EDP

/**
 * @brief Constructeur de la classe EDP
 * @param option Option associée à l'EDP
 */
EDP::EDP(const Option& option) : option_(option) {}

/**
 * @brief Constructeur de la classe EDPComplete
 * @param option Option associée à l'EDP
 */
EDPComplete::EDPComplete(const Option& option) : EDP(option) {}

/**
 * @brief Constructeur de la classe EDPReduite
 * @param option Option associée à l'EDP
 */
EDPReduite::EDPReduite(const Option& option) : EDP(option) {}
