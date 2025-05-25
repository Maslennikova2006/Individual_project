// Copyright 2025 Maslennikova Mary

#include <string>
#include <iostream>

#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/MyTVector/TVector.h"

#ifndef FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_
#define FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_

class Director : public Creator{
    TVector<std::string> _awards;
    float _rating;

public:
    Director();
    Director(const FIO&, const Date&, const TVector<std::string>&, const float);
    Director(const Creator&, const TVector<std::string>&, const float);
    Director(const Director&);

    ~Director() = default;

    void add_award(const std::string&) noexcept;
    void set_rating(const float);

    const TVector<std::string> get_awards() const noexcept;
    const float get_rating() const noexcept;
};
#endif  // FILM_LIBRARY_FILM_DIRECTOR_DIRECTOR_H_
