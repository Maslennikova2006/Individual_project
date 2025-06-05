// Copyright 2025 Maslennikova Mary

#include <string>

#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/MyTVector/TVector.h"

#ifndef FILM_LIBRARY_USER_USER_H_
#define FILM_LIBRARY_USER_USER_H_

class Film;
class FilmLibrary;

class User {
    std::string _login;
    std::string _password;
    TVector<const Film*> _favorites;
    TVector<const Film*> _watched;

 public:
    User();
    User(const std::string&, const std::string&);
    User(const std::string& login, const std::string& password,
        const TVector<const Film*>& favorites,
        const TVector<const Film*>& watched);
    User(const User&);

    ~User();

    void set_login(const std::string& login);
    void set_password(const std::string& password);
    void set_favorites(const TVector<const Film*>& favorites);
    void set_viewed(const TVector<const Film*>& watched);

    const std::string get_login() const noexcept;
    const std::string get_password() const noexcept;
    const TVector<const Film*>& get_favorites() const noexcept;
    const TVector<const Film*>& get_watched() const noexcept;

    void add_favorites(const Film* film);
    void add_watched(const Film* film);

    bool operator==(const User& other) const noexcept;

    void save_to_stream(std::ostream& os) const;
    void load_from_stream(std::istream& is, const FilmLibrary& library);

 private:
    bool check_to_correct_login(const std::string& login);
    bool check_to_correct_password(const std::string& password);
};
#endif  // FILM_LIBRARY_USER_USER_H_
