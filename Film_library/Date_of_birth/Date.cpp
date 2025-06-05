// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>

#include "/git/Film_library/Date_of_birth/Date.h"

Date::Date() : _day(1), _month(1), _year(2025) {}
Date::Date(const int day, const int month, const int year) {
    if (!check_to_correct_date(day, month, year))
        throw std::invalid_argument("Incorrect date!\n");
    _day = day;
    _month = month;
    _year = year;
}
Date::Date(const Date& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _day = other._day;
    _month = other._month;
    _year = other._year;
}

void Date::set_date(const int day, const int month, const int year) {
    if (!check_to_correct_date(day, month, year))
        throw std::invalid_argument("Incorrect date!\n");
    _day = day;
    _month = month;
    _year = year;
}
void Date::set_from_string(const std::string& date_str) {
    std::istringstream iss(date_str);
    char delimeter1, delimeter2;
    int day, month, year;

    if (!(iss >> day >> delimeter1 >> month >> delimeter2 >> year) ||
        delimeter1 != '.' || delimeter2 != '.') {
        throw std::invalid_argument
        ("Incorrect date format. Expected dd.mm.yyyy!\n");
    }

    if (!check_to_correct_date(day, month, year))
        throw std::invalid_argument("Incorrect date!\n");

    _day = day;
    _month = month;
    _year = year;
}

const int Date::get_day() const noexcept {
    return _day;
}
const int Date::get_month() const noexcept {
    return _month;
}
const int Date::get_year() const noexcept {
    return _year;
}

std::string Date::toString() const noexcept {
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d", _day, _month, _year);
    return std::string(buffer);
}

bool Date::check_to_correct_date
(const int day, const int month, const int year) const noexcept {
    if (year < 1862) return false;
    int last_day_February = 28;
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (!check_to_correct_day(day, 31)) return false;
        break;
    case 2:
        if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
            last_day_February = 29;
        if (!check_to_correct_day(day, last_day_February)) return false;
        break;
    case 4: case 6: case 9: case 11:
        if (!check_to_correct_day(day, 30)) return false;
        break;
    default:
        return false;
        break;
    }
    return true;
}
bool Date::check_to_correct_day(const int current_day, const int last_day)
const noexcept {
    if (current_day < 1 || current_day > last_day) return false;
    return true;
}
