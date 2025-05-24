// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <string>

#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MyTVector/TVector.h"

User::User() : _login("Username"), _password("123456pw") {}
User::User(const std::string& login, const std::string& password) {
    set_login(login);
    set_password(password);
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

const std::string User::get_login() const noexcept {
    return _login;
}
const std::string User::get_password() const noexcept {
    return _password;
}

bool User::operator==(const User& other) const noexcept {
    if (_login != other._login)
        return false;
    if (_password != other._password)
        return false;
    return true;
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
