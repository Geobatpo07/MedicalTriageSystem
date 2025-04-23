@echo off
setlocal enabledelayedexpansion

echo === Nettoyage des fichiers temporaires et de construction ===

REM Demander confirmation avant de procéder
set /p confirm="Voulez-vous procéder au nettoyage du projet (tous les fichiers de construction seront supprimés) ? [o/n] : "
if /i not "%confirm%"=="o" (
    echo Abandon du nettoyage.
    exit /b
)

REM Sauvegarder les logs avant suppression
set /p save_logs="Souhaitez-vous sauvegarder les fichiers de logs avant suppression ? [o/n] : "
if /i "%save_logs%"=="o" (
    echo Sauvegarde des fichiers de logs dans le dossier 'logs_backup'...
    mkdir logs_backup 2>nul
    xcopy /e /i /y logs\* logs_backup\
    echo Sauvegarde terminée.
)

REM Suppression des fichiers générés de la compilation
echo Suppression des fichiers .exe, .obj, et autres fichiers de construction...
del /f /q bin\*.exe
del /f /q bin\*.obj
del /f /q bin\*.pdb
del /f /q bin\*.ilk
del /f /q bin\*.lib

REM Supprimer les fichiers temporaires de l'IDE (si utilisés)
echo Suppression des fichiers temporaires...
del /f /q *.user
del /f /q *.suo

REM Demander confirmation avant de supprimer les dossiers 'bin' et 'obj'
set /p delete_bin="Souhaitez-vous supprimer le dossier 'bin' ? [o/n] : "
if /i "%delete_bin%"=="o" (
    if exist bin (
        echo Suppression du dossier 'bin'...
        rmdir /s /q bin
    ) else (
        echo Le dossier 'bin' n'existe pas.
    )
)

set /p delete_obj="Souhaitez-vous supprimer le dossier 'obj' ? [o/n] : "
if /i "%delete_obj%"=="o" (
    if exist obj (
        echo Suppression du dossier 'obj'...
        rmdir /s /q obj
    ) else (
        echo Le dossier 'obj' n'existe pas.
    )
)

REM Demander confirmation avant de supprimer les fichiers de log
set /p delete_logs="Souhaitez-vous supprimer tous les fichiers de logs ? [o/n] : "
if /i "%delete_logs%"=="o" (
    echo Suppression des fichiers de logs...
    del /f /q logs\*
)

REM Nettoyage des fichiers temporaires dans le répertoire racine
echo Suppression des fichiers temporaires dans le répertoire racine...
del /f /q *.log
del /f /q *.bak
del /f /q *.tmp

REM Récapitulation des actions effectuées
echo === Nettoyage terminé ===
pause
