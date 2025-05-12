// Copyright 2025 Maslennikova Mary

#ifndef FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_
#define FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_

class Date {
    int day;
    int month;
    int year;

 public:
    Date();
    Date(const int, const int, const int);
    Date(const Date&);

    ~Date() = default;

    void set_day(const int&);
    void set_month(const int&);
    void set_year(const int&);

    const int get_day() const noexcept;
    const int get_month() const noexcept;
    const int get_year() const noexcept;

 private:
    bool check_to_correct_date(const int&, const int&, const int&)
        const noexcept;
    bool check_to_correct_day(const int&, const int) const noexcept;
};
#endif  // FILM_LIBRARY_DATE_OF_BIRTH_DATE_H_
