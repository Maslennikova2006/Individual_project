// Copyright 2025 Maslennikova Mary

#include <stdexcept>
#include <string>

#include "/git/Film_library/FIO/FIO.h"

FIO::FIO(const std::string& fn, const std::string& sn, const std::string& ln) {
    _first_name = fn;
    _second_name = sn;
    _last_name = ln;
}
FIO::FIO() : _first_name("Ivan"), _second_name("Ivanovich"),
_last_name("Ivanov") { }
FIO::FIO(const FIO& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _first_name = other._first_name;
    _second_name = other._second_name;
    _last_name = other._last_name;
}

void FIO::set_first_name(const std::string& fn) {
    if (!check_to_correct_form(fn)) {
        throw std::invalid_argument("Incorrect symbols were used!\n");
    } else {
        convert_to_norm_form(fn);
        _first_name = fn;
    }
}
void FIO::set_second_name(const std::string& sn) {
    if (!check_to_correct_form(sn)) {
        throw std::invalid_argument("Incorrect symbols were used!\n");
    } else {
        convert_to_norm_form(sn);
        _second_name = sn;
    }
}
void FIO::set_last_name(const std::string& ln) {
    if (!check_to_correct_form(ln)) {
        throw std::invalid_argument("Incorrect symbols were used!\n");
    } else {
        convert_to_norm_form(ln);
        _last_name = ln;
    }
}

const std::string FIO::get_first_name() const noexcept {
    return _first_name;
}
const std::string FIO::get_second_name() const noexcept {
    return _second_name;
}
const std::string FIO::get_last_name() const noexcept {
    return _last_name;
}

bool FIO::check_to_correct_form(const std::string name) const noexcept {
    int len = name.length();
    for (int i = 0; i < len; i++) {
        if (name[i] < 'A' || (name[i] > 'Z' && name[i] < 'a')
            || name[i] > 'z') {
            return false;
        }
    }
    return true;
}
void FIO::convert_to_norm_form(std::string name) const noexcept {
    int len = name.length();
    if ('a' <= name[0] && 'z' >= name[0]) {
        name[0] = name[0] - ('a' - 'A');
    }
    for (int i = 1; i < len; i++) {
        if ('A' <= name[i] && 'Z' >= name[i]) {
            name[i] = name[i] + ('a' - 'A');
        }
    }
}
