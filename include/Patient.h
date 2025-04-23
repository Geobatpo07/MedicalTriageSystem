//
// Created by Geovany on 4/23/2025.
//

#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
public:
    Patient(std::string firstName, std::string lastName, std::string address,
            std::string disease, bool fever, bool cough, bool fatigue,
            bool difficultyBreathing, int age, std::string gender,
            std::string bloodPressure, std::string cholesterol, std::string outcome);

    void saveToCSV(const std::string& filename) const;
    static void readPatientsFromCSV(const std::string& filename);
    void printDetails() const;
    std::string getID() const;
    std::string getTriageCategory() const;
    static void displaySortedPatientsByTriage(const std::string& filename);
    static void insertPatientAndUpdateDiseases(const Patient& patient);
    int getPriorityScore() const;

private:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string disease;
    bool fever;
    bool cough;
    bool fatigue;
    bool difficultyBreathing;
    int age;
    std::string gender;
    std::string bloodPressure;
    std::string cholesterol;
    std::string outcome;
    std::string registrationDate;
    std::string triageCategory;

    void evaluateTriageCategory();
};

#endif // PATIENT_H
