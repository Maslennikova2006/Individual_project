// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <string>

#include "/git/Film_library/Creator/Creator.h"

Creator::Creator() : _person(), _date_of_birth() {}
Creator::Creator(const FIO& person, const Date& date) {
    _person = person;
    _date_of_birth = date;
}
Creator::Creator(const Creator& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!");
    _person = other._person;
    _date_of_birth = other._date_of_birth;
}

void Creator::set_person(const FIO& person) {
    _person = person;
}
void Creator::set_date_of_birth(const Date& date) {
    _date_of_birth = date;
}

const FIO Creator::get_person() const noexcept {
    return _person;
}
const Date Creator::get_date_of_birth() const noexcept {
    return _date_of_birth;
}
std::string Creator::toString() const noexcept {
    return _person.get_full_name() + " " + _date_of_birth.toString();
}
