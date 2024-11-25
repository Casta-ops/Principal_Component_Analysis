import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV
filename = "eigenvectors.csv"
eigenvectors = pd.read_csv(filename, header=None)

# Configuración de etiquetas y datos
componentes = ["PC" + str(i) for i in range(1, len(eigenvectors)+1)]
variables = [f"Var {i}" for i in range(1, len(eigenvectors.columns))]

# Transponer para trabajar con las variables como categorías
eigenvectors_transposed = eigenvectors.iloc[:, 1:].T  # Ignorar el texto inicial
eigenvectors_transposed.columns = componentes

# Crear el gráfico
plt.figure(figsize=(10, 6))
for i, comp in enumerate(componentes):
    plt.plot(variables, eigenvectors_transposed[comp], label=comp, marker='o')

# Etiquetas y leyenda
plt.title("Visualización de los Eigenvectores (Componentes principales)")
plt.xlabel("Variables originales")
plt.ylabel("Coeficientes (cargas)")
plt.xticks(rotation=45)
plt.legend(title="Componentes principales")
plt.grid(True)
plt.tight_layout()

# Mostrar la gráfica
plt.show()

