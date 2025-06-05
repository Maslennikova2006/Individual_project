// Copyright 2025 Maslennikova Mary

#include <fstream>
#include <sstream>

#include "/git/Film_library/Film_library/Film_library.h"

FilmLibrary::FilmLibrary() : _films(), _users() {}
FilmLibrary::FilmLibrary(TVector<Film>& films, TVector<User*>& users) {
    _films = films;
    _users = users;
}
FilmLibrary::FilmLibrary(const std::string& filmsFile,
    const std::string& usersFile) {
    load_films_from_file(filmsFile);
    load_users_from_file(usersFile);
    for (User* user : _users) {
        TVector<const Film*> favorites = user->get_favorites();
        TVector<const Film*> watched = user->get_watched();

        for (size_t i = 0; i < favorites.size(); i++) {
            const Film* found = find_film_by_name(favorites[i]->get_film_name());
            if (found) {
                favorites[i] = const_cast<Film*>(found);
            }
        }

        for (size_t i = 0; i < watched.size(); i++) {
            const Film* found = find_film_by_name(watched[i]->get_film_name());
            if (found) {
                watched[i] = const_cast<Film*>(found);
            }
        }
    }
}
FilmLibrary::FilmLibrary(const FilmLibrary& other) {
    _films = other._films;
    for (const User* user : other._users) {
        _users.push_back(new User(*user));
    }
}
FilmLibrary::~FilmLibrary() {
    for (User* user : _users) {
        delete user;
    }
    if (_users.size() > 0)
        _users.clear();
}

const TVector<Film>& FilmLibrary::get_films() const noexcept {
    return _films;
}
const TVector<User*>& FilmLibrary::get_users() const noexcept {
    return _users;
}

void FilmLibrary::load_films_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Cannot open films file!\n");
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        TVector<std::string> parts;
        std::string part;

        while (getline(iss, part, '|')) {
            parts.push_back(part);
        }

        if (parts.size() == 6) {
            Film film;
            film.set_film_name(parts[0]);
            film.set_film_genre(parts[1]);
            size_t spacePos = parts[2].rfind(' ');
            if (spacePos != std::string::npos) {
                std::string nameStr = parts[2].substr(0, spacePos);
                std::string dateStr = parts[2].substr(spacePos + 1);

                FIO director_name;
                director_name.set_from_string(nameStr);
                Date director_birthDate;
                director_birthDate.set_from_string(dateStr);

                Director director;
                director.set_person(director_name);
                director.set_date_of_birth(director_birthDate);
                film.set_director(director);
            }

            film.set_country(parts[3]);
            film.set_year(stoi(parts[4]));
            film.set_image(parts[5]);

            _films.push_back(film);
        }
    }
    file.close();
}
void FilmLibrary::save_users_to_file(const std::string& filename) {
    std::ofstream file(filename);
    for (User* user : _users) {
        user->save_to_stream(file);
        file << "\n";
    }
    file.close();
}

void FilmLibrary::load_users_from_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        User* user = new User();
        user->load_from_stream(iss, *this);
        _users.push_back(user);
    }
}

const Film* FilmLibrary::find_film_by_name(const std::string& name) const {
    for (const Film& film : _films) {
        if (film.get_film_name() == name) {
            return &film;
        }
    }
    return nullptr;
}
User* FilmLibrary::find_user(const std::string& login) {
    for (User* user : _users) {
        if (user->get_login() == login) {
            return user;
        }
    }
    return nullptr;
}

void FilmLibrary::update_user(const User& user) {
    for (size_t i = 0; i < _users.size(); ++i) {
        if (_users[i]->get_login() == user.get_login()) {
            delete _users[i];
            _users[i] = new User(user);
            return;
        }
    }
    _users.push_back(new User(user));
}
void FilmLibrary::update_user_favorites(const std::string& login, const Film* film) {
    for (User* user : _users) {
        if (user && user->get_login() == login) {
            user->add_favorites(film);
            return;
        }
    }
}
void FilmLibrary::update_user_watched(const std::string& login, const Film* film) {
    for (User* user : _users) {
        if (user && user->get_login() == login) {
            user->add_watched(film);
            return;
        }
    }
}
