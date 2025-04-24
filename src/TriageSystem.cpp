#include "../include/TriageSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>

std::map<std::string, double> TriageAlgorithm::weights;

void TriageAlgorithm::loadWeights(const std::string& weightsFile) {
    std::ifstream file(weightsFile);
    nlohmann::json json_weights;
    file >> json_weights;

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
        std::getline(ss, field, ','); // address
        std::getline(ss, field, ','); // disease
        std::getline(ss, field, ','); p.fever = (field == "1");
        std::getline(ss, field, ','); p.cough = (field == "1");
        std::getline(ss, field, ','); p.fatigue = (field == "1");
        std::getline(ss, field, ','); p.difficultyBreathing = (field == "1");
        std::getline(ss, field, ','); p.age = std::stoi(field);
        std::getline(ss, field, ','); // gender
        std::getline(ss, p.bloodPressure, ',');
        std::getline(ss, p.cholesterol, ',');
        std::getline(ss, field, ','); // outcome
        p.outcome = field;  // Capture the outcome (e.g., Positive/Negative)
        std::getline(ss, field, ','); // registration date
        std::getline(ss, p.triageTime, ',');

        p.score = computeTriageScore(p);
        p.triageCategory = determineCategory(p.score);

        patients.push_back(p);
    }

    return patients;
}

int TriageAlgorithm::computePriorityScore(bool fever, bool cough, bool fatigue,
                                          bool difficultyBreathing, int age,
                                          const std::string& bloodPressure,
                                          const std::string& cholesterol,
                                          const std::string& outcome) {
    int score = 0;
    score += fever ? weights["Fever"] : 0;
    score += cough ? weights["Cough"] : 0;
    score += fatigue ? weights["Fatigue"] : 0;
    score += difficultyBreathing ? weights["DifficultyBreathing"] : 0;
    score += (age >= 65) ? weights["Age"] : 0;
    score += (bloodPressure == "High") ? weights["BloodPressure"] : 0;
    score += (cholesterol == "High") ? weights["Cholesterol"] : 0;

    // Normalisation pour ajuster le score dans une plage de 1 à 10
    double normalizedScore = score / 0.1;
    score += std::max(1, (int)normalizedScore);

    // Ajouter un bonus au score si l'outcome est "Positive"
    if (outcome == "Positive") {
        score += 5; // Ajoute un poids supplémentaire pour les cas positifs
    }

    return score;
}

int TriageAlgorithm::computeTriageScore(const PatientRecord& p) {
    return computePriorityScore(p.fever, p.cough, p.fatigue, p.difficultyBreathing,
                                p.age, p.bloodPressure, p.cholesterol, p.outcome);
}

std::string TriageAlgorithm::determineCategory(int score) {
    if (score >= 6) return "Critical";
    else if (score >= 3) return "Moderate";
    else return "Low";
}

void TriageAlgorithm::processAndDisplayTriage(const std::string& filename) {
    auto patients = loadPatients(filename);

    // Trier les patients par score de priorité
    std::sort(patients.begin(), patients.end(), [](const PatientRecord& a, const PatientRecord& b) {
        return a.score > b.score;
    });

    std::cout << "\nRésultat du triage médical :\n";
    for (const auto& p : patients) {
        std::cout << "ID: " << p.id
                  << " | " << p.firstName << " " << p.lastName
                  << " | Score: " << p.score
                  << " | Triage: " << p.triageCategory
                  << " | Triage Time: " << p.triageTime << "\n";
    }
}
