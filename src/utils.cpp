//
// Created by Geovany on 4/23/2025.
//

#include "utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>

bool stringToBool(const std::string& str) {
    std::string s = toUpper(trim(str));
    return s == "YES" || s == "TRUE" || s == "1";
}

std::string boolToString(bool value) {
    return value ? "Yes" : "No";
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos)
        ? ""
        : str.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(trim(item));
    }

    return tokens;
}

bool isNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return result;
}

// Génère un ID unique simple basé sur l'heure et un nombre aléatoire
std::string generateUniqueID() {
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();

    // Ajoute un petit nombre aléatoire pour éviter les collisions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1000, 9999);

    return "P" + std::to_string(millis) + std::to_string(dist(gen));
}

// Renvoie la date/heure actuelle au format "YYYY-MM-DD HH:MM"
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M");
    return oss.str();
}