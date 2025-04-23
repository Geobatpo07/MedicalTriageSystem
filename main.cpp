//
// Created by Geovany on 4/23/2025.
//

#include <iostream>
#include "../include/patient.h"
#include "../include/triagesystem.h"

int main() {
    std::cout << "=== 🏥 Système de Triage Médical ===\n";

    // Exemple de création d'un patient
    Patient p(
        "Alice",                    // Prénom
        "Martin",                   // Nom
        "123 rue des Lilas",        // Adresse
        "Pneumonie",                // Maladie
        true,                       // Fièvre
        true,                       // Toux
        true,                       // Fatigue
        true,                       // Difficulté respiratoire
        75,                         // Âge
        "Femme",                    // Sexe
        "Élevée",                   // Pression artérielle
        "Élevé",                    // Cholestérol
        "Guérison en cours"         // Issue
    );

    // Application du système de triage
    TriageSystem::assignPriorityAndCategory(p);

    // Affichage des détails du patient (avec priorité et catégorie assignées)
    p.printDetails();

    // Sauvegarde dans le CSV des patients
    p.saveToCSV("data/patients.csv");

    // Mise à jour du fichier des maladies
    Patient::insertPatientAndUpdateDiseases(p);

    // Lecture et affichage de tous les patients enregistrés
    std::cout << "\n🔎 Tous les patients enregistrés :\n";
    Patient::readPatientsFromCSV("data/patients.csv");

    // Affichage trié par niveau d'urgence
    std::cout << "\n📊 Patients triés par niveau d'urgence :\n";
    Patient::displaySortedPatientsByTriage("data/patients.csv");

    std::cout << "\n✅ Fin du programme.\n";
    return 0;
}
