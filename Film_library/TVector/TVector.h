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
    inline T& front() noexcept;
    inline T& back() noexcept;
    inline T* begin() noexcept;
    inline T* end() noexcept;

    void push_front(const T& value);
    T* insert(const T* index, const T& value);
    T* insert(const T* index, size_t count, const T& value);
    T* insert(const T* index, std::initializer_list<T> data);
    void push_back(const T& value);

    void pop_front();
    T* erase(T* index);
    T* erase(const T* index);
    T* erase(T* first, T* last);
    T* erase(const T* first, const T* last);
    void pop_back();
    void clear();

    void replace(const T* index, const T& value);
    void replace(const T* index, size_t count, const T& value);
    void replace(const T* index, std::initializer_list<T> data);

    const T& at(size_t index) const;
    void assign(size_t count, const T& value);

    TVector<T>& operator=(const TVector<T>& other);
    bool operator!=(const TVector<T>& other);
    bool operator==(const TVector<T>& other);
    const T& operator[](size_t index) const;

    inline bool is_empty() const noexcept;
    void print() const;

 private:
    inline bool is_full() const noexcept;
    void reserve(size_t new_capacity);
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void shrink_to_fit();
    void reallocation_memory();
};
template <class T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(STEP_OF_CAPACITY), _deleted(0), _states(nullptr) { }
template <class T>
TVector<T>::TVector(size_t size, const T* data) : _data(nullptr), _size(size), _capacity(STEP_OF_CAPACITY), _deleted(0), _states(nullptr) {
    if (size != 0) {
        _capacity = ((size + 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
        if ((size + 1) % STEP_OF_CAPACITY != 0) {
            _capacity += STEP_OF_CAPACITY;
        }
    }
    _data = new T[_capacity];
    _states = new State[_capacity];
    if (data != nullptr) {
        for (size_t i = 0; i < _size; i++) {
            _data[i] = data[i];
            _states[i] = busy;
        }
    }
    for (size_t i = _size; i < _capacity; i++) {
        _states[i] = empty;
    }
}
template <class T>
TVector<T>::TVector(size_t size, std::initializer_list<T> data) {
    _size = size;
    _capacity = ((_size + 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
    if ((_size + 1) % STEP_OF_CAPACITY != 0) {
         _capacity += STEP_OF_CAPACITY;
	}
    _data = new T[_capacity];
    _states = new State[_capacity];
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
    _size = data.size();
    _capacity = ((_size + 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
    if ((_size + 1) % STEP_OF_CAPACITY != 0) {
        _capacity += STEP_OF_CAPACITY;
    }
    _data = new T[_capacity];
    _states = new State[_capacity];
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
    _data = new T[_capacity];
    _states = new State[_capacity];
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
#endif  // FILM_LIBRARY_TVECTOR_TVECTOR_H_
