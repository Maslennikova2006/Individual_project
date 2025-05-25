// Copyright 2025 Maslennikova Mary

#include <string>
#include <iostream>

#include "/git/Film_library/Feedback/Feedback.h"

Feedback::Feedback() : _review_text(""), _mark(0), _user(nullptr) {}
Feedback::Feedback(const std::string& text, int mark, User* user) {
    set_review_text(text);
    set_mark(mark);
    set_user(user);
}
Feedback::Feedback(const Feedback& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _review_text = other._review_text;
    _mark = other._mark;
    _user = other._user;
}

void Feedback::set_review_text(const std::string& text) {
    _review_text = text;
}
void Feedback::set_mark(const int mark) {
    if (mark < 0 || mark > 5)
        throw std::invalid_argument("The mark should be from 0 to 5!");
    _mark = mark;
}
void Feedback::set_user(User* user) {
    _user = user;
}

const std::string Feedback::get_review_text() const noexcept {
    return _review_text;
}
const int Feedback::get_mark() const noexcept {
    return _mark;
}
const User* Feedback::get_user() const noexcept {
    return _user;
}
