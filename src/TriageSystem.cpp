//
// Created by Geovany on 4/23/2025.
//

#include "../include/TriageSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>

std::map<std::string, double> TriageAlgorithm::weights;

void TriageAlgorithm::loadWeights(const std::string& weightsFile) {
    // Lire le fichier JSON contenant les poids
    std::ifstream file(weightsFile);
    nlohmann::json json_weights;
    file >> json_weights;

    // Charger les poids dans la map
    for (auto& element : json_weights.items()) {
        weights[element.key()] = element.value();
    }
}

std::vector<PatientRecord> TriageAlgorithm::loadPatients(const std::string& filename) {
    std::vector<PatientRecord> patients;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        PatientRecord p;

        std::getline(ss, p.id, ',');
        std::getline(ss, p.firstName, ',');
        std::getline(ss, p.lastName, ',');
        std::getline(ss, field, ','); // Skip address
        std::getline(ss, field, ','); // Skip disease
        std::getline(ss, field, ','); p.fever = (field == "1");
        std::getline(ss, field, ','); p.cough = (field == "1");
        std::getline(ss, field, ','); p.fatigue = (field == "1");
        std::getline(ss, field, ','); p.difficultyBreathing = (field == "1");
        std::getline(ss, field, ','); p.age = std::stoi(field);
        std::getline(ss, field, ','); // Gender
        std::getline(ss, p.bloodPressure, ',');
        std::getline(ss, p.cholesterol, ',');
        std::getline(ss, field, ','); // Outcome
        std::getline(ss, field, ','); // Registration date
        std::getline(ss, p.triageTime, ','); // Triage time

        p.score = computeTriageScore(p);
        p.triageCategory = determineCategory(p.score);

        patients.push_back(p);
    }

    return patients;
}

int TriageAlgorithm::computeTriageScore(const PatientRecord& p) {
    int score = 0;

    // Calculer le score avec les poids du modèle Random Forest
    score += p.fever ? weights["Fever"] : 0;
    score += p.cough ? weights["Cough"] : 0;
    score += p.fatigue ? weights["Fatigue"] : 0;
    score += p.difficultyBreathing ? weights["DifficultyBreathing"] : 0;
    score += (p.age >= 65) ? weights["Age"] : 0;
    score += (p.bloodPressure == "High") ? weights["BloodPressure"] : 0;
    score += (p.cholesterol == "High") ? weights["Cholesterol"] : 0;

    return score;
}

std::string TriageAlgorithm::determineCategory(int score) {
    if (score >= 6) return "Critical";
    else if (score >= 3) return "Moderate";
    else return "Low";
}

void TriageAlgorithm::processAndDisplayTriage(const std::string& filename) {
    auto patients = loadPatients(filename);

    std::sort(patients.begin(), patients.end(), [](const PatientRecord& a, const PatientRecord& b) {
        return a.score > b.score;
    });

    std::cout << "\n🔍 Résultat du triage médical :\n";
    for (const auto& p : patients) {
        std::cout << "ID: " << p.id
                  << " | " << p.firstName << " " << p.lastName
                  << " | Score: " << p.score
                  << " | Triage: " << p.triageCategory
                  << " | Triage Time: " << p.triageTime << "\n";
    }
}

