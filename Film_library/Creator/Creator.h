// Copyright 2025 Maslennikova Mary

#include "/git/Film_library/FIO/FIO.h"
#include "/git/Film_library/Date_of_birth/Date.h"

#ifndef FILM_LIBRARY_CREATOR_CREATOR_H_
#define FILM_LIBRARY_CREATOR_CREATOR_H_

class Creator {
 protected:
    FIO _person;
    Date _date_of_birth;
 public:
    Creator();
    Creator(const FIO&, const Date&);
    Creator(const Creator&);

    ~Creator() = default;

    void set_person(const FIO&);
    void set_date_of_birth(const Date&);

    const FIO get_person() const noexcept;
    const Date get_date_of_birth() const noexcept;
    std::string toString() const noexcept;
};
#endif  // FILM_LIBRARY_CREATOR_CREATOR_H_
