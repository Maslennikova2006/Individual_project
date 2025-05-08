// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <Windows.h>

#include "/git/Film_library/Actor/Actor.h"
#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/Date_of_birth/Date.h"
#include "/git/Film_library/Feedback/Feedback.h"
#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Film_director/Director.h"
#include "/git/Film_library/Film_library/Film_library.h"
#include "/git/Film_library/FIO/FIO.h"
#include "/git/Film_library/User/User.h"

#define FIO_TESTS

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
    int count_success = 0, count_failed = 0;
    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0);
        std::cout << "[ RUN      ] ";
        set_color(7, 0);
        std::cout << name_of_test << std::endl;

        bool status = test();

        if (status == true) {
            set_color(2, 0);
            std::cout << "[       OK ]" << std::endl;
            count_success++;
        }
        else {
            set_color(4, 0);
            std::cout << "[  FAILED  ]" << std::endl;
            count_failed++;
        }
        set_color(7, 0);
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        else {
            std::cerr << "Expected result is " << expected << ", but actual is "
                << actual << "." << std::endl;
            return false;
        }
    }

    void print_init_info() {
        set_color(2, 0);
        std::cout << "[==========] " << std::endl;
        set_color(7, 0);
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test"
            << (count_success + count_failed > 1 ? "s" : "")
            << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test"
            << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test"
                << (count_failed > 1 ? "s." : ".") << std::endl;
        }
    }
};  // namespace TestSystem

#ifdef FIO_TESTS
bool FIO_test_1_check_the_default_constructor() {
    FIO person;
    return TestSystem::check((std::string)"Ivan", person.get_first_name()) &&
        TestSystem::check((std::string)"Ivanovich", person.get_second_name()) &&
        TestSystem::check((std::string)"Ivanov", person.get_last_name());
}
bool FIO_test_2_check_the_initialization_constructor() {
    FIO person("Mary", "Vyacheslavovna", "Maslennikova");
    return TestSystem::check((std::string)"Mary", person.get_first_name()) &&
        TestSystem::check((std::string)"Vyacheslavovna", person.get_second_name()) &&
        TestSystem::check((std::string)"Maslennikova", person.get_last_name());
}
bool FIO_test_3_throw_when_try_copy_vector() {
    FIO* person = nullptr;
    bool expected_result = false;
    bool actual_result = true;
    try {
        FIO copy_person(*person);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool FIO_test_4_check_the_copy_constructor() {
    FIO person1("Anna", "Dmitrievna", "Danilova");
    FIO person2(person1);
    return TestSystem::check((std::string)"Anna", person2.get_first_name()) &&
        TestSystem::check((std::string)"Dmitrievna", person2.get_second_name()) &&
        TestSystem::check((std::string)"Danilova", person2.get_last_name());
}
bool FIO_test_5_check_the_setters() {
    FIO person("Anna", "Dmitrievna", "Danilova");
    person.set_first_name("Elena");
    person.set_second_name("Andreevna");
    person.set_last_name("Osipova");
    return TestSystem::check((std::string)"Elena", person.get_first_name()) &&
        TestSystem::check((std::string)"Andreevna", person.get_second_name()) &&
        TestSystem::check((std::string)"Osipova", person.get_last_name());
}
bool FIO_test_6_check_the_exception_in_the_setters() {
    FIO person;
    bool expected_result = true;
    bool actual_result = true;
    try {
        person.set_first_name("Ele na");
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        person.set_second_name("Andr99eevna");
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        person.set_last_name("Osi__pova");
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool FIO_test_7_check_string_conversion_in_setters() {
    FIO person("Anna", "Dmitrievna", "Danilova");
    person.set_first_name("eLENA");
    person.set_second_name("anDreEvnA");
    person.set_last_name("OsIpOvA");
    return TestSystem::check((std::string)"Elena", person.get_first_name()) &&
        TestSystem::check((std::string)"Andreevna", person.get_second_name()) &&
        TestSystem::check((std::string)"Osipova", person.get_last_name());
}
#endif
int main() {
#ifdef FIO_TESTS
    TestSystem::start_test(FIO_test_1_check_the_default_constructor,
        "FIO.test_1_check_the_default_constructor");
    TestSystem::start_test(FIO_test_2_check_the_initialization_constructor,
        "FIO.test_2_check_the_initialization_constructor");
    TestSystem::start_test(FIO_test_3_throw_when_try_copy_vector,
        "FIO.test_3_throw_when_try_copy_vector");
    TestSystem::start_test(FIO_test_4_check_the_copy_constructor,
        "FIO.test_4_check_the_copy_constructor");
    TestSystem::start_test(FIO_test_5_check_the_setters,
        "FIO.test_5_check_the_setters");
    TestSystem::start_test(FIO_test_6_check_the_exception_in_the_setters,
        "FIO.test_6_check_the_exception_in_the_setters");
    TestSystem::start_test(FIO_test_7_check_string_conversion_in_setters,
        "FIO.test_7_check_string_conversion_in_setters");
#endif
    TestSystem::print_init_info();
    TestSystem::print_final_info();
    return 0;
}
