#include <utility>
#include <cstddef>

template<typename T>
class ScopePtr {
private:
    T* m_ptr;

public:
    ScopePtr()
        : m_ptr{nullptr} {}
    
    explicit ScopePtr(T* ptr) : m_ptr{ptr} {}
    ScopePtr(const ScopePtr&) = delete;
    ScopePtr& operator=(const ScopePtr&) = delete;
    ScopePtr(ScopePtr&& other)
        : m_ptr{std::exchange(other.m_ptr, nullptr)} {}
    
    ScopePtr& operator=(ScopePtr&& other) {
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    explicit operator bool() const { return nullptr != m_ptr; } //я тут сделал != иначе тупо как-то
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
    T* release() {
        auto old_ptr = m_ptr;
        m_ptr = nullptr;
        return old_ptr;
    }
    void reset(T* new_ptr) {
        delete m_ptr;
        m_ptr = new_ptr;
    }

    ~ScopePtr() { delete m_ptr; }
};

template<typename T>
class ScopePtr<T[]> {
private:
    T* m_ptr;

public:
    ScopePtr()
        : m_ptr{nullptr} {}
    
    explicit ScopePtr(T* ptr) : m_ptr{ptr} {}
    ScopePtr(const ScopePtr&) = delete;
    ScopePtr& operator=(const ScopePtr&) = delete;
    ScopePtr(ScopePtr&& other)
        : m_ptr{std::exchange(other.m_ptr, nullptr)} {}

    ScopePtr& operator=(ScopePtr&& other) {
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    
    explicit operator bool() const { return nullptr != m_ptr; }
    T& operator[](std::size_t index) const { return m_ptr[index]; }
    T* get() const { return m_ptr; }
    T* release() {
        auto old_ptr = m_ptr;
        m_ptr = nullptr;
        return old_ptr;
    }
    void reset(T* new_ptr = nullptr) {
        delete[] m_ptr;
        m_ptr = new_ptr;
    }

    ~ScopePtr() { delete[] m_ptr; }
};

//2

template<typename T, typename U>
struct is_same {
    static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

//3

template<typename... Types>
struct are_same;

template<typename T>
struct are_same<T> {
    static constexpr bool value = true;
};

template<typename T, typename U, typename... Rest>
struct are_same<T, U, Rest...> {
    static constexpr bool value = is_same<T, U>::value && are_same<T, Rest...>::value;
};

//4

template<typename T, std::size_t N>
constexpr std::size_t size(const Array<T, N>&) {
    return N;
}

//5

template<typename Func, typename... Args>
auto invoke(Func func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
    return func(std::forward<Args>(args)...);
}

//6

template<typename T>
void flatten(const T& elem) {
    std::cout << elem << " ";
}

template<typename T>
void flatten(const Array<T>& array) {
    for (const auto& elem : array) {
        flatten(elem);
    }
}
