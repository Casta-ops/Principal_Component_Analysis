#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <cmath>

using namespace std;

vector<vector<double>> loadData(const string& filename) {
    vector<vector<double>> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return data;
    }

    string line;
    bool first_line = true;
    while (getline(file, line)) {
        if (first_line) {  // Saltar la primera línea (encabezados)
            first_line = false;
            continue;
        }

        stringstream ss(line);
        string value;
        vector<double> row_data;

        // Leer y almacenar todos los valores excepto la última columna
        vector<double> temp_row;
        while (getline(ss, value, ',')) {
            try {
                temp_row.push_back(stod(value));
            } catch (const invalid_argument& e) {
                cerr << "Error al convertir el valor a número: " << value << endl;
            }
        }

        // Excluir la última columna (variable predictiva)
        if (!temp_row.empty()) {
            temp_row.pop_back();  // Elimina el último elemento
            if (data.empty()) {
                data.resize(temp_row.size());
            }
            for (size_t i = 0; i < temp_row.size(); ++i) {
                data[i].push_back(temp_row[i]);
            }
        }
    }

    file.close();
    return data;
}

// Función para imprimir un vector
void printVector(const vector<double>& v) {
    for (double value : v) {
        cout << value << " ";
    }
    cout << endl;
}

// Función para calcular la media de un vector
double mean(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// Función para calcular la covarianza entre dos vectores
double covariance(const vector<double>& x, const vector<double>& y) {
    double mean_x = mean(x);
    double mean_y = mean(y);
    double cov = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        cov += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return cov / (x.size() - 1);
}

// Función para calcular la matriz de covarianza
vector<vector<double>> calculateCovarianceMatrix(const vector<vector<double>>& data) {
    vector<vector<double>> covariance_matrix(data.size(), vector<double>(data.size()));
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.size(); ++j) {
            covariance_matrix[i][j] = covariance(data[i], data[j]);
        }
    }
    return covariance_matrix;
}

// Función para calcular el producto matriz-vector
vector<double> multiply(const vector<vector<double>>& matrix, const vector<double>& vec) {
    vector<double> result(matrix.size(), 0.0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

// Función para normalizar un vector
double normalize(vector<double>& vec) {
    double norm = 0.0;
    for (double val : vec) {
        norm += val * val;
    }
    norm = sqrt(norm);
    for (double& val : vec) {
        val /= norm;
    }
    return norm;
}

// Función para calcular el valor y vector propio más grande usando el método de la potencia
pair<double, vector<double>> powerMethod(const vector<vector<double>>& matrix, int max_iterations = 1000, double tol = 1e-9) {
    vector<double> vec(matrix.size(), 1.0);  // Vector inicial
    double eigenvalue = 0.0;

    for (int i = 0; i < max_iterations; ++i) {
        vector<double> new_vec = multiply(matrix, vec);
        eigenvalue = normalize(new_vec);
        
        double diff = 0.0;
        for (size_t j = 0; j < vec.size(); ++j) {
            diff += abs(new_vec[j] - vec[j]);
        }
        
        vec = new_vec;
        if (diff < tol) break;
    }

    return {eigenvalue, vec};
}

// Función para deflacionar la matriz
void deflateMatrix(vector<vector<double>>& matrix, const vector<double>& eigenvector, double eigenvalue) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            matrix[i][j] -= eigenvalue * eigenvector[i] * eigenvector[j];
        }
    }
}

// Función para calcular varios valores y vectores propios
pair<vector<double>, vector<vector<double>>> calculateEigenValuesAndVectors(const vector<vector<double>>& matrix, int num_values) {
    vector<vector<double>> matrix_copy = matrix;
    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;

    for (int i = 0; i < num_values; ++i) {
        auto [eigenvalue, eigenvector] = powerMethod(matrix_copy);
        eigenvalues.push_back(eigenvalue);
        eigenvectors.push_back(eigenvector);
        deflateMatrix(matrix_copy, eigenvector, eigenvalue);
    }

    return {eigenvalues, eigenvectors};
}

// Función para imprimir una matriz
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Función para guardar los valores propios en un archivo CSV
void saveEigenvalues(const vector<double>& eigenvalues, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para valores propios: " << filename << endl;
        return;
    }

    file << "Valores propios";
    for (double value : eigenvalues) {
        file << "," << value;
    }
    file << endl;
    file.close();
}

// Función para guardar los vectores propios en un archivo CSV
void saveEigenvectors(const vector<vector<double>>& eigenvectors, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para vectores propios: " << filename << endl;
        return;
    }

    for (size_t i = 0; i < eigenvectors.size(); ++i) {
        file << "Vector propio " << (i + 1);
        for (double value : eigenvectors[i]) {
            file << "," << value;
        }
        file << endl;
    }
    file.close();
}



void cleanwindow() {
    system("cls");
}

int main() {
    vector<vector<double>> data = loadData("Wine.csv");

    while (true) {
        cout << "Menu" << endl;
        cout << "1. Imprimir un vector de la matriz" << endl;
        cout << "2. Calcular matriz de covarianza" << endl;
        cout << "3. Imprimir la matriz de covarianza" << endl;
        cout << "4. Calcular e imprimir valores y vectores propios" << endl;
        cout << "5. Guardar valores y vectores propios en un archivo" << endl;
        cout << "6. Salir" << endl;
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                printVector(data[0]);
                cleanwindow();
                break;
            case 2: {
                vector<vector<double>> cov_matrix = calculateCovarianceMatrix(data);
                cout << "Matriz de Covarianza calculada." << endl;
                cleanwindow();
                break;
            }
            case 3: {
                vector<vector<double>> cov_matrix = calculateCovarianceMatrix(data);
                cout << "Matriz de Covarianza:" << endl;
                printMatrix(cov_matrix);
                cleanwindow();
                break;
            }
            case 4: {
                vector<vector<double>> cov_matrix = calculateCovarianceMatrix(data);
                auto [eigenvalues, eigenvectors] = calculateEigenValuesAndVectors(cov_matrix, 3);
                cout << "Valores propios:" << endl;
                printVector(eigenvalues);
                cout << "Vectores propios:" << endl;
                printMatrix(eigenvectors);
                cleanwindow();
                break;
            }
            case 5:
                {
                    vector<vector<double>> cov_matrix = calculateCovarianceMatrix(data);
                    auto [eigenvalues, eigenvectors] = calculateEigenValuesAndVectors(cov_matrix, 3);
                    saveEigenvalues(eigenvalues, "eigenvalues.csv");
                    saveEigenvectors(eigenvectors, "eigenvectors.csv");
                    cout << "Valores y vectores propios guardados en archivos." << endl;
                    cleanwindow();
                    break;
                }
            case 6:
                return 0;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }

    return 0;
}