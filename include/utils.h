//
// Created by Geovany on 4/23/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Convertit "Yes"/"No" en bool
bool stringToBool(const std::string& str);

// Convertit bool en "Yes"/"No"
std::string boolToString(bool value);

// Nettoie les espaces autour d'une string
std::string trim(const std::string& str);

// Split une chaîne par un délimiteur (par ex. pour lire les CSV)
std::vector<std::string> split(const std::string& str, char delimiter);

// Vérifie si une chaîne est un entier
bool isNumber(const std::string& str);

// Met une string en majuscules (utile pour comparaison)
std::string toUpper(const std::string& str);

// Génère un ID unique basé sur un compteur ou timestamp (simple ID unique)
std::string generateUniqueID();

// Renvoie la date et l'heure actuelle au format "YYYY-MM-DD HH:MM"
std::string getCurrentDateTime();

#endif //UTILS_H
