#include <AdtClasses/AdtClasses.hpp>
#include <MathLib/VectorFuncs.hpp>
#include <random>

typedef vector<vector<float>> matrix_t;

// Matrix_t functions

matrix_t multiplyMatrix(const matrix_t& matrix1, const matrix_t& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        throw std::invalid_argument("Invalid matrix_t dimensions for multiplication: "+to_string(cols1) + " " + to_string(rows2));
    }

    matrix_t result(rows1, vector<float>(cols2, 0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

vector<float> multiplyMatrixAndVector(const matrix_t& matrix, const vector<float>& vec) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (cols != vec.size()) {
        throw std::invalid_argument("Invalid matrix_t and vector dimensions for multiplication");
    }

    vector<float> result(rows, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }

    return result;
}

matrix_t convertVectorToMatrix(const vector<float>& vec) {
    matrix_t matrix_t;
    for (const auto& element : vec) {
        matrix_t.push_back({element});
    }
    return {matrix_t};
}

vector<vector<float>> transposeMatrix(const vector<vector<float>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<float>> transposed(cols, vector<float>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}