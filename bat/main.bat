@echo off
REM Fichier de gestion du triage médical
REM Ce fichier permet de gérer les patients et leurs informations médicales

:MENU
cls
echo ============================
echo 1. Ajouter un nouveau patient
echo 2. Afficher la liste des patients
echo 3. Trier les patients par urgence
echo 4. Supprimer un patient
echo 5. Modifier un patient
echo 6. Quitter
echo ============================
set /p choice=Choisir une option (1-6) :

if "%choice%"=="1" goto ADD_PATIENT
if "%choice%"=="2" goto VIEW_PATIENTS
if "%choice%"=="3" goto SORT_PATIENTS
if "%choice%"=="4" goto DELETE_PATIENT
if "%choice%"=="5" goto MODIFY_PATIENT
if "%choice%"=="6" exit

:ADD_PATIENT
cls
echo Ajouter un nouveau patient :
set /p firstName=Prénom :
set /p lastName=Nom :
set /p address=Adresse :
set /p disease=Maladie :
set /p fever=Fievre (1 pour oui, 0 pour non) :
set /p cough=Toux (1 pour oui, 0 pour non) :
set /p fatigue=Fatigue (1 pour oui, 0 pour non) :
set /p difficultyBreathing=Diff. respiratoire (1 pour oui, 0 pour non) :
set /p age=Age :
set /p gender=Sexe :
set /p bloodPressure=Pression sanguine (Low/Normal/High) :
set /p cholesterol=Cholestérol (Low/Normal/High) :
set /p outcome=Issue (Positif/Negatif) :

REM Enregistrer les informations du patient dans le fichier CSV
echo %firstName%,%lastName%,%address%,%disease%,%fever%,%cough%,%fatigue%,%difficultyBreathing%,%age%,%gender%,%bloodPressure%,%cholesterol%,%outcome% >> data/patient.csv

echo Le patient a été ajouté avec succès.
pause
goto MENU

:VIEW_PATIENTS
cls
echo Liste des patients :
type data/patient.csv
pause
goto MENU

:SORT_PATIENTS
cls
echo Tri des patients par niveau d'urgence :
REM Tri des patients par priorité (fichier CSV)
type data/patient.csv | sort > sorted_patients.txt
type sorted_patients.txt
pause
goto MENU

:DELETE_PATIENT
cls
echo Supprimer un patient :
set /p patientID=Entrez l'ID du patient à supprimer :

REM Filtrer et supprimer l'enregistrement du patient (ne pas conserver la ligne avec l'ID donné)
findstr /v "%patientID%" data/patient.csv > data/temp.csv
move /y data/temp.csv data/patient.csv

echo Le patient avec l'ID %patientID% a été supprimé avec succès.
pause
goto MENU

:MODIFY_PATIENT
cls
echo Modifier un patient :
set /p patientID=Entrez l'ID du patient à modifier :

REM Vérifier si l'ID existe et lire les informations du patient
findstr /i "%patientID%" data/patient.csv > data/temp_patient.txt
if %errorlevel% neq 0 (
    echo Aucun patient avec cet ID trouvé.
    pause
    goto MENU
)

REM Afficher les informations actuelles du patient
echo Voici les informations actuelles du patient avec l'ID %patientID% :
type data/temp_patient.txt

REM Demander les nouvelles informations pour le patient
echo Entrez les nouvelles informations pour le patient (laisser vide pour garder la valeur existante) :
set /p newFirstName=Prénom (%patientID%) :
set /p newLastName=Nom (%patientID%) :
set /p newAddress=Adresse :
set /p newDisease=Maladie :
set /p newFever=Fievre (1 pour oui, 0 pour non) :
set /p newCough=Toux (1 pour oui, 0 pour non) :
set /p newFatigue=Fatigue (1 pour oui, 0 pour non) :
set /p newDifficultyBreathing=Diff. respiratoire (1 pour oui, 0 pour non) :
set /p newAge=Age :
set /p newGender=Sexe :
set /p newBloodPressure=Pression sanguine (Low/Normal/High) :
set /p newCholesterol=Cholestérol (Low/Normal/High) :
set /p newOutcome=Issue (Positif/Negatif) :

REM Modifier le fichier CSV en remplaçant l'ancienne ligne par la nouvelle
echo %newFirstName%,%newLastName%,%newAddress%,%newDisease%,%newFever%,%newCough%,%newFatigue%,%newDifficultyBreathing%,%newAge%,%newGender%,%newBloodPressure%,%newCholesterol%,%newOutcome% >> data/temp.csv
findstr /v "%patientID%" data/patient.csv >> data/temp.csv
move /y data/temp.csv data/patient.csv

echo Le patient avec l'ID %patientID% a été mis à jour avec succès.
pause
goto MENU
