// Copyright 2025 Maslennikova Mary

#include <string>

#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/Film_director/Director.h"

#ifndef FILM_LIBRARY_FILM_FILM_H_
#define FILM_LIBRARY_FILM_FILM_H_

class Film {
    std::string _film_name;
    std::string _film_genre;
    Director _director;
    std::string _country;
    int _year;
    std::string _image;

 public:
    Film();
    Film(const std::string&, const std::string&, const Director&,
        const std::string&, const int, const std::string&);
    Film(const Film&);

    ~Film() = default;

    const std::string get_film_name() const noexcept;
    const std::string get_film_genre() const noexcept;
    const Director get_director() const noexcept;
    const std::string get_country() const noexcept;
    const int get_year() const noexcept;
    const std::string get_image() const noexcept;

    void set_film_name(const std::string& name) noexcept;
    void set_film_genre(const std::string& genre) noexcept;
    void set_director(const Director& director) noexcept;
    void set_country(const std::string& country) noexcept;
    void set_year(const int year) noexcept;
    void set_image(const std::string& path) noexcept;
};
#endif  // FILM_LIBRARY_FILM_FILM_H_
