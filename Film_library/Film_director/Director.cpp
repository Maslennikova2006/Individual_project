// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <sstream>
#include <string>

#include "/git/Film_library/Film_director/Director.h"

Director::Director() : Creator() {}
Director::Director(const FIO& person, const Date& date) {
    Creator(person, date);
}
Director::Director(const Creator& person) : Creator(person) {}
Director::Director(const Director& other) : Creator(other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
}
