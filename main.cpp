//
// Created by Geovany on 4/23/2025.
//

#include <iostream>
#include "../include/Patient.h"

int main() {
    std::cout << "=== 🏥 Medical Triage System ===\n";

    // Example of creating a patient
    Patient p(
        "Alice",                    // First Name
        "Martin",                   // Last Name
        "123 Lily Street",          // Address
        "Pneumonia",                // Disease
        true,                       // Fever
        true,                       // Cough
        true,                       // Fatigue
        true,                       // Difficulty Breathing
        75,                         // Age
        "Female",                   // Gender
        "High",                     // Blood Pressure
        "High",                     // Cholesterol
        "positive"                  // Outcome
    );

    // The triage category is evaluated internally during construction or save
    // Display patient's details (with priority and category assigned)
    p.printDetails();

    // Save to patients CSV
    p.saveToCSV("data/patients.csv");

    // Update diseases CSV
    Patient::insertPatientAndUpdateDiseases(p);

    // Read and display all registered patients
    std::cout << "\nAll registered patients:\n";
    Patient::readPatientsFromCSV("data/patients.csv");

    // Display sorted patients by triage priority
    std::cout << "\nPatients sorted by triage priority:\n";
    Patient::displaySortedPatientsByTriage("data/patients.csv");

    std::cout << "\nEnd of the program.\n";
    return 0;
}
