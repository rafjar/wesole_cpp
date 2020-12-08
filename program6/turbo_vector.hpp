#ifndef _turbo_vector_hpp_
#define _turbo_vector_hpp_

#include <iostream>

using uint = unsigned int;

template<typename T>
class TurboVector {
    private:
        uint capacity_;
        uint size_;
        T* values_;

    public:
        constexpr TurboVector();
        TurboVector(uint size);
        TurboVector(uint size, const T& val);
        ~TurboVector();

        T& at(uint indx);
        T& operator[](uint indx);
        T& front();
        T& back();

        T* begin();
        T* end();
        T* begin() const;
        T* end() const;

        bool empty() const;
        uint size() const;
        uint capacity() const;

        void clear();
        void push_back(const T& val);
        void push_at(uint indx, const T& val);
        void pop_back();

        void print() const;
};

template<typename T> constexpr TurboVector<T>::TurboVector()
    : capacity_(0), size_(0)
    {}

template<typename T> TurboVector<T>::TurboVector(uint size)
    : capacity_(size), size_(size)
    {}

template<typename T> TurboVector<T>::TurboVector(uint size, const T& val)
    : capacity_(size), size_(size), values_(new T[size]) {
        for(uint i=0; i<size_; ++i)
            values_[i] = val;
}

template<typename T> TurboVector<T>::~TurboVector() {
    if(capacity_ != 0)
        delete[] values_;
}

template<typename T> T& TurboVector<T>::at(uint indx) {
    return values_[indx];
}

template<typename T> T& TurboVector<T>::operator[](uint indx) {
    return values_[indx];
}

template<typename T> T& TurboVector<T>::front() {
    return values_[0];
}

template<typename T> T& TurboVector<T>::back() {
    return values_[size_-1];
}

template<typename T> T* TurboVector<T>::begin() {
    return values_;
}

template<typename T> T* TurboVector<T>::end() {
    return values_+size_;
}

template<typename T> T* TurboVector<T>::begin() const {
    return values_;
}

template<typename T> T* TurboVector<T>::end() const {
    return values_+size_;
}

template<typename T> bool TurboVector<T>::empty() const {
    if(size_ == 0)
        return true;
    return false;
}

template<typename T> uint TurboVector<T>::size() const {
    return size_;
}

template<typename T> uint TurboVector<T>::capacity() const {
    return capacity_;
}

template<typename T> void TurboVector<T>::clear() {
    if(capacity_ != 0)
        delete[] values_;

    capacity_ = 0;
    size_ = 0;
}

template<typename T> void TurboVector<T>::push_back(const T& val) {
    if(capacity_ == 0) {
        values_ = new T[++capacity_];
        values_[size_++] = val;
    }
    else if(size_ < capacity_) {
        values_[size_++] = val;
    }
    else {
        T *temp = new T[++capacity_];

        for(uint i=0; i<size_; ++i)
            temp[i] = values_[i];
        temp[size_++] = val;

        delete[] values_;

        values_ = temp;
    }
}

template<typename T> void TurboVector<T>::push_at(uint indx, const T& val) {
    if(capacity_ == 0 && indx == 0) {
        push_back(val);
    }
    else if(size_ < capacity_) {
        for(uint i=size_-1; i>=indx; --i)
            values_[i+1] = values_[i];
        values_[indx] = val;
        ++size_;
    }
    else {
        T *temp = new T[++capacity_];

        for(uint i=size_-1; i>=indx; --i)
            temp[i+1] = values_[i];
        for(uint i=0; i<indx; ++i)
            temp[i] = values_[i];
        temp[indx] = val;

        delete[] values_;
        values_ = temp;

        ++size_;
    }
}

template<typename T> void TurboVector<T>::pop_back() {
    if(size_ > 0)
        --size_;
}

template<typename T> void TurboVector<T>::print() const {
    for(const auto &i : *this)
        std::cout << i << std::endl;
}

# endif





