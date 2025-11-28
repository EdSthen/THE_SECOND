//1

#include <string>
#include <exception>

class MathException : public std::exception {
private:
    std::string message_;
    
public:
    MathException() : message_("Math error occurred") {}
    
    MathException(const std::string& message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

int divide(int x, int y) {
    if (y == 0) throw MathException("Division by zero");
    return x / y;
}

//2

#include <utility>

template<typename T>
class shared_ptr {
private:
    T* ptr_;
    
    struct ControlBlock {
        size_t ref_count;
        
        ControlBlock() : ref_count(1) {}
    };
    
    ControlBlock* control_block_;

public:
    explicit shared_ptr(T* ptr = nullptr) : ptr_(ptr), control_block_(new ControlBlock()) {}
    
    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), control_block_(other.control_block_) {
        if (control_block_) {
            ++control_block_->ref_count;
        }
    }
    
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            if (control_block_) {
                ++control_block_->ref_count;
            }
        }
        return *this;
    }
    
    ~shared_ptr() {
        release();
    }
    
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    
    T* get() const { return ptr_; }
    
    size_t use_count() const { 
        return control_block_ ? control_block_->ref_count : 0; 
    }
    
private:
    void release() {
        if (control_block_) {
            --control_block_->ref_count;
            if (control_block_->ref_count == 0) {
                delete ptr_;
                delete control_block_;
            }
        }
    }
    
    template<typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    shared_ptr<T> result;
    result.ptr_ = new T(std::forward<Args>(args)...);
    result.control_block_ = new typename shared_ptr<T>::ControlBlock();
    return result;
}

//3

#include <string>
#include <sstream>
#include <exception>
#include <iostream>

class bad_from_string : public std::exception {
private:
    std::string message_;

public:
    bad_from_string(const std::string& message) : message_(message) {}
    bad_from_string(const char* message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

template<class T>
T from_string(std::string const& s) {
    std::istringstream iss(s);
    T result;
    
    iss >> std::noskipws >> result;

    if (iss.fail() || !iss.eof()) {
        throw bad_from_string("Failed to convert string to requested type");
    }
    
    return result;
}

template<>
std::string from_string<std::string>(std::string const& s) {
    std::istringstream iss(s);
    std::string result;
    iss >> std::noskipws >> result;
    
    if (iss.fail() || !iss.eof()) {
        throw bad_from_string("Failed to read string");
    }
    
    return result;
}
