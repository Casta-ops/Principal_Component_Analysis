import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Cargar los datos desde el archivo CSV
data = pd.read_csv('eigenvectors.csv', header=None)
data.columns = ['Vector propio'] + [f'Var {i}' for i in range(1, len(data.columns))]
data.set_index('Vector propio', inplace=True)

# Crear el mapa de calor
plt.figure(figsize=(10, 6))
sns.heatmap(data, annot=True, cmap='coolwarm', cbar_kws={'label': 'Magnitud de la carga'})
plt.title('Mapa de Calor de las Cargas de los Eigenvectores')
plt.xlabel('Variables Originales')
plt.ylabel('Componentes Principales')
plt.show()

