// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <Windows.h>
#include <clocale>

#include "/git/Film_library/Actor/Actor.h"
#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/Date_of_birth/Date.h"
#include "/git/Film_library/Feedback/Feedback.h"
#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Film_director/Director.h"
#include "/git/Film_library/Film_library/Film_library.h"
#include "/git/Film_library/FIO/FIO.h"
#include "/git/Film_library/TVector/TVector.h"
#include "/git/Film_library/User/User.h"

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
    } else {
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
    } else {
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
        << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
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
};

bool test_1_check_the_default_constructor() {
    TVector<float> vec;
    return TestSystem::check(static_cast < size_t>(0), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity()) &&
        TestSystem::check(true, vec.is_empty());
}
bool test_2_check_the_initialization_constructor() {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(5, array);
    bool check_address_data = (vec.data() != nullptr);
    bool check_correct_values_data = true;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == array[i])
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    return TestSystem::check(static_cast < size_t>(5), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity()) &&
        TestSystem::check(true, check_address_data) &&
        TestSystem::check(true, check_correct_values_data);
}
bool test_3_check_the_initialization_list_constructor() {
    TVector<int> vec(4, { 1, 2, 3, 4 });
    bool check_address_data = (vec.data() != nullptr);
    bool check_correct_values_data = true;
    int v;
    for (size_t i = 0, v = 1; i < vec.size(); i++, v++) {
        if (vec[i] == v)
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    return TestSystem::check(static_cast < size_t>(4), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity()) &&
        TestSystem::check(true, check_address_data) &&
        TestSystem::check(true, check_correct_values_data);
}
bool test_4_throw_when_try_copy_vector() {
    TVector<int>* obj = nullptr;
    bool expected_result = false;
    bool actual_result = true;
    try {
        TVector<int> copy(*obj);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_5_check_the_copy_constructor() {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, array);
    TVector<int> vec2(vec1);
    bool check_address_data = (vec2.data() != nullptr);
    bool check_correct_values_data = true;
    for (size_t i = 0; i < vec2.size(); i++) {
        if (vec2[i] == array[i])
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    return TestSystem::check(static_cast < size_t>(5), vec2.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY), vec2.capacity()) &&
        TestSystem::check(true, check_address_data) &&
        TestSystem::check(true, check_correct_values_data);
}
int main() {
    TestSystem::start_test(test_1_check_the_default_constructor, 
        "TVector.test_1_check_the_default_constructor");
    TestSystem::start_test(test_2_check_the_initialization_constructor, 
        "TVector.test_2_check_the_initialization_constructor");
    TestSystem::start_test(test_3_check_the_initialization_list_constructor, 
        "TVector.test_3_check_the_initialization_list_constructor");
    TestSystem::start_test(test_4_throw_when_try_copy_vector, 
        "TVector.test_4_throw_when_try_copy_vector");
    TestSystem::start_test(test_5_check_the_copy_constructor, 
        "TVector.test_5_check_the_copy_constructor");
    TestSystem::print_init_info();
    TestSystem::print_final_info();
    return 0;
}
