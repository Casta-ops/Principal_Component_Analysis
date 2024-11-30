import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Datos simulados basados en los vectores propios y variables originales
data = {
    "Var 1": [-0.00608593, -0.0285523, 0.939908],
    "Var 2": [0.000398349, -0.001766, -0.0252689],
    "Var 3": [0.000183535, -0.00299433, 0.0739394],
    "Var 4": [0.00782167, 0.00776741, 0.317548],
    "Var 5": [6.6375e-05, -0.000161487, 0.00325755],
    "Var 6": [0.213178, 0.976373, 0.0249432],
    "Var 7": [0.976936, -0.213151, -0.00211636],
    "Var 8": [2.55204e-06, -3.17011e-05, 0.000779757],
    "Var 9": [-0.000241239, 0.00325993, -0.0583682],
    "Var 10": [0.000141593, 0.000456473, 0.0171996],
    "Var 11": [-0.00591117, 0.016607, -0.0391049],
    "Var 12": [-0.00431675, 0.00936209, 0.0613266],
}

# Crear un DataFrame
variables = list(data.keys())
components = ["PC1", "PC2", "PC3"]
eigenvectors = pd.DataFrame(data, index=components)

# Generar puntos aleatorios simulados para observaciones (proyecciones en PC1 y PC2)
np.random.seed(42)
observations = np.random.randn(100, 2)  # 100 observaciones proyectadas en PC1 y PC2

# Crear el biplot
fig, ax = plt.subplots(figsize=(10, 7))

# Graficar las observaciones proyectadas en PC1 y PC2
ax.scatter(observations[:, 0], observations[:, 1], alpha=0.7, c='blue', label='Observations')

# Graficar las variables originales como vectores
for i, variable in enumerate(variables):
    ax.arrow(0, 0, eigenvectors.loc["PC1", variable], eigenvectors.loc["PC2", variable],
             color='red', alpha=0.8, head_width=0.03, head_length=0.05)
    ax.text(eigenvectors.loc["PC1", variable] * 1.2, eigenvectors.loc["PC2", variable] * 1.2,
            variable, color='black', fontsize=9)

# Configurar el gráfico
ax.axhline(0, color='gray', linewidth=0.5, linestyle='--')
ax.axvline(0, color='gray', linewidth=0.5, linestyle='--')
ax.set_title('Biplot: Proyecciones y Cargas de PCA', fontsize=14)
ax.set_xlabel('PC1')
ax.set_ylabel('PC2')
ax.legend()
ax.grid(alpha=0.3)

plt.tight_layout()
plt.show()
