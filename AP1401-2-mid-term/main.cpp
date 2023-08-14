#include "SparseMatrix.h"
#include <iostream>

int main()
{
    // Create two 3x3 sparse matrices
    SparseMatrix<int> matrix1 { 3, 3 };
    SparseMatrix<int> matrix2 { 3, 3 };

    // Insert values into matrix1
    matrix1.insert(0, 0, 1);
    matrix1.insert(1, 1, 2);
    matrix1.insert(2, 2, -1);
    matrix1.insert(2, 2, 3);

    // Insert values into matrix2
    matrix2.insert(0, 0, 4);
    matrix2.insert(1, 1, 5);
    matrix2.insert(2, 2, 6);

    // Display matrices
    std::cout << "Matrix 1:" << std::endl;
    matrix1.display();
    std::cout << "\nMatrix 2:" << std::endl;
    matrix2.display();

    // Test addition
    SparseMatrix<int> matrix3 { matrix1.add(matrix2) };
    std::cout << "\nMatrix 3 (Matrix 1 + Matrix 2):" << std::endl;
    matrix3.display();

    // Test copy constructor
    SparseMatrix<int> matrix4 { matrix3 };
    std::cout << "\nMatrix 4 (Copy of Matrix 3):" << std::endl;
    matrix4.display();

    // Test move constructor
    SparseMatrix<int> matrix5 { std::move(matrix4) };
    std::cout << "\nMatrix 5 (Move of Matrix 4):" << std::endl;
    matrix5.display();
    std::cout << "\nMatrix 4 should be zero now:" << std::endl;
    matrix4.display();

    // Test copy assignment operator
    matrix4 = matrix5;
    std::cout << "\nMatrix 4 = Matrix 5:" << std::endl;
    matrix4.display();
    matrix5.display();

    // Test swap
    std::swap(matrix1, matrix2);
    std::cout << "\nMatrix 1:" << std::endl;
    matrix1.display();
    std::cout << "\nMatrix 2:" << std::endl;
    matrix2.display();

    return 0;
}
