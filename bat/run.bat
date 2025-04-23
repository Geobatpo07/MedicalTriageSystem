@echo off
setlocal enabledelayedexpansion

echo === Lancement de l'application MedicalTriageApp ===

REM Définir le chemin de l'exécutable et du fichier de log
set EXE_PATH=bin\MedicalTriageApp.exe
set LOG_FILE=logs\medical_triage_log.txt

REM Créer le dossier 'logs' s'il n'existe pas
if not exist logs (
    mkdir logs
)

REM Vérifier si l'exécutable existe
if exist %EXE_PATH% (
    echo L'exécutable existe, lancement de l'application...

    REM Lancer l'application et rediriger la sortie standard et d'erreur dans le fichier de log
    echo === Début de l'exécution %DATE% %TIME% === >> %LOG_FILE%
    start "" %EXE_PATH% >> %LOG_FILE% 2>&1

    REM Vérifier l'exécution et afficher un message
    if %ERRORLEVEL% equ 0 (
        echo L'application a été lancée avec succès.
        echo La sortie a été redirigée vers %LOG_FILE%.
    ) else (
        echo Une erreur est survenue pendant l'exécution de l'application. Voir %LOG_FILE% pour les détails.
    )
) else (
    echo L'exécutable %EXE_PATH% est introuvable. Veuillez d'abord compiler l'application avec build.bat.
    exit /b 1
)

echo === Fin du script run.bat ===
pause
