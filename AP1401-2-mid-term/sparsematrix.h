#ifndef SPARSE_MATRIX
#define SPARSE_MATRIX

#include <exception>
#include <iostream>
#include <map>

template <typename T>
class SparseMatrix {
private:
    class Node {
    public:
        int row, col;
        T value;
        Node* next;

        Node(int row, int col, T value)
            : row(row)
            , col(col)
            , value(value)
            , next(nullptr)
        {
        }
    };

    Node* head;
    int rows, cols;

public:
    SparseMatrix(int rows, int cols)
        : head(nullptr)
        , rows(rows)
        , cols(cols)
    {
    }

    SparseMatrix(const SparseMatrix<T>& other)
        : head(nullptr)
        , rows(other.rows)
        , cols(other.cols)
    {
        Node* curr = other.head;
        while (curr != nullptr) {
            this->insert(curr->row, curr->col, curr->value);
            curr = curr->next;
        }
    }

    SparseMatrix(SparseMatrix<T>&& other) noexcept
        : head(other.head)
        , rows(other.rows)
        , cols(other.cols)
    {
        other.head = nullptr;
    }

    ~SparseMatrix()
    {
        Node* curr = this->head;
        while (curr != nullptr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
    }

    SparseMatrix<T>& operator=(const SparseMatrix<T>& other)
    {
        if (this == &other)
            return *this;
        SparseMatrix<T> temp { other };
        std::swap(head, temp.head);
        rows = temp.rows;
        cols = temp.cols;
        return *this;
    }

    SparseMatrix<T>& operator=(SparseMatrix<T>&& other) noexcept
    {
        std::swap(head, other.head);
        cols = other.cols;
        rows = other.rows;
        return *this;
    }

    void swap(SparseMatrix<T>& other) noexcept
    {
        std::swap(this->head, other.head);
        std::swap(this->rows, other.rows);
        std::swap(this->cols, other.cols);
    }

    void insert(int row, int col, T value)
    {
        Node* newNode = new Node(row, col, value);
        Node* curr = this->head;
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->row == row && curr->col == col) {
                if (prev == nullptr) {
                    this->head = newNode;
                } else {
                    prev->next = newNode;
                }
                newNode->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        newNode->next = this->head;
        this->head = newNode;
    }

    void display() const
    {
        std::map<std::pair<int, int>, T> nodeMap;
        Node* curr = this->head;

        // create a map with position as key and value as the value
        while (curr != nullptr) {
            nodeMap[{ curr->row, curr->col }] = curr->value;
            curr = curr->next;
        }

        // iterate over rows and columns and check if there is a value in the map
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                if (nodeMap.find({ i, j }) != nodeMap.end()) {
                    std::cout << nodeMap[{ i, j }] << ' ';
                } else {
                    std::cout << 0 << ' ';
                }
            }
            std::cout << '\n';
        }
    }

    SparseMatrix<T> add(const SparseMatrix<T>& other) const
    {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Matrices dimensions do not match for addition.");
        }

        SparseMatrix<T> result(this->rows, this->cols);

        std::map<std::pair<int, int>, T> elements;

        // Insert nodes from this matrix into the map
        Node* curr1 = this->head;
        while (curr1 != nullptr) {
            elements[{ curr1->row, curr1->col }] = curr1->value;
            curr1 = curr1->next;
        }

        // Insert or update nodes from the other matrix into the map
        Node* curr2 = other.head;
        while (curr2 != nullptr) {
            elements[{ curr2->row, curr2->col }] += curr2->value;
            curr2 = curr2->next;
        }

        // Insert elements from the map into the result matrix
        for (const auto& [pos, value] : elements) {
            result.insert(pos.first, pos.second, value);
        }

        return result;
    }
};

#endif
