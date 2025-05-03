// Copyright 2025 Maslennikova Mary
#ifndef FILM_LIBRARY_TVECTOR_TVECTOR_H_
#define FILM_LIBRARY_TVECTOR_TVECTOR_H_

#define STEP_OF_CAPACITY 15
enum State { empty, busy, deleted };

template <class T>
class TVector {
    T* _data;
    size_t _size;
    size_t _capacity;
    size_t _deleted;
    State* _states;

 public:
    TVector();
    TVector(size_t size, const T* data);
    TVector(size_t size, std::initializer_list<T> data);
    TVector(std::initializer_list<T> data);
    TVector(const TVector<T>&);

    ~TVector();

    inline T* data() noexcept;

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline const T* data() const noexcept;
    inline const T& front();
    inline const T& back();
    inline const T* begin() const noexcept;
    inline const T* end() const noexcept;

    void reserve(size_t new_capacity);
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void shrink_to_fit();
    void reallocation_memory();

    void push_front(const T& value) noexcept;
    void insert(const size_t index, const T& value);
    void insert(const size_t index, size_t count, const T& value);
    void insert(const size_t index, std::initializer_list<T> data);
    void push_back(const T& value) noexcept;

    void pop_front();
    void erase(size_t index);
    void erase(const size_t first, const size_t last);
    void pop_back();
    void clear();

    void replace(size_t index, const T& value);

    const T& at(size_t index) const;
    void assign(size_t count, const T& value);
    void assign(std::initializer_list<T> data);

    TVector<T>& operator=(const TVector<T>& other);
    bool operator!=(const TVector<T>& other);
    bool operator==(const TVector<T>& other);
    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    inline bool is_empty() const noexcept;
    void print() const noexcept;

 private:
    inline bool is_full() const noexcept;
    void set_memory(size_t size) noexcept;
    void reallocation_memory_for_deleted() noexcept;
    void reallocation_memory(size_t count) noexcept;
    void my_swap(T& first_number, T& second_number) const noexcept;
    size_t rand_generation(size_t min, size_t max) const noexcept;
    size_t recalculate_the_position(size_t index) const noexcept;
    size_t recalculate_the_address(size_t index) const noexcept;
};
template <class T>
TVector<T>::TVector() : _data(nullptr), _size(0),
_capacity(STEP_OF_CAPACITY), _deleted(0), _states(nullptr) {
    set_memory(0);
}
template <class T>
TVector<T>::TVector(size_t size, const T* data) : _data(nullptr), _size(size),
_capacity(STEP_OF_CAPACITY), _deleted(0), _states(nullptr) {
    set_memory(size);
    if (data != nullptr) {
        for (size_t i = 0; i < _size; i++) {
            _data[i] = data[i];
            _states[i] = busy;
        }
    }
}
template <class T>
TVector<T>::TVector(size_t size, std::initializer_list<T> data) {
    set_memory(size);
    _deleted = 0;
    size_t index = 0;
    auto it = data.begin();
    for (index; it != data.end(); index++, it++) {
        _data[index] = *it;
        _states[index] = busy;
    }
    while (index < _size) {
        _data[index++] = 0;
    }
}
template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
    size_t size = data.size();
    set_memory(size);
    _deleted = 0;
    size_t index = 0;
    auto it = data.begin();
    for (index; it != data.end(); index++, it++) {
        _data[index] = *it;
        _states[index] = busy;
    }
    while (index < _size) {
        _data[index++] = 0;
    }
}
template <class T>
TVector<T>::TVector(const TVector<T>& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _size = other._size;
    _capacity = other._capacity;
    _deleted = other._deleted;
    set_memory(_size);
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}
template <class T>
TVector<T>::~TVector() {
    delete[] _data;
    delete[] _states;
}
template <class T>
inline T* TVector<T>::data() noexcept {
    return _data;
}
template <class T>
inline size_t TVector<T>::size() const noexcept {
    return _size;
}
template <class T>
inline size_t TVector<T>::capacity() const noexcept {
    return _capacity;
}
template <class T>
inline const T* TVector<T>::data() const noexcept {
    if (is_empty())
        return nullptr;
    T* new_address = recalculate_the_address(0);
    return new_address;
}
template <class T>
inline const T& TVector<T>::front() {
    if (is_empty())
        throw std::invalid_argument
        ("There is no first element in the empty vector!\n");
    size_t new_index = recalculate_the_position(0);
    return _data[new_index];
}
template <class T>
inline const T& TVector<T>::back() {
    if (is_empty())
        throw std::invalid_argument
        ("There is no last element in the empty vector!\n");
    size_t new_index = recalculate_the_position(_size - 1);
    return _data[new_index];
}
template <class T>
inline const T* TVector<T>::begin() const noexcept {
    if (is_empty())
        return nullptr;
    T* new_address = recalculate_the_address(0);
    return new_address;
}
template <class T>
inline const T* TVector<T>::end() const noexcept {
    if (is_empty())
        return nullptr;
    T* new_address = recalculate_the_address(_size - 1) + 1;
    return new_address;
}


template <class T>
void TVector<T>::set_memory(size_t size) noexcept {
    _size = size;
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    delete[] _data;
    delete[] _states;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = empty;
    }
}
template <class T>
void TVector<T>::reallocation_memory_for_deleted() noexcept {
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];
    for (int i = 0, j = 0; i < _size + _deleted; i++) {
        if (_states[i] != deleted) {
            new_data[j] = _data[i];
            new_states[j] = _states[i];
            j++;
        }
    }
    set_memory(_size);
    for (int i = 0; i < _size; i++) {
        _data[i] = new_data[i];
        _states[i] = new_states[i];
    }
    for (int i = _size; i < _capacity; i++) {
        _states[i] = empty;
    }
    delete[] new_data;
    delete[] new_states;
    _deleted = 0;
}
template <class T>
void TVector<T>::reallocation_memory(size_t count) noexcept {
    size_t new_capacity = (count / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    reserve(new_capacity);
}
template <class T>
void TVector<T>::my_swap(T& first_number, T& second_number) const noexcept {
    T tmp = first_number;
    first_number = second_number;
    second_number = tmp;
}
template <class T>
size_t TVector<T>::rand_generation(size_t min, size_t max) const noexcept {
    srand(time(0));
    /*size_t seed = time(0);
    size_t result = min + rand_r(&seed) % (max - min + 1);*/
    size_t result = min + rand() % (max - min + 1);
    return result;
}
template <class T>
size_t TVector<T>::recalculate_the_position(size_t index) const noexcept {
    size_t count_busy = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (index == count_busy)
                return i;
            count_busy++;
        }
    }
}
template <class T>
size_t TVector<T>::recalculate_the_address(size_t index) const noexcept {
    size_t count_busy = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (index == count_busy)
                return &_data[i];
            count_busy++;
        }
    }
}
#endif  // FILM_LIBRARY_TVECTOR_TVECTOR_H_
