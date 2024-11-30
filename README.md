# Principal_Component_Analysis
This repository contains the implementation of Principal Component Analysis (PCA) on a wine dataset, aimed at dimensionality reduction and feature interpretation. The dataset includes various physicochemical properties of wine samples, and the goal is to analyze how these features contribute to the overall variance and identify key components for future analysis.

LINK TO THE VIDEO: https://youtu.be/vV4iBd3UOc8

LINK TO THE FULL VERSION: https://youtu.be/YrDsGn8GdyY

Features:
- PCA Algorithm: A custom implementation of PCA from scratch, which includes loading data, computing covariance matrices, and extracting eigenvalues and eigenvectors.
- Data Analysis: The code performs dimensionality reduction and visualizes the principal components to better understand the underlying patterns in the data.
- Data Preprocessing: Functions to clean and load the wine dataset, ensuring compatibility with the PCA algorithm.
Visualization: Generates plots that display the contributions of each variable to the principal components, helping to interpret the key factors that drive variation in the data.

Objective:

The purpose of this project is to:

- Reduce the number of variables in the wine dataset while preserving as much information as possible.
- Visualize the most significant components and understand which physicochemical properties influence wine quality.
- Provide an intuitive approach to performing PCA without relying on third-party libraries.

Files:

- PCA.cpp: The core C++ implementation for performing PCA on the wine dataset.
- eigenvectors.csv: The file containing the eigenvectors (principal components) of the covariance matrix.
- eigenvalues.csv: The file containing the eigenvalues that represent the variance captured by each principal component.
- Wine.csv: The dataset containing wine physicochemical properties and quality scores.

How to Use:

- Download or clone this repository to your local machine.
- Compile and run the PCA.cpp file with any standard C++ compiler.
- Load the wine dataset and execute PCA to analyze the principal components.
- Visualize and interpret the results using the generated plots.

DATASET: https://www.kaggle.com/datasets/yasserh/wine-quality-dataset
