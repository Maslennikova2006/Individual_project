// Copyright 2025 Maslennikova Mary

#include "string"

#ifndef FILM_LIBRARY_FIO_FIO_H_
#define FILM_LIBRARY_FIO_FIO_H_

class FIO {
    std::string _first_name;
    std::string _second_name;
    std::string _last_name;

 public:
    FIO(const std::string&, const std::string&, const std::string&);
    FIO();
    FIO(const FIO&);

    ~FIO() = default;

    void set_first_name(const std::string&);
    void set_second_name(const std::string&);
    void set_last_name(const std::string&);
    void set_from_string(const std::string& name_str);

    const std::string get_first_name() const noexcept;
    const std::string get_second_name() const noexcept;
    const std::string get_last_name() const noexcept;
    const std::string get_full_name() const noexcept;

 private:
    bool check_to_correct_form(const std::string&) const noexcept;
    std::string convert_to_norm_form(const std::string&) const noexcept;
};
#endif  // FILM_LIBRARY_FIO_FIO_H_
