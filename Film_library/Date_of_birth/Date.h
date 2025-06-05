// Copyright 2025 Maslennikova Mary

#include <string>

#ifndef FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_
#define FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_

class Date {
    int _day;
    int _month;
    int _year;

 public:
    Date();
    Date(const int, const int, const int);
    Date(const Date&);

    ~Date() = default;

    void set_date(const int, const int, const int);
    void set_from_string(const std::string& date_str);

    const int get_day() const noexcept;
    const int get_month() const noexcept;
    const int get_year() const noexcept;

    std::string toString() const noexcept;
 private:
    bool check_to_correct_date(const int, const int, const int)
        const noexcept;
    bool check_to_correct_day(const int, const int) const noexcept;
};
#endif  // FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_
