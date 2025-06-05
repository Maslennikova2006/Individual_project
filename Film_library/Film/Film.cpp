// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <string>

#include "/git/Film_library/Film/Film.h"

Film::Film() : _film_name(""), _film_genre(""), _director(),
_country(""), _year(2025), _image("") {}
Film::Film(const std::string& film, const std::string& genre,
    const Director& director, const std::string& country,
    const int year, const std::string& image) {
    _film_name = film;
    _film_genre = genre;
    _director = director;
    _country = country;
    _year = year;
    _image = image;
}
Film::Film(const Film& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _film_name = other._film_name;
    _film_genre = other._film_genre;
    _director = other._director;
    _country = other._country;
    _year = other._year;
    _image = other._image;
}

const std::string Film::get_film_name() const noexcept {
    return _film_name;
}
const std::string Film::get_film_genre() const noexcept {
    return _film_genre;
}
const Director Film::get_director() const noexcept {
    return _director;
}
const std::string Film::get_country() const noexcept {
    return _country;
}
const int Film::get_year() const noexcept {
    return _year;
}
const std::string Film::get_image() const noexcept {
    return _image;
}

void Film::set_film_name(const std::string& name) noexcept {
    _film_name = name;
}
void Film::set_film_genre(const std::string& genre) noexcept {
    _film_genre = genre;
}
void Film::set_director(const Director& director) noexcept {
    _director = director;
}
void Film::set_country(const std::string& country) noexcept {
    _country = country;
}
void Film::set_year(const int year) noexcept {
    _year = year;
}
void Film::set_image(const std::string& path) noexcept {
    _image = path;
}
