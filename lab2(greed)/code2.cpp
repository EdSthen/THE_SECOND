#include <cassert>
#include <vector>
#include <memory>
#include <iostream>

template <typename T, size_t Dimension>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<Grid<T, Dimension - 1>> data;
    size_type current_dim_size;

public:
    Grid(T const &t) : data(1, Grid<T, Dimension - 1>(t)), current_dim_size(1) { }
    
    template<typename... Sizes>
    Grid(size_type first_size, Sizes... other_sizes) 
        : data(first_size, Grid<T, Dimension - 1>(other_sizes...)), current_dim_size(first_size) { }
    
    template<typename... Sizes>
    Grid(size_type first_size, Sizes... other_sizes, T const &t) 
        : data(first_size, Grid<T, Dimension - 1>(other_sizes..., t)), current_dim_size(first_size) { }
    
    Grid(Grid&& other) = delete;
    
    Grid& operator=(Grid&& other) = delete;

    Grid(const Grid& other) = default;

    Grid& operator=(const Grid& other) = default;

    Grid<T, Dimension - 1>& operator[](size_type idx) {
        return data[idx];
    }

    const Grid<T, Dimension - 1>& operator[](size_type idx) const {
        return data[idx];
    }

    template<typename... Indices>
    T& operator()(size_type first_idx, Indices... other_indices) {
        return data[first_idx](other_indices...);
    }

    template<typename... Indices>
    const T& operator()(size_type first_idx, Indices... other_indices) const {
        return data[first_idx](other_indices...);
    }

    ~Grid() = default;

    Grid& operator=(T const &t) {
        for (auto& item : data) {
            item = t;
        }
        return *this;
    }

    size_type get_size(size_t dim = 0) const {
        if (dim == 0) {
            return current_dim_size;
        } else {
            return data[0].get_size(dim - 1);
        }
    }
};

template <typename T>
class Grid<T, 1> final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<T> data;

public:
    explicit Grid(T const &t) : data(1, t) { }
    
    explicit Grid(size_type size) : data(size) { }
    
    Grid(size_type size, T const &t) : data(size, t) { }
    
    Grid(Grid&& other) = delete;
    
    Grid& operator=(Grid&& other) = delete;

    Grid(const Grid& other) = default;

    Grid& operator=(const Grid& other) = default;

    T& operator[](size_type idx) {
        return data[idx];
    }

    const T& operator[](size_type idx) const {
        return data[idx];
    }

    T& operator()(size_type idx) {
        return data[idx];
    }

    const T& operator()(size_type idx) const {
        return data[idx];
    }

    ~Grid() = default;

    Grid& operator=(T const &t) {
        std::fill(data.begin(), data.end(), t);
        return *this;
    }

    size_type get_size(size_t dim = 0) const { 
        return static_cast<size_type>(data.size()); 
    }
};

int main() {
    Grid<float, 1> g1_1(5u, 1.5f);
    assert(1.5f == g1_1(2));
    assert(5 == g1_1.get_size());
    
    Grid<float, 2> g2_1(3u, 4u);
    g2_1 = 2.0f;
    assert(2.0f == g2_1(1, 1));
    assert(3 == g2_1.get_size(0));
    assert(4 == g2_1.get_size(1));
    
    Grid<float, 2> g2_3(3u, Grid<float, 1>(4u, 2.0f));
    assert(2.0f == g2_3(1, 1));
    
    Grid<float, 3> g3_1(2u, 3u, 4u);
    g3_1 = 1.0f;
    assert(1.0f == g3_1(1, 1, 1));
    assert(2 == g3_1.get_size(0));
    assert(3 == g3_1.get_size(1));
    assert(4 == g3_1.get_size(2));
    
    Grid<float, 3> g3_other(1u, 1u, 1u);
    g3_other = 5.0f;
    assert(5.0f == g3_other(0, 0, 0));
    
    Grid<float, 4> g4_1(2u, 3u, 4u, 5u);
    g4_1 = 3.0f;
    assert(3.0f == g4_1(1, 1, 1, 1));
    assert(2 == g4_1.get_size(0));
    assert(3 == g4_1.get_size(1));
    assert(4 == g4_1.get_size(2));
    assert(5 == g4_1.get_size(3));
    
    Grid<float, 5> g5_1(2u, 2u, 2u, 2u, 2u);
    g5_1 = 4.0f;
    assert(4.0f == g5_1(1, 1, 1, 1, 1));
    
    Grid<float, 2> g2_copy = g2_3;
    assert(2.0f == g2_copy(1, 1));
    
    Grid<float, 3> g3_test(2u, 2u, 2u);
    g3_test = 1.0f;
    Grid<float, 2>& slice = g3_test[1];
    assert(1.0f == slice(1, 1));
    
    std::cout << "Pass" << std::endl;
    
    return 0;
}