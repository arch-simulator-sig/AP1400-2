# Advanced Programming Mid-Term Exam

## Question 1: Statistical Analysis of a Dataset

Duration: 1h

Suppose we want to simulate a large dataset of measurements obtained from a scientific experiment. We model these measurements as a normal distribution of floating-point numbers.

Alright, here is the revised part 1 that forbids the usage of explicit for or while loops:

**Part 1:** Write a C++ program using STL algorithms to generate `data`, a `std::vector<double>` with 100,000 elements. Each element should be a random number drawn from a normal distribution with a mean of 0 and a standard deviation of 1. You can use `std::normal_distribution`, `std::default_random_engine` and `std::generate_n` from the `<algorithm>` library to accomplish this.

Prototypes for this task:

```cpp
std::default_random_engine generator;
std::normal_distribution<double> distribution(mean, stddev);
```

```cpp
OutputIt generate_n(OutputIt first, Size count, Generator gen); // creates count elements using gen function
```

Your code creates a `std::vector<double>` filled with the specified number of normally-distributed random numbers. Remember that you are not allowed to use traditional for or while loops in your code.

Hint: Maximum 4 lines of code, do not think hard!

**Part 2:** Continue with writing a one-liner to compute the mean (average) of the data. You can use the `std::accumulate` function from the `<numeric>` library inside this function. The prototype for `std::accumulate` is:

```cpp
T accumulate(InputIt first, InputIt last, T init); // summation of array
```

Hint: init is added to the sum of array, so you may set it to 0.

**Part 3:** Now compute the standard deviation of the data. You need to use the average variable which is calculated in part 2. Use `std::transform` and `std::accumulate` functions for this task. The prototype for `std::transform` is:

```cpp
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op); // apply unary_op to input and store in output
```

Hint: For equal length Input and Output, you do not need output argument of `std::transform`. `std` and `avg` are near 0 but not exactly 0.

**Part 4:** Now we want to discard outliers from our data, defined as values that are more than two standard deviations away from the mean:

Use the `std::remove_if` function to remove outliers from the `data` vector inplace. Use a lambda function to define the condition. The prototype for `std::remove_if` is:

```cpp
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p);
```

Hint: The size of `data` decreases.

**Part 5:** Now calculate `avg` and `std` again using the codes in part 2 and 3. If everything is done correctly, they should equal 0 after removing the outliers.

**Note:** For this entire problem, you must not use traditional for or while loops in your code.

---

# Question 2 - Sparse Matrix Implementation using Nested Classes (Linked List)

Duration: 3h

In this exam, you are tasked with implementing a SparseMatrix class in C++. A sparse matrix is a matrix in which most of the elements are zero. By only storing non-zero elements, we can drastically reduce memory usage for large matrices with few non-zero elements.

The SparseMatrix class should use nested classes and template programming. You should use dynamic variables and manage memory yourself, including writing a destructor that frees any memory that the class uses.

**API Description:**

Here is the basic structure of the SparseMatrix class:

```cpp
template <typename T>
class SparseMatrix {
private:
    // Nested Node class
    class Node {
    public:
        // Node class constructors, destructor, etc.
        // Your code here...
    };

    // Your data members here...

public:
    // Default constructor
    SparseMatrix(int rows, int columns);

    // Copy constructor
    SparseMatrix(const SparseMatrix<T>& other);

    // Move constructor
    SparseMatrix(SparseMatrix<T>&& other) noexcept;

    // Copy assignment operator
    SparseMatrix<T>& operator=(const SparseMatrix<T>& other);

    // Move assignment operator
    SparseMatrix<T>& operator=(SparseMatrix<T>&& other) noexcept;

    // Destructor
    ~SparseMatrix();

    // Insert an element into the matrix
    void insert(int row, int column, T value);

    // Add another SparseMatrix to this one
    SparseMatrix<T> add(const SparseMatrix<T>& other) const;

    // Subtract another SparseMatrix from this one
    SparseMatrix<T> subtract(const SparseMatrix<T>& other) const;

    // Multiply another SparseMatrix with this one
    SparseMatrix<T> multiply(const SparseMatrix<T>& other) const;

    // Print the matrix
    void display() const;
};
```

Please use the following `main.cpp` file to check your sparse matrix:

```cpp
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

```

**Tasks:**

1.  **Implement the Node class.** This class should have data members for the row and column of the element, the value of the element, and a pointer to the next Node in the linked list.

2.  **Implement the SparseMatrix constructor.** This should initialize a new empty SparseMatrix with the given number of rows and columns.

3.  **Implement the `insert` method.** This should create a new Node for the given value and insert it into the appropriate position in the linked list. Remember to handle the case where a value is inserted into a position that already has a value.

4.  **Implement the `display` method.** This should print out the complete matrix in its original 2D form, with all elements in their original positions. Please iterate over the SparseMatrix once, store all values and show them appropriately. `std::map<std::pair<int, int>, T> elements;` This map could be useful. You can fill it once and then use its `find` method to check if there is any value. `elements[{i,j}]` stores the value.

5.  **Implement the `add` method.** This should return a new SparseMatrix that is the result of adding the other matrix to this one. Remember that you can only add matrices that have the same dimensions. **You need to iterate over all Nodes only once.**

    Hint: Read all elements using a `map` similar to `display` method. You can easily then iterate over the map to do the addition.

    ````cpp
    for (const auto& [pos, value] : elements) {
        result.insert(pos.first, pos.second, value);
    }
    ````

6.  **Implement the SparseMatrix destructor.** This should properly free all of the memory used by the SparseMatrix. Remember that you need to delete every Node in the linked list.

7.  **Implement the copy constructor and the copy assignment operator.** These should make a complete copy of the other SparseMatrix. After the copy is made, changes to one matrix should not affect the other.

    Hint: Using `insert` can be useful in copy constructor. `std::swap` makes life much easier in assigment operator.

8.  **Implement the move constructor and the move assignment operator.** These should efficiently transfer the resources from the other SparseMatrix to this one. After the move, the other SparseMatrix should be left in a valid but unspecified state.

    Hint: Move constructor is effectively a one-liner :-) `std::swap` proves to be useful in move assigment operator.

9.  **Leak Check.**
    It is important to check for leak tests. If you have correctly deleted all variables you can see similar output for `valgrind`.

```sh
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
```

```log
    ==97== HEAP SUMMARY:
    ==97==     in use at exit: 0 bytes in 0 blocks
    ==97==   total heap usage: 48 allocs, 48 frees, 75,552 bytes allocated
    ==97==
    ==97== All heap blocks were freed -- no leaks are possible
```

---

All the bests!
