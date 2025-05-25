// Copyright 2025 Maslennikova Mary

#include <string>

#include "/git/Film_library/User/User.h"

#ifndef FILM_LIBRARY_FEEDBACK_FEEDBACK_H_
#define FILM_LIBRARY_FEEDBACK_FEEDBACK_H_

class Feedback {
    std::string _review_text;
    int _mark;
    User* _user;

 public:
    Feedback();
    Feedback(const std::string&, int, User*);
    Feedback(const Feedback&);

    ~Feedback() = default;

    void set_review_text(const std::string&);
    void set_mark(const int);
    void set_user(User*);

    const std::string get_review_text() const noexcept;
    const int get_mark() const noexcept;
    const User* get_user() const noexcept;
};
#endif  // FILM_LIBRARY_FEEDBACK_FEEDBACK_H_
