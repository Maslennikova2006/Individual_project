// Copyright 2025 Maslennikova Mary
#ifndef FILM_LIBRARY_TVECTOR_TVECTOR_H
#define FILM_LIBRARY_TVECTOR_TVECTOR_H

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
	TVector(size_t size = 0);
	TVector(const TVector<T>&);
	~TVector();
};
#endif  // FILM_LIBRARY_TVECTOR_TVECTOR_H

