template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type y_size, x_size;

public:
    Grid(T* data, size_type y_size, size_type x_size)
        : data(data), y_size(y_size), x_size(x_size) { }
    
    Grid(T const &t) : data(new T[1]{t}) ,y_size(1), x_size(1) { }
    
    Grid(size_type y_size, size_type x_size) : data(new T[x_size*y_size]{}) ,y_size(y_size), x_size(x_size) { }
    
    Grid(size_type y_size, size_type x_size, T const &t) :data(new T[x_size*y_size]), y_size(y_size), x_size(x_size) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }
    
    class Row {
        private:
        T* row_data;
        size_type row_size;
        public:
        Row(T* data, size_type size) : row_data(data), row_size(size) { }
        
        T& operator[](size_type x_idx) {
            return row_data[x_idx];
        }
        
        const T& operator[](size_type x_idx) const {
            return row_data[x_idx];
        }
        
    };
    
    Row operator[](size_type y_idx) {
        return Row(data + y_idx * x_size, x_size);
    }

    const Row operator[](size_type y_idx) const {
        return Row(data + y_idx * x_size, x_size);
    }

    ~Grid() {
        delete[] data;
    }

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const &t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};

