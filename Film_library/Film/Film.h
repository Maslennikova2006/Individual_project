// Copyright 2025 Maslennikova Mary

#include "string"

#ifndef FILM_LIBRARY_FILM_FILM_H_
#define FILM_LIBRARY_FILM_FILM_H_

class Film {
    std::string _film_name;
    std::string _film_genre;
    std::string _country;
    int _year;
    float _average_mark;  // TVector<float>

 public:
    Film();
    Film(const std::string&, const std::string&,
        const std::string&, int, float);
    Film(const Film&);

    ~Film() = default;

    const std::string get_film_name() const noexcept;
    const std::string get_film_genre() const noexcept;
    const std::string get_country() const noexcept;
    const int get_year() const noexcept;
    const float get_average_mark() const noexcept;

    //  const float calculate_average_mark() const noexcept;
};
#endif  // FILM_LIBRARY_FILM_FILM_H_
