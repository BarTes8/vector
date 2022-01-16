#include <exception>
#include <iostream>
#include <stddef.h>
#include <vector>

namespace ab {

template <typename T>
class Vector {
public:
    Vector()
        : size_(0)
        , capacity_(1)
        , vec_{new T[capacity_]}
    {}

    Vector(const Vector& other)
        : size_(other.size_)
        , capacity_(other.capacity_)
        , vec_(new T[capacity_])
    {
        for (size_t i = 0; i < other.size(); i++) {
            vec_[i] = other.vec_[i];
        }
    }

    ~Vector() {
        delete [] vec_;
    }

    void push_back(T value) {
        if (size_ < capacity_) {
            vec_[size_] = value;
            size_++;
        }
        else {
            capacity_ *= 2;
            T* newVec = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                newVec[i] = vec_[i];
            }
            newVec[size_] = value;
            size_++;
            delete [] vec_;
            vec_ = newVec;
        } 
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::runtime_error("Pop back on empty vector!");
        }
        size_--;
    }

    void reserve(size_t capacity) {
        if (capacity > size_) {
            capacity_ = capacity;
        }
    }

    void shrink_to_fit() {
        capacity_ = size_;
    }

    void resize(size_t size) {
        if(size > 0) {
            size_ = size;
        }
    }

    T& front() {
        return vec_[0];
    }

    T& back() {
        return vec_[size_ - 1];
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void clear() {
        size_ = 0;
    }

    T* begin() {
        return vec_;
    }

    T* end() {
        return vec_ + size_ * sizeof(T);
    }

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size(); i++) {
            if (vec_[i] != other.vec_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return *this != other;
    }

    T& at(size_t index) {
        if (index < 0 || index >= size_) {
            throw std::runtime_error("At - out of bounds!");
        }
        return vec_[index];
    }

    T& operator[](size_t index) {
        return vec_[index];
    }

private:
    size_t size_{};
    size_t capacity_{};
    T* vec_{}; 
};
}

void printVector(ab::Vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    ab::Vector<int> v;
    for (size_t i = 0; i < 10; i++) {
        v.push_back(i);
    }
    printVector(v);
    
    v.pop_back();
    
    printVector(v);

    std::cout << "Front: " << v.front() << " \nBack: " << v.back() << '\n';
    std::cout << "Element v[5]: " << v[5] << '\n';
    std::cout << "Element at(2): " << v.at(2) << '\n';
    std::cout << "Begin: " << v.begin() << " Value: " << *(v.begin()) << '\n';
    std::cout << "End: " << v.end() << " Value: " << *(v.end() - sizeof(int)) << '\n';


    v.clear();
    std::cout << "After clear: " << v.size() << '\n';
    printVector(v);

    return 0;
}