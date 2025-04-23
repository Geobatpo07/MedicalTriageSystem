@echo off
echo === Compilation de l'application MedicalTriageApp ===

REM Création du dossier bin s'il n'existe pas
if not exist bin (
    mkdir bin
)

REM Compilation avec g++
g++ -std=c++17 -Iinclude -Isrc ^
    src/main.cpp src/patient.cpp src/triagesystem.cpp ^
    -o bin/MedicalTriageApp.exe

if %errorlevel% neq 0 (
    echo Erreur lors de la compilation.
) else (
    echo Compilation réussie. Exécutable créé : bin\MedicalTriageApp.exe
)
