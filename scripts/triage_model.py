import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import LabelEncoder
import json

df = pd.read_csv("data/diseases.csv")

# Features sélectionnées
features = ['Fever', 'Cough', 'Fatigue', 'DifficultyBreathing', 'Age',
            'BloodPressure', 'Cholesterol']
X = df[features]
y = df['Outcome']

# Encodage des variables catégorielles
le_bp = LabelEncoder()
le_chol = LabelEncoder()
X['BloodPressure'] = le_bp.fit_transform(X['BloodPressure'])
X['Cholesterol'] = le_chol.fit_transform(X['Cholesterol'])
y = LabelEncoder().fit_transform(y)

# Random Forest
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X, y)

# Importance des variables
importances = dict(zip(features, model.feature_importances_))

# Export
with open("data/weights.json", "w") as f:
    json.dump(importances, f, indent=4)

print("📊 Feature importances saved to weights.json")
