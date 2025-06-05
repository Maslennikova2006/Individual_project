// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MyTVector/TVector.h"
#include "/git/Film_library/Film_library/Film_library.h"

User::User() : _login("Username"), _password("123456pw"),
_favorites(), _watched() {}
User::User(const std::string& login, const std::string& password) {
    set_login(login);
    set_password(password);
    _favorites = TVector<const Film*>();
    _watched = TVector<const Film*>();
}
User::User(const std::string& login, const std::string& password,
    const TVector<const Film*>& favorites, const TVector<const Film*>& watched) {
    set_login(login);
    set_password(password);
    _favorites = favorites;
    _watched = watched;
}
User::~User() {
    if (_favorites.size() > 0)
        _favorites.clear();
    if (_watched.size() > 0)
        _watched.clear();
}
User::User(const User& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _login = other._login;
    _password = other._password;
}

void User::set_login(const std::string& login) {
    if (!check_to_correct_login(login))
        throw std::invalid_argument("Incorrect login!\n");
    _login = login;
}
void User::set_password(const std::string& password) {
    if (!check_to_correct_password(password))
        throw std::invalid_argument("Incorrect password!\n");
    _password = password;
}
void User::set_favorites(const TVector<const Film*>& favorites) {
    _favorites = favorites;
}
void User::set_viewed(const TVector<const Film*>& watched) {
    _watched = watched;
}

const std::string User::get_login() const noexcept {
    return _login;
}
const std::string User::get_password() const noexcept {
    return _password;
}
const TVector<const Film*>& User::get_favorites() const noexcept {
    return _favorites;
}
const TVector<const Film*>& User::get_watched() const noexcept {
    return _watched;
}

bool User::operator==(const User& other) const noexcept {
    if (_login != other._login)
        return false;
    if (_password != other._password)
        return false;
    return true;
}

void User::add_favorites(const Film* new_film) {
    if (!new_film) return;
    for (const Film* film : _favorites) {
        if (film && film->get_film_name() == new_film->get_film_name()) {
            return;
        }
    }
    _favorites.push_back(new_film);
}

void User::add_watched(const Film* new_film) {
    if (!new_film) return;
    for (const Film* film : _watched) {
        if (film && film->get_film_name() == new_film->get_film_name()) {
            return;
        }
    }
    _watched.push_back(new_film);
}

void User::save_to_stream(std::ostream& os) const {
    os << _login << "|" << _password << "|";

    os << _favorites.size() << "|";
    for (const Film* film : _favorites) {
        if (film != nullptr) {
            os << film->get_film_name() << ";";
        }
    }
    os << "|";

    os << _watched.size() << "|";
    for (const Film* film : _watched) {
        if (film != nullptr) {
            os << film->get_film_name() << ";";
        }
    }
    os << "|";
}

void User::load_from_stream(std::istream& is, const FilmLibrary& library) {
    std::string line;
    if (!std::getline(is, line)) return;

    std::vector<std::string> parts;
    size_t start = 0, end = line.find('|');
    while (end != std::string::npos) {
        parts.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find('|', start);
    }

    if (parts.size() < 6) {
        throw std::invalid_argument("Invalid user data format");
    }

    _login = parts[0];
    _password = parts[1];

    if (_favorites.size() > 0)
        _favorites.clear();
    size_t fav_count = 0;
    try { fav_count = std::stoul(parts[2]); }
    catch (...) {}

    if (fav_count > 0 && !parts[3].empty()) {
        std::istringstream fav_stream(parts[3]);
        std::string film_name;
        while (std::getline(fav_stream, film_name, ';')) {
            if (!film_name.empty()) {
                const Film* film = library.find_film_by_name(film_name);
                if (film) _favorites.push_back(film);
            }
        }
    }

    if (_watched.size() > 0)
        _watched.clear();
    size_t watched_count = 0;
    try { watched_count = std::stoul(parts[4]); }
    catch (...) {}

    if (watched_count > 0 && !parts[5].empty()) {
        std::istringstream watched_stream(parts[5]);
        std::string film_name;
        while (std::getline(watched_stream, film_name, ';')) {
            if (!film_name.empty()) {
                const Film* film = library.find_film_by_name(film_name);
                if (film) _watched.push_back(film);
            }
        }
    }
}

bool User::check_to_correct_login(const std::string& login) {
    if (login.length() < 4 || login.length() > 20) {
        throw std::invalid_argument
        ("The login must contain from 4 to 20 symbols!\n");
        return false;
    }

    if (login.find(' ') != std::string::npos) {
        throw std::invalid_argument("The login must not contain spaces!\n");
        return false;
    }
    return true;
}
bool User::check_to_correct_password(const std::string& password) {
    if (password.length() < 8 || password.length() > 20) {
        throw std::invalid_argument
        ("The password must contain from 8 to 20 symbols!\n");
        return false;
    }

    if (password.find(' ') != std::string::npos) {
        throw std::invalid_argument("The password must not contain spaces!\n");
        return false;
    }
    return true;
}
