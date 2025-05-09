//
// Created by Geovany on 4/23/2025.
//

#ifndef TRIAGESYSTEM_H
#define TRIAGESYSTEM_H

#include <string>
#include <vector>
#include <map>

struct PatientRecord {
    std::string id;
    std::string firstName;
    std::string lastName;
    bool fever;
    bool cough;
    bool fatigue;
    bool difficultyBreathing;
    int age;
    std::string bloodPressure;
    std::string cholesterol;
    int score;
    std::string triageCategory;
    std::string triageTime;
    std::string outcome;  // Ajout du champ outcome
};

// Classe pour gérer la logique du triage
class TriageAlgorithm {
public:
    static void loadWeights(const std::string& weightsFile);
    static std::vector<PatientRecord> loadPatients(const std::string& filename);
    static int computeTriageScore(const PatientRecord& p);
    static std::string determineCategory(int score);
    static void processAndDisplayTriage(const std::string& filename);
    static int computePriorityScore(bool fever, bool cough, bool fatigue,
                                    bool difficultyBreathing, int age,
                                    const std::string& bloodPressure,
                                    const std::string& cholesterol,
                                    const std::string& outcome);  // Mise à jour

private:
    static std::map<std::string, double> weights; // Poids pour chaque caractéristique

};

#endif // TRIAGESYSTEM_H
