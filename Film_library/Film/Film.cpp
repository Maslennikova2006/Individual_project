// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <string>

#include "/git/Film_library/Film/Film.h"

Film::Film() : _film_name(""), _film_genre(""), _country(""), _year(2025),
_average_mark(0) {}
Film::Film(const std::string& film, const std::string& genre,
    const std::string& country, int year, float mark) {
    _film_name = film;
    _film_genre = genre;
    _country = country;
    _year = year;
    _average_mark = mark;  // calculate_mark();
}
Film::Film(const Film& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _film_name = other._film_name;
    _film_genre = other._film_genre;
    _country = other._country;
    _year = other._year;
    _average_mark = other._average_mark;
}

const std::string Film::get_film_name() const noexcept {
    return _film_name;
}
const std::string Film::get_film_genre() const noexcept {
    return _film_genre;
}
const std::string Film::get_country() const noexcept {
    return _country;
}
const int Film::get_year() const noexcept {
    return _year;
}
const float Film::get_average_mark() const noexcept {
    return _average_mark;
}
