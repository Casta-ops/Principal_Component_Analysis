import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Cargar los datos desde el archivo CSV
data = pd.read_csv('eigenvectors.csv', header=None)
data.columns = ['Vector propio'] + [f'Var {i}' for i in range(1, len(data.columns))]
data.set_index('Vector propio', inplace=True)

# Función para crear gráficos de radar
def radar_plot(data, component_name):
    labels = data.columns
    values = data.loc[component_name].values
    num_vars = len(labels)

    # Asegurar cierre del gráfico
    values = np.append(values, values[0])
    angles = np.linspace(0, 2 * np.pi, num_vars, endpoint=False).tolist()
    angles += angles[:1]  # Cerrar gráfico

    # Configurar el gráfico
    fig, ax = plt.subplots(figsize=(6, 6), subplot_kw=dict(polar=True))
    ax.fill(angles, values, color='blue', alpha=0.25)
    ax.plot(angles, values, color='blue', linewidth=2)
    ax.set_yticks([])
    ax.set_xticks(angles[:-1])
    ax.set_xticklabels(labels)

    # Título y visualización
    ax.set_title(f'Gráfico de Radar para {component_name}', size=15, pad=20)
    plt.show()

# Crear gráficos de radar para cada componente
for component in data.index:
    radar_plot(data, component)
