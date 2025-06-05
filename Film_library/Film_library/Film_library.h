// Copyright 2025 Maslennikova Mary

#include <string>

#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Feedback/Feedback.h"
#include "/git/Film_library/MyTVector/TVector.h"

#ifndef FILM_LIBRARY_FILM_LIBRARY_FILM_LIBRARY_H_
#define FILM_LIBRARY_FILM_LIBRARY_FILM_LIBRARY_H_

class FilmLibrary {
    TVector<Film> _films;
    TVector<User*> _users;

 public:
    FilmLibrary();
    FilmLibrary(TVector<Film>&, TVector<User*>&);
    FilmLibrary(const std::string&, const std::string&);
    FilmLibrary(const FilmLibrary& other);

    ~FilmLibrary();

    const TVector<Film>& get_films() const noexcept;
    const TVector<User*>& get_users() const noexcept;

    void save_users_to_file(const std::string& filename);

    const Film* find_film_by_name(const std::string& name) const;
    User* find_user(const std::string&);
    void update_user(const User& user);
    void update_user_favorites(const std::string& login, const Film* film);
    void update_user_watched(const std::string& login, const Film* film);

 private:
    void load_films_from_file(const std::string& file);
    void load_users_from_file(const std::string& filename);
};
#endif  // FILM_LIBRARY_FILM_LIBRARY_FILM_LIBRARY_H_
