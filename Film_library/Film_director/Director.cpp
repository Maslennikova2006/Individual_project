// Copyright 2025 Maslennikova Mary

#include <iostream>

#include "/git/Film_library/Film_director/Director.h"

Director::Director() : Creator(), _awards(), _rating(0) {}
Director::Director(const FIO& person, const Date& date,
    const TVector<std::string>& awards, const float rating) {
    Creator(person, date);
    _awards = awards;
    _rating = rating;
}
Director::Director(const Creator& other,
    const TVector<std::string>& awards, const float rating) : Creator(other) {
    _awards = awards;
    _rating = rating;
}
Director::Director(const Director& other) : Creator(other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _awards = other._awards;
    _rating = other._rating;
}

void Director::add_award(const std::string& award) noexcept {
    _awards.push_back(award);
}
void Director::set_rating(const float mark) {
    _rating = mark;
}

const TVector<std::string> Director::get_awards() const noexcept {
    return _awards;
}
const float Director::get_rating() const noexcept {
    return _rating;
}
