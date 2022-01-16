#include <stddef.h>

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
        } 
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

    bool operator !=(const Vector& other) const {
        return !(*this == other);
    }

private:
    size_t size_{};
    size_t capacity_{};
    T* vec_{}; 
};
}

int main() {
    return 0;
}