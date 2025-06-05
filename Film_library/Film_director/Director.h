// Copyright 2025 Maslennikova Mary

#include <string>
#include <iostream>
#include <sstream>

#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/MyTVector/TVector.h"

#ifndef FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_
#define FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_

class Director : public Creator{
 public:
    Director();
    Director(const FIO&, const Date&);
    Director(const Creator&);
    Director(const Director&);

    ~Director() = default;
};
#endif  // FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_
