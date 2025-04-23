import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import classification_report, confusion_matrix
import numpy as np
import os
from tqdm import tqdm

# Dossier pour les figures
FIG_DIR = "figures"
os.makedirs(FIG_DIR, exist_ok=True)

# Chargement des données
df = pd.read_csv('data/diseases.csv')

# Aperçu rapide
print(df.head())
print(df.info())
print(df.describe(include='all'))

# Nettoyage et encodage des variables catégorielles
binary_cols = [
    'Fever (Yes/No)', 'Cough (Yes/No)', 'Fatigue (Yes/No)',
    'Difficulty Breathing (Yes/No)', 'Blood Pressure', 'Cholesterol Level',
    'Gender', 'Outcome Variable'
]

label_encoders = {}
for col in tqdm(binary_cols, desc="Encodage des variables"):
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

# Statistiques générales
print("\n--- Répartition de l'issue ---")
print(df['Outcome Variable'].value_counts())

# Vérification des valeurs manquantes
print("\n--- Valeurs manquantes ---")
print(df.isnull().sum())

# Visualisation des variables
sns.countplot(x='Outcome Variable', data=df)
plt.title('Distribution des outcomes')
plt.savefig(f"{FIG_DIR}/distribution_outcomes.png")
plt.clf()

sns.histplot(data=df, x='Age (in years)', hue='Outcome Variable', kde=True)
plt.title("Répartition de l'âge selon l'issue")
plt.savefig(f"{FIG_DIR}/age_distribution_by_outcome.png")
plt.clf()

symptoms = ['Fever (Yes/No)', 'Cough (Yes/No)', 'Fatigue (Yes/No)', 'Difficulty Breathing (Yes/No)']
for symptom in tqdm(symptoms, desc="Visualisation symptômes vs issue"):
    sns.countplot(x=symptom, hue='Outcome Variable', data=df)
    plt.title(f'{symptom} vs Outcome')
    filename = symptom.lower().replace(" ", "_").replace("(", "").replace(")", "").replace("/", "_")
    plt.savefig(f"{FIG_DIR}/{filename}_vs_outcome.png")
    plt.clf()

# Heatmap des corrélations
plt.figure(figsize=(10, 8))
sns.heatmap(df.corr(), annot=True, cmap="coolwarm", fmt='.2f')
plt.title("Corrélations entre les variables")
plt.tight_layout()
plt.savefig(f"{FIG_DIR}/heatmap_correlation.png")
plt.clf()

# Modèle Random Forest
features = df.drop(columns=['Disease', 'Outcome Variable'])
target = df['Outcome Variable']

X_train, X_test, y_train, y_test = train_test_split(features, target, test_size=0.3, random_state=42)

rf = RandomForestClassifier(n_estimators=100, random_state=42)
print("Entraînement du modèle Random Forest...")
rf.fit(X_train, y_train)

# Importance des variables
importances = rf.feature_importances_
feature_names = features.columns
indices = np.argsort(importances)[::-1]

plt.figure(figsize=(10, 6))
sns.barplot(x=importances[indices], y=feature_names[indices])
plt.title('Importance des variables (Random Forest)')
plt.tight_layout()
plt.savefig(f"{FIG_DIR}/feature_importance_rf.png")
plt.clf()

# Rapport de classification
y_pred = rf.predict(X_test)
print("\n--- Rapport de classification ---")
print(classification_report(y_test, y_pred))

# Matrice de confusion
cm = confusion_matrix(y_test, y_pred)
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.title('Matrice de confusion')
plt.xlabel('Prédictions')
plt.ylabel('Réel')
plt.tight_layout()
plt.savefig(f"{FIG_DIR}/confusion_matrix.png")
plt.clf()

print(f"\n✅ Analyse terminée. Toutes les figures sont sauvegardées dans le dossier '{FIG_DIR}/'.")
