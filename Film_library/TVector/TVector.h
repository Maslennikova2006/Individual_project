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
#endif  // FILM_LIBRARY_TVECTOR_TVECTOR_H_
