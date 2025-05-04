// Copyright 2025 Maslennikova Mary
#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <random>
#ifndef FILM_LIBRARY_TVECTOR_TVECTOR_H_
#define FILM_LIBRARY_TVECTOR_TVECTOR_H_

#define STEP_OF_CAPACITY 15
enum State { empty, busy, deleted };

template <class T> class TVector;
template <class T> void hoara_sort(TVector<T>& data);
template <class T> void hoara_sort_rec(TVector<T>& data, size_t left, size_t right);
template <class T> void shuffle(TVector<T>& data);

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
    TVector(const TVector<T>& other);

    ~TVector();

    inline T* data() noexcept;

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline const T* data() const noexcept;
    inline const T& front();
    inline const T& back();
    inline const T* begin() const noexcept;
    inline const T* end() const noexcept;

    void reserve(size_t new_capacity) noexcept;
    void resize(size_t count) noexcept;
    void resize(size_t count, const T& value) noexcept;
    void shrink_to_fit() noexcept;

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

    TVector<T>& operator=(const TVector<T>& other) noexcept;
    bool operator!=(const TVector<T>& other) const noexcept;
    bool operator==(const TVector<T>& other) const noexcept;
    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    inline bool is_empty() const noexcept;
    void print() const noexcept;

    friend void hoara_sort_rec<T>(TVector<T>& data, size_t left, size_t right);
    friend void hoara_sort<T>(TVector<T>& data);
    friend void shuffle<T>(TVector<T>& data);

 private:
    inline bool is_full() const noexcept;
    void set_memory(size_t size) noexcept;
    void reallocation_memory(size_t count) noexcept;
    void reallocation_memory_for_deleted() noexcept;
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
void TVector<T>::reserve(size_t new_capacity) noexcept {
    if (new_capacity <= _capacity) {
        return;
    }
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];
    for (size_t i = 0, j = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    for (size_t i = _size; i < new_capacity; i++) {
        new_states[i] = empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}
template <class T>
void TVector<T>::resize(size_t count) noexcept {
    if (count == _size) {
        return;
    }
    if (count < _size) {
        T* new_data = new T[_capacity];
        State* new_states = new State[_capacity];
        for (size_t i = 0, j = 0; i < _size + _deleted; i++) {
            if (_states[i] == busy) {
                new_data[j] = _data[i];
                new_states[j] = busy;
                if (j == count) {
                    new_states[j] = empty;
                }
                j++;
            }
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
    }
    if (count > _capacity) {
        reallocation_memory(count);
    }
    _size = count;
}
template <class T>
void TVector<T>::resize(size_t count, const T& value) noexcept {
    if (count == _size) {
        return;
    }
    if (count < _size) {
        resize(count);
        return;
    }
    if (count > _capacity) {
        reallocation_memory(count);
    }
    size_t size = _size;
    _size = count;
    for (size_t i = size; i < _size; i++) {
        _data[i] = value;
    }
}
template <class T>
void TVector<T>::shrink_to_fit() noexcept {
    if (_size == _capacity) {
        return;
    }
    T* new_data = new T[_size];
    State* new_states = new State[_size];
    for (size_t i = 0, j = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            if (j == _size)
                break;
            j++;
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = _size;
}

template <class T>
void TVector<T>::push_front(const T& value) noexcept {
    if (is_full()) {
        reallocation_memory(_size + 1);
    }
    size_t new_index = recalculate_the_position(0);
    for (int i = _size + _deleted; i > new_index; i--) {
        _data[i] = _data[i - 1];
        _states[i] = busy;
    }
    _data[new_index] = value;
    _states[new_index] = busy;
    _size++;
}
template <class T>
void TVector<T>::insert(const size_t index, const T& value) {
    if (index > _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    if (is_full())
        reallocation_memory(_size + 1);
    size_t new_index = recalculate_the_position(index);
    for (size_t i = _size + _deleted; i > new_index; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[new_index] = value;
    _states[new_index] = busy;
    _size++;
}
template <class T>
void TVector<T>::insert(const size_t index, size_t count, const T& value) {
    if (index > _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    if (_size + _deleted + count > _capacity)
        reallocation_memory(_size + count);
    size_t new_index = recalculate_the_position(index);
    for (size_t i = _size + _deleted; i > new_index; i--) {
        _data[i + count - 1] = _data[i - 1];
        _states[i + count - 1] = _states[i - 1];
    }
    for (size_t i = 0; i < count; i++) {
        _data[new_index + i] = value;
        _states[new_index + i] = busy;
    }
    _size += count;
}
template <class T>
void TVector<T>::insert(const size_t index, std::initializer_list<T> data) {
    if (index > _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    if (_size + _deleted + data.size() > _capacity)
        reallocation_memory(_size + data.size());
    size_t new_index = recalculate_the_position(index);
    for (size_t i = _size + _deleted; i > new_index; i--) {
        _data[i + data.size() - 1] = _data[i - 1];
        _states[i + data.size() - 1] = _states[i - 1];
    }
    auto it = data.begin();
    for (size_t i = 0; i < data.size(); i++) {
        _data[new_index + i] = *(it + i);
        _states[new_index + i] = busy;
    }
    _size += data.size();
}
template <class T>
void TVector<T>::push_back(const T& value) noexcept {
    if (is_full()) {
        reallocation_memory(_size + 1);
    }
    size_t new_index = recalculate_the_position(_size - 1) + 1;
    _data[new_index] = value;
    _states[new_index] = busy;
    _size++;
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty())
        throw std::invalid_argument("Cannot be deleted from an empty vector\n");
    size_t new_index = recalculate_the_position(0);
    _states[new_index] = deleted;
    _deleted++;
    _size--;
    if (_deleted >= 0.10 * (_size + _deleted)) {
        reallocation_memory_for_deleted();
    }
}
template <class T>
void TVector<T>::erase(size_t index) {
    if (is_empty())
        throw std::invalid_argument("Cannot be deleted from an empty vector\n");
    if (index > _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    size_t new_index = recalculate_the_position(index);
    _states[new_index] = deleted;
    _size--;
    _deleted++;
    if (_deleted >= 0.10 * (_size + _deleted)) {
        reallocation_memory_for_deleted();
    }
}
template <class T>
void TVector<T>::erase(const size_t first, const size_t last) {
    if (is_empty())
        throw std::invalid_argument("Cannot be deleted from an empty vector\n");
    if (first > last || last >= _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    size_t new_first = recalculate_the_position(first);
    size_t new_last = recalculate_the_position(last);
    size_t count_busy_deleted = 0;
    for (size_t i = new_first; i <= new_last; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            count_busy_deleted++;
        }
    }
    _deleted += count_busy_deleted;
    _size -= count_busy_deleted;
    if (_deleted >= 0.10 * (_size + _deleted)) {
        reallocation_memory_for_deleted();
    }
}
template <class T>
void TVector<T>::pop_back() {
    if (is_empty())
        throw std::invalid_argument("Cannot be deleted from an empty vector\n");
    size_t new_index = recalculate_the_position(_size - 1);
    _states[new_index] = empty;
    _size--;
}
template <class T>
void TVector<T>::clear() {
    if (is_empty())
        throw std::invalid_argument("Cannot be deleted from an empty vector\n");
    for (size_t i = 0; i < _size + _deleted; i++) {
        _states[i] = empty;
    }
    _deleted = 0;
    _size = 0;
}

template <class T>
void TVector<T>::replace(size_t index, const T& value) {
    if (is_empty())
        throw std::invalid_argument
        ("It is impossible to replace an element in an empty vector\n");
    if (index >= _size)
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    size_t new_index = recalculate_the_position(index);
    _data[new_index] = value;
}

template <class T>
const T& TVector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    }
    size_t new_index = recalculate_the_position(index);
    return _data[new_index];
}
template <class T>
void TVector<T>::assign(size_t count, const T& value) {
    set_memory(count);
    _deleted = 0;
    size_t i = 0;
    for (i; i < count; i++) {
        _data[i] = value;
        _states[i] = busy;
    }
    while (i < _capacity) {
        _states[i++] = empty;
    }
}
template <class T>
void TVector<T>::assign(std::initializer_list<T> data) {
    size_t size = data.size();
    set_memory(size);
    _deleted = 0;
    size_t i = 0;
    auto it = data.begin();
    for (i; it != data.end(); i++, it++) {
        _data[i] = *it;
        _states[i] = busy;
    }
    while (i < _capacity) {
        _states[i++] = empty;
    }
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) noexcept {
    if (this == &other)
        return *this;
    size_t size = other._size;
    _deleted = other._deleted;
    set_memory(size);
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
    return *this;
}
template <class T>
bool TVector<T>::operator!=(const TVector<T>& other) const noexcept {
    return !(this->operator==(other));
}
template <class T>
bool TVector<T>::operator==(const TVector<T>& other) const noexcept {
    if (_size != other._size) {
        return false;
    }
    size_t i = 0, j = 0;

    while (i < _capacity && j < other._capacity) {
        while (i < _capacity && _states[i] != busy)
            i++;
        while (j < other._capacity && other._states[j] != busy)
            j++;
        if (i >= _capacity || j >= other._capacity) {
            break;
        }
        if (_data[i] != other._data[j]) {
            return false;
        }
        i++;
        j++;
    }
    return true;
}
template <class T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _size + _deleted) {
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    }
    size_t new_index = recalculate_the_position(index);
    return _data[new_index];
}
template <class T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _size + _deleted) {
        throw std::invalid_argument("The index goes beyond the boundaries\n");
    }
    size_t new_index = recalculate_the_position(index);
    return _data[new_index];
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
    return _size == 0;
}
template <class T>
void TVector<T>::print() const noexcept {
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy)
            std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
inline bool TVector<T>::is_full() const noexcept {
    return (_size + _deleted) == _capacity;
}
template <class T>
void TVector<T>::set_memory(size_t size) noexcept {
    _size = size;
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    delete[] _data;
    delete[] _states;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = empty;
    }
}
template <class T>
void TVector<T>::reallocation_memory(size_t count) noexcept {
    size_t new_capacity = (count / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    reserve(new_capacity);
}
template <class T>
void TVector<T>::reallocation_memory_for_deleted() noexcept {
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];
    for (int i = 0, j = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    set_memory(_size);
    for (int i = 0; i < _size; i++) {
        _data[i] = new_data[i];
        _states[i] = new_states[i];
    }
    delete[] new_data;
    delete[] new_states;
    _deleted = 0;
}
template <class T>
void TVector<T>::my_swap(T& first_number, T& second_number) const noexcept {
    T tmp = first_number;
    first_number = second_number;
    second_number = tmp;
}
template <class T>
size_t TVector<T>::rand_generation(size_t min, size_t max) const noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(gen);
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

template <class T>
void hoara_sort(TVector<T>& data) {
    if (data.size() < 2) return;
    hoara_sort_rec(data, 0, data.size() - 1);
}
template <class T>
void hoara_sort_rec(TVector<T>& data, size_t left, size_t right) {
    if (left < right) {
        size_t base = (left + right) / 2;
        size_t l = left, r = right;
        const T base_value = data[base];
        while (l <= r) {
            while (data[l] < base_value) {
                l++;
            }
            while (data[r] > base_value) {
                r--;
            }
            if (l <= r) {
                data.my_swap(data[l], data[r]);
                l++;
                if (r > 0)
                    r--;
            }
            else { break; } // ??
        }
        hoara_sort_rec(data, left, r);
        hoara_sort_rec(data, l, right);
    }
}
template <class T>
void shuffle(TVector<T>& data) {
    int i, rand_i;
    for (i = 0; i < data._size + data._deleted; i++) {
        rand_i = data.rand_generation(0, data._size + data._deleted - 1);
        data.my_swap(data[i], data[rand_i]);
    }
}
