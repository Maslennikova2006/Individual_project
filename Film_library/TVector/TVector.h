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
#endif  // FILM_LIBRARY_TVECTOR_TVECTOR_H_
