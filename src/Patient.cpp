#include "../include/patient.h"
#include "../include/utils.h"
#include "../include/triagesystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

const std::string DATA_DIR = "data/";

Patient::Patient(std::string firstName, std::string lastName, std::string address,
                 std::string disease, bool fever, bool cough, bool fatigue,
                 bool difficultyBreathing, int age, std::string gender,
                 std::string bloodPressure, std::string cholesterol, std::string outcome)
    : firstName(firstName), lastName(lastName), address(address), disease(disease),
      fever(fever), cough(cough), fatigue(fatigue), difficultyBreathing(difficultyBreathing),
      age(age), gender(gender), bloodPressure(bloodPressure), cholesterol(cholesterol),
      outcome(outcome)
{
    id = generateUniqueID();
    registrationDate = getCurrentDateTime();
    evaluateTriageCategory();
}

void Patient::saveToCSV(const std::string& filename) const {
    std::ofstream file(DATA_DIR + filename, std::ios::app);
    if (file.is_open()) {
        file << id << "," << firstName << "," << lastName << "," << address << ","
             << disease << "," << fever << "," << cough << "," << fatigue << ","
             << difficultyBreathing << "," << age << "," << gender << ","
             << bloodPressure << "," << cholesterol << "," << outcome << ","
             << registrationDate << "," << triageCategory << "\n";
        file.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << " pour l'enregistrement.\n";
    }
}

void Patient::readPatientsFromCSV(const std::string& filename) {
    std::ifstream file(DATA_DIR + filename);
    std::string line;
    if (file.is_open()) {
        std::cout << "📄 Liste des patients enregistrés :\n";
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string value;
            while (std::getline(ss, value, ',')) {
                std::cout << std::setw(15) << std::left << value;
            }
            std::cout << "\n";
        }
        file.close();
    } else {
        std::cerr << "Erreur lors de la lecture du fichier " << filename << "\n";
    }
}

int Patient::getPriorityScore() const {
    return TriageAlgorithm::computePriorityScore(fever, cough, fatigue, difficultyBreathing, age, bloodPressure, cholesterol, outcome);
}

void Patient::evaluateTriageCategory() {
    int score = getPriorityScore();
    triageCategory = TriageAlgorithm::determineCategory(score);
}

void Patient::printDetails() const {
    std::cout << "🧾 Patient ID: " << id << "\n"
              << "Name: " << firstName << " " << lastName << "\n"
              << "Address: " << address << "\n"
              << "Disease: " << disease << "\n"
              << "Symptoms: Fever(" << fever << "), Cough(" << cough
              << "), Fatigue(" << fatigue << "), Breathing(" << difficultyBreathing << ")\n"
              << "Age: " << age << " | Gender: " << gender
              << " | BP: " << bloodPressure << " | Cholesterol: " << cholesterol << "\n"
              << "Outcome: " << outcome << "\n"
              << "Registered on: " << registrationDate << "\n"
              << "Triage Category: " << triageCategory << "\n"
              << "Priority Score: " << getPriorityScore() << "\n"
              << "---------------------------------------------\n";
}

std::string Patient::getID() const {
    return id;
}

std::string Patient::getTriageCategory() const {
    return triageCategory;
}

void Patient::displaySortedPatientsByTriage(const std::string& filename) {
    std::ifstream file(DATA_DIR + filename);
    std::vector<std::vector<std::string>> patients;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erreur d'ouverture de " << filename << "\n";
        return;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> patientData;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            patientData.push_back(field);
        }
        if (!patientData.empty())
            patients.push_back(patientData);
    }
    file.close();

    std::sort(patients.begin(), patients.end(), [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        std::map<std::string, int> priorityMap = { {"Critical", 3}, {"Moderate", 2}, {"Low", 1} };
        return priorityMap[a[15]] > priorityMap[b[15]];
    });

    std::cout << "\n📋 Liste des patients triés par niveau d'urgence :\n";
    for (const auto& p : patients) {
        std::cout << "ID: " << p[0] << " | " << p[1] << " " << p[2]
                  << " | Triage: " << p[15] << " | Enregistré le: " << p[14] << "\n";
    }
}

void Patient::insertPatientAndUpdateDiseases(const Patient& patient) {
    std::ofstream patientFile(DATA_DIR + "patient.csv", std::ios::app);
    if (patientFile.is_open()) {
        patientFile << patient.id << "," << patient.firstName << "," << patient.lastName << ","
                    << patient.address << "," << patient.disease << ","
                    << patient.fever << "," << patient.cough << "," << patient.fatigue << ","
                    << patient.difficultyBreathing << "," << patient.age << ","
                    << patient.gender << "," << patient.bloodPressure << ","
                    << patient.cholesterol << "," << patient.outcome << ","
                    << patient.registrationDate << "," << patient.triageCategory << "\n";
        patientFile.close();
    } else {
        std::cerr << "Erreur lors de l'écriture dans patient.csv\n";
    }

    std::ofstream diseasesFile(DATA_DIR + "diseases.csv", std::ios::app);
    if (diseasesFile.is_open()) {
        diseasesFile << patient.disease << "," << patient.fever << "," << patient.cough << ","
                     << patient.fatigue << "," << patient.difficultyBreathing << ","
                     << patient.age << "," << patient.gender << "," << patient.bloodPressure << ","
                     << patient.cholesterol << "," << patient.outcome << "\n";
        diseasesFile.close();
    } else {
        std::cerr << "Erreur lors de l'écriture dans diseases.csv\n";
    }
}
