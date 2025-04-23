import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import json

def train_model():
    # Charger les données du fichier diseases.csv
    data = pd.read_csv("data/diseases.csv")

    # Préparer les données
    # Convertir les variables catégorielles en variables numériques (encodage)
    le = LabelEncoder()
    data['Disease'] = le.fit_transform(data['Disease'])
    data['Gender'] = le.fit_transform(data['Gender'])
    data['BloodPressure'] = le.fit_transform(data['BloodPressure'])
    data['Cholesterol'] = le.fit_transform(data['Cholesterol'])
    data['Outcome'] = le.fit_transform(data['Outcome'])

    # Séparer les caractéristiques (X) et la variable cible (y)
    X = data.drop('Outcome', axis=1)
    y = data['Outcome']

    # Diviser les données en ensembles d'entraînement et de test
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Entraîner le modèle Random Forest
    model = RandomForestClassifier(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    # Extraire les poids (importances des caractéristiques)
    feature_importances = model.feature_importances_

    # Sauvegarder les poids dans un fichier JSON
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

    # Sauvegarder les poids dans un fichier JSON
    with open("data/weights.json", "w") as f:
        json.dump(weights, f, indent=4)

    print("Model training completed and weights saved to weights.json")

if __name__ == "__main__":
    train_model()
