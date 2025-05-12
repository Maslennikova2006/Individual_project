// Copyright 2025 Maslennikova Mary

#include <stdexcept>
#include <string>

#include "/git/Film_library/FIO/FIO.h"

FIO::FIO(const std::string& fn, const std::string& sn, const std::string& ln) {
    set_first_name(fn);
    set_second_name(sn);
    set_last_name(ln);
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
        _first_name = convert_to_norm_form(fn);;
    }
}
void FIO::set_second_name(const std::string& sn) {
    if (!check_to_correct_form(sn)) {
        throw std::invalid_argument("Incorrect symbols were used!\n");
    } else {
        _second_name = convert_to_norm_form(sn);;
    }
}
void FIO::set_last_name(const std::string& ln) {
    if (!check_to_correct_form(ln)) {
        throw std::invalid_argument("Incorrect symbols were used!\n");
    } else {
        _last_name = convert_to_norm_form(ln);
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

bool FIO::check_to_correct_form(const std::string& name) const noexcept {
    size_t len = name.length();
    for (int i = 0; i < len; i++) {
        if (name[i] < 'A' || (name[i] > 'Z' && name[i] < 'a')
            || name[i] > 'z') {
            return false;
        }
    }
    return true;
}
std::string FIO::convert_to_norm_form(const std::string& name) const noexcept {
    size_t len = name.length();
    std::string current_name = name;
    if ('a' <= name[0] && 'z' >= name[0]) {
        current_name[0] = name[0] - ('a' - 'A');
    }
    for (int i = 1; i < len; i++) {
        if ('A' <= name[i] && 'Z' >= name[i]) {
            current_name[i] = name[i] + ('a' - 'A');
        }
    }
    return current_name;
}
