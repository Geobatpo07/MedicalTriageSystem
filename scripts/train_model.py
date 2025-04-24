import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import json
import os

def train_model():
    # Répertoire courant du script
    base_dir = os.path.dirname(os.path.abspath(__file__))

    # Chemin vers le fichier CSV
    data_path = os.path.join(base_dir, "../data/diseases.csv")
    weights_path = os.path.join(base_dir, "../data/weights.json")

    # Vérification de l'existence du fichier
    if not os.path.exists(data_path):
        print(f"Fichier introuvable : {data_path}")
        return

    # Charger les données
    data = pd.read_csv(data_path)

    # Vérifier les valeurs manquantes
    print(f"Valeurs manquantes par colonne :\n{data.isnull().sum()}")

    # Remplir les valeurs manquantes par la médiane pour les colonnes numériques
    data['Age'] = data['Age'].fillna(data['Age'].median())

    # Séparation X / y avant d'appliquer get_dummies
    X = data.drop('Outcome Variable', axis=1)  # La variable cible est 'Outcome Variable'
    y = data['Outcome Variable']  # Variable cible

    # Appliquer get_dummies pour encoder les variables catégorielles sur X
    X = pd.get_dummies(X, drop_first=True)

    # Split des données
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Entraînement du modèle
    model = RandomForestClassifier(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    # Extraction des importances
    feature_importances = model.feature_importances_

    weights = {
        "Fever": feature_importances[0],
        "Cough": feature_importances[1],
        "Fatigue": feature_importances[2],
        "DifficultyBreathing": feature_importances[3],
        "Age": feature_importances[4],
        "Gender": feature_importances[5],
        "BloodPressure": feature_importances[6],
        "Cholesterol": feature_importances[7]
    }

    # Sauvegarde dans un fichier JSON
    with open(weights_path, "w") as f:
        json.dump(weights, f, indent=4)

    print(f"Entraînement terminé. Poids sauvegardés dans : {weights_path}")

if __name__ == "__main__":
    train_model()
