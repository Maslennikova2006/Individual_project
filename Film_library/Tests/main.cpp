// Copyright 2025 Maslennikova Mary

#include <iostream>
#include <Windows.h>
#include <string>

#include "/git/Film_library/Actor/Actor.h"
#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/Date_of_birth/Date.h"
#include "/git/Film_library/Feedback/Feedback.h"
#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Film_director/Director.h"
#include "/git/Film_library/Film_library/Film_library.h"
#include "/git/Film_library/FIO/FIO.h"
#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MyTVector/TVector.h"

// #define FIO_TESTS
// #define DATE_TESTS
#define TVECTOR_TESTS

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


#ifdef TVECTOR_TESTS
bool test_1_check_the_default_constructor() {
    TVector<float> vec;
    return TestSystem::check(static_cast <size_t>(0), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY),
            vec.capacity()) &&
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
    return TestSystem::check(static_cast <size_t>(5), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY),
            vec.capacity()) &&
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
    return TestSystem::check(static_cast <size_t>(4), vec.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY),
            vec.capacity()) &&
        TestSystem::check(true, check_address_data) &&
        TestSystem::check(true, check_correct_values_data);
}
bool test_4_throw_when_try_copy_vector() {
    TVector<int>* obj = nullptr;
    bool expected_result = false;
    bool actual_result = true;
    try {
        TVector<int> copy_obj(*obj);
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
    return TestSystem::check(static_cast <size_t>(5), vec2.size()) &&
        TestSystem::check(static_cast<size_t>(STEP_OF_CAPACITY),
            vec2.capacity()) &&
        TestSystem::check(true, check_address_data) &&
        TestSystem::check(true, check_correct_values_data);
}
bool test_6_check_for_equivalence() {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(4, { 1, 2, 3, 4 });
    bool expected_result = true;
    bool actual_result = (vec1 == vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_7_check_for_equivalence() {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(4, { 1, 2, 3, 4 });
    bool expected_result = false;
    bool actual_result = (vec1 != vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_8_check_for_not_equivalence() {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(5, { 1, 2, 3, 4, 5 });
    bool expected_result = true;
    bool actual_result = (vec1 != vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_9_check_for_not_equivalence() {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, array), vec2(4, { 1, 2, 3, 4 });
    bool expected_result = false;
    bool actual_result = (vec1 == vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_10_check_reserve_with_decreasing_capacity() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.reserve(5);
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_11_check_reserve_with_increasing_capacity() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.reserve(25);
    return TestSystem::check(static_cast<size_t>(25), vec.capacity());
}
bool test_12_check_resize_with_decreasing_size() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(5);
    TVector<int> res({ 1, 2, 3, 4, 5 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_13_check_resize_with_increasing_size_and_capacity() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(16);
    return TestSystem::check(static_cast<size_t>(16), vec.size()) &&
        TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
bool test_14_check_resize_with_filling_in_the_value() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(16, 0);
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(16), vec.size()) &&
        TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_15_check_shrink_to_fit() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.shrink_to_fit();
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(10), vec.size()) &&
        TestSystem::check(static_cast<size_t>(10), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_16_check_the_assignment_operator() {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    TVector<int> vec2;
    vec2 = vec1;
    bool expected_result = true;
    bool actual_result = (vec2 == vec1);
    return TestSystem::check(expected_result, actual_result);
}
bool test_17_check_the_index_conversion_operator() {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_value = 4;
    int actual_value = vec[3];
    return TestSystem::check(expected_value, actual_value);
}
bool test_18_check_the_index_conversion_operator() {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_value = 5;
    vec[3] = 5;
    return TestSystem::check(expected_value, vec[3]);
}
bool test_19_check_the_insertion_at_the_beginning() {
    TVector<int> vec(10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.push_front(55);
    TVector<int> res(11,
        { 55, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_20_check_the_insertion_in_the_middle() {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 3, 4 });
    vec.insert(3, 44);
    TVector<int> res(11, { 6, 2, 3, 44, 4, 5, 6, 7, 8, 3, 4 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_21_check_the_insertion_several_elems() {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 5, 6 });
    vec.insert(2, 4, 99);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        vec[2] == 99 && vec[5] == 99;
}
bool test_22_check_the_insertion_from_the_list() {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 99, 87 });
    vec.insert(3, { 11, 22, 33 });
    TVector<int> res(13,
        { 6, 2, 3, 11, 22, 33, 4, 5, 6, 7, 8, 99, 87 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_23_check_the_insertion_at_the_end() {
    TVector<int> vec(10, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6 });
    vec.push_back(9);
    TVector<int> res(11, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 9 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_24_check_the_insertion_at_the_beginning_with_memory_reallocation() {
    TVector<int> vec(15, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    vec.push_front(55);
    TVector<int> res(16,
        { 55, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_25_check_the_insertion_in_the_middle_with_memory_reallocation() {
    TVector<int> vec(15, { 6, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    vec.insert(3, 44);
    TVector<int> res(16, { 6, 2, 3, 44, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_26_check_the_insertion_several_elems_with_memory_reallocation() {
    TVector<int> vec(14, { 6, 2, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    vec.insert(2, 4, 99);
    TVector<int> res(18,
        { 6, 2, 99, 99, 99, 99, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_27_check_the_insertion_from_the_list_with_memory_reallocation() {
    TVector<int> vec(13, { 6, 2, 3, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    vec.insert(3, { 11, 22, 33 });
    TVector<int> res(16,
        { 6, 2, 3, 11, 22, 33, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_28_check_the_insertion_at_the_end_with_memory_reallocation() {
    TVector<int> vec(15, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6 });
    vec.push_back(9);
    TVector<int> res(16, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6, 9 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_29_check_for_deletion_from_the_beginning() {
    TVector<int> vec(10,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.pop_front();
    vec.pop_front();
    vec.pop_front();
    TVector<int> res(7, { 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_30_check_for_deletion_from_the_middle() {
    TVector<int> vec(10,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.erase(4);
    vec.erase(3);
    vec.erase(5);
    TVector<int> res(7, { 1, 2, 3, 6, 7, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_31_check_for_deletion_from_the_beginning_with_memory_reallocation() {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.pop_front();
    vec.pop_front();
    vec.pop_front();
    TVector<int> res(13, { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_32_check_for_deletion_from_the_middle_with_memory_reallocation() {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.erase(4);
    vec.erase(3);
    vec.erase(5);
    TVector<int> res(13, { 1, 2, 3, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(15), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_33_check_for_deletion_from_the_back() {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    TVector<int> res(13, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_34_check_for_complete_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.clear();
    return TestSystem::check(static_cast<size_t>(0), vec.size()) &&
        TestSystem::check(static_cast<size_t>(15), vec.capacity());
}
bool test_35_check_the_insertion_after_deletion() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3, 6);
    vec.insert(4, 55);
    vec.insert(6, { 33, 44, 55 });
    TVector<int> res({ 2, 3, 5, 10, 55, 11, 33, 44, 55, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_36_check_the_replacement_by_index() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.replace(4, 77);
    TVector<int> res({ 1, 2, 3, 4, 77, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_37_check_the_replacement_by_index_after_deleted() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    vec.replace(4, 55);
    TVector<int> res({ 2, 3, 5, 7, 55, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_38_check_at() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    size_t res = vec.at(4);
    bool expected_result = true;
    bool actual_result = (res == 5);
    return TestSystem::check(expected_result, actual_result);
}
bool test_39_check_the_exception_in_at() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = false;
    bool actual_result = true;
    try {
        size_t res = vec.at(10);
    }
    catch (const std::exception& ex) {
        actual_result &= false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_40_check_assign_value() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign(4, 66);
    TVector<int> res({ 66, 66, 66, 66 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_41_check_assign_list() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign({ 11, 22, 33, 44, 55, 66 });
    return (vec.front() == 11) && (vec.back() == 66) && (vec[3] == 44);
}
bool test_42_check_the_exception_when_going_out_of_bounds() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool actual_result_1 = false;
    bool actual_result_2 = false;
    bool actual_result_3 = false;
    bool actual_result_4 = false;
    bool actual_result_5 = false;
    bool actual_result_6 = false;
    bool expected_result = true;
    try {
        vec.insert(11, { 2, 3, 4 });
    }
    catch (const std::exception& ex) {
        actual_result_1 = true;
    }
    try {
        vec.insert(11, 2, 77);
    }
    catch (const std::exception& ex) {
        actual_result_2 = true;
    }
    try {
        vec.insert(12, 55);
    }
    catch (const std::exception& ex) {
        actual_result_3 = true;
    }
    try {
        vec.erase(12);
    }
    catch (const std::exception& ex) {
        actual_result_4 = true;
    }
    try {
        vec.erase(7, 18);
    }
    catch (const std::exception& ex) {
        actual_result_5 = true;
    }
    try {
        vec.replace(12, 8);
    }
    catch (const std::exception& ex) {
        actual_result_6 = true;
    }
    return TestSystem::check(expected_result, actual_result_1 &&
        actual_result_2 && actual_result_3 && actual_result_4 &&
        actual_result_5 && actual_result_6);
}
bool test_43_check_for_an_exception_when_interacting_with_an_empty_vector() {
    TVector<int> vec;
    bool actual_result_1 = false;
    bool actual_result_2 = false;
    bool actual_result_3 = false;
    bool actual_result_4 = false;
    bool actual_result_5 = false;
    bool actual_result_6 = false;
    bool expected_result = true;
    try {
        vec.pop_front();
    }
    catch (const std::exception& ex) {
        actual_result_1 = true;
    }
    try {
        vec.pop_back();
    }
    catch (const std::exception& ex) {
        actual_result_2 = true;
    }
    try {
        vec.clear();
    }
    catch (const std::exception& ex) {
        actual_result_3 = true;
    }
    try {
        vec.erase(10);
    }
    catch (const std::exception& ex) {
        actual_result_4 = true;
    }
    try {
        vec.erase(7, 18);
    }
    catch (const std::exception& ex) {
        actual_result_5 = true;
    }
    try {
        vec.replace(12, 8);
    }
    catch (const std::exception& ex) {
        actual_result_6 = true;
    }
    return TestSystem::check(expected_result, actual_result_1 &&
        actual_result_2 && actual_result_3 && actual_result_4 &&
        actual_result_5 && actual_result_6);
}
bool test_44_check_the_insertion_into_an_empty_vector() {
    TVector<int> vec1;
    vec1.push_front(1);
    TVector<int> res1({ 1 });
    TVector<int> vec2;
    vec2.push_back(10);
    TVector<int> res2({ 10 });
    TVector<int> vec3;
    vec3.insert(0, 88);
    TVector<int> res3({ 88 });
    bool expected_result = true;
    bool actual_result = false;
    if ((vec1 == res1) && (vec2 == res2) && (vec3 == res3))
        actual_result = true;

    return TestSystem::check(expected_result, actual_result);
}
bool test_45_check_shuffle_vector() {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    TVector<int> vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    bool expected_result = true;
    shuffle(vec2);
    bool actual_result = (vec1 != vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_46_check_hoara_sort() {
    TVector<int> vec({ 2, 7, 3, 9, 28, 38, 93, 9, 6, 4, 2 });
    hoara_sort(vec);
    TVector<int> res({ 2, 2, 3, 4, 6, 7, 9, 9, 28, 38, 93 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_47_check_find_first_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_first_elem_by_index(vec, 5);
    return TestSystem::check(2, pos);
}
bool test_48_check_find_first_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_first_elem_by_index(vec, 11);
    return TestSystem::check(-1, pos);
}
bool test_49_check_find_last_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_last_elem_by_index(vec, 5);
    return TestSystem::check(4, pos);
}
bool test_50_check_find_last_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_last_elem_by_index(vec, 11);
    return TestSystem::check(-1, pos);
}
bool test_51_check_find_several_elements() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    int* actual_indexes = find_elem_by_index(vec, 5);
    int expected_indexes[] = { 3, 2, 4, 8 };
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < 3; i++) {
        if (actual_indexes[i] == expected_indexes[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_52_check_find_several_elements_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    int* indexes = find_elem_by_index(vec, 15);
    return TestSystem::check(0, indexes[0]);
}
bool test_53_check_find_first_elem_after_deletion() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int pos = find_first_elem_by_index(vec, 7);
    bool expected_result = true;
    bool actual_result = (pos == 3);
    return TestSystem::check(expected_result, actual_result);
}
bool test_54_check_find_last_elem_after_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
        89, 90, 91, 92, 93, 94, 95, 96, 7, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int pos = find_last_elem_by_index(vec, 7);
    bool expected_result = true;
    bool actual_result = (pos == 93);
    return (vec.front() == 2) && (vec.back() == 99) && (vec[3] == 7) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_55_check_find_all_elements_after_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(30);
    vec.erase(3);
    int* indexes = find_elem_by_index(vec, 7);
    int right_indexes[] = { 4, 3, 17, 51, 84 };
    bool actual_result = true;
    bool expected_result = true;
    for (size_t i = 0; i < 5; i++) {
        if (indexes[i] == right_indexes[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_56_check_the_replacement_by_the_pointer() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    bool expected_result = true;
    vec.erase(2);
    vec.replace(vec.begin() + 4, 99);
    return (vec[0] == 1) && (vec[4] == 99);
}
bool test_57_check_shifted_insert_into_a_full_array_with_deleted_elems() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(5);
    vec.insert(5, 88);
    vec.insert(7, 99);
    return (vec[0] == 1) && (vec[5] == 88) && (vec[7] == 99)
        && TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
bool test_58_check_find_first_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_first_elem_by_pointer(vec, 5);
    return TestSystem::check(&vec[2], ptr) &&
        TestSystem::check(5, *ptr);
}
bool test_59_check_find_first_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* null_ptr = nullptr;
    int* ptr = find_first_elem_by_pointer(vec, 11);
    return TestSystem::check(null_ptr, ptr);
}
bool test_60_check_find_last_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_last_elem_by_pointer(vec, 5);
    return TestSystem::check(&vec[4], ptr) &&
        TestSystem::check(5, *ptr);
}
bool test_61_check_find_last_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* null_ptr = nullptr;
    int* ptr = find_last_elem_by_pointer(vec, 11);
    return TestSystem::check(null_ptr, ptr);
}
bool test_62_check_find_several_elements() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    TVector<int*> ptrs = find_elem_by_pointer(vec, 5);
    TVector<int*> true_ptrs({ &vec[2], &vec[4], &vec[8] });
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < ptrs.size(); i++) {
        if (ptrs[i] == true_ptrs[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    return TestSystem::check(static_cast<size_t>(3), ptrs.size()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_63_check_find_several_elements_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    TVector<int*> ptrs = find_elem_by_pointer(vec, 10);
    return TestSystem::check(static_cast<size_t>(0), ptrs.size());
}
bool test_64_check_find_first_elem_after_deletion() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int* ptr = find_first_elem_by_pointer(vec, 7);
    return TestSystem::check(&vec[3], ptr) &&
        TestSystem::check(7, *ptr);
}
bool test_65_check_find_last_elem_after_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
        89, 90, 91, 92, 93, 94, 95, 96, 7, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int* ptr = find_last_elem_by_pointer(vec, 7);
    return TestSystem::check(&vec[93], ptr) &&
        TestSystem::check(7, *ptr);
}
bool test_66_check_find_all_elements_after_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(30);
    vec.erase(3);
    TVector<int*> ptrs = find_elem_by_pointer(vec, 7);
    TVector<int*> true_ptrs({ &vec[3], &vec[17], &vec[51], &vec[84] });
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < ptrs.size(); i++) {
        if (ptrs[i] == true_ptrs[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    return TestSystem::check(static_cast<size_t>(4), ptrs.size()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_67_check_the_replace_by_the_pointer_after_searching_and_deleting() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    bool expected_result = false;
    bool actual_result = true;
    int* ptr = find_first_elem_by_pointer(vec, 10);
    vec.erase(9);
    try {
        vec.replace(ptr, 99);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_68_check_shifted_insert_into_a_full_array_with_deleted_elems() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(5);
    vec.insert(3, 2, 77);
    return (vec[0] == 1) && (vec[3] == 77) && (vec[4] == 77)
        && TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
bool test_69_check_shifted_insert_into_a_full_array_with_deleted_elems() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(3);
    vec.insert(3, { 3, 6 });
    return (vec[0] == 1) && (vec[3] == 3) && (vec[4] == 6)
        && TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
bool test_70_check_shifted_push_front_into_a_full_array_with_deleted_elems() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(3);
    vec.push_front(11);
    vec.push_front(22);
    return (vec.front() == 22) && (vec[1] == 11)
        && TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
bool test_71_check_shifted_push_back_into_a_full_array_with_deleted_elems() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(3);
    vec.push_back(11);
    vec.push_back(22);
    return (vec.back() == 22) && (vec[27] == 11)
        && TestSystem::check(static_cast<size_t>(30), vec.capacity());
}
#endif

#ifdef FIO_TESTS
bool FIO_test_1_check_the_default_constructor() {
    FIO person;
    return TestSystem::check((std::string)"Ivan", person.get_first_name()) &&
        TestSystem::check((std::string)"Ivanovich", person.get_second_name())
        && TestSystem::check((std::string)"Ivanov", person.get_last_name());
}
bool FIO_test_2_check_the_initialization_constructor() {
    FIO person("Mary", "Vyacheslavovna", "Maslennikova");
    return TestSystem::check((std::string)"Mary", person.get_first_name()) &&
        TestSystem::check((std::string)"Vyacheslavovna",
            person.get_second_name()) &&
        TestSystem::check((std::string)"Maslennikova", person.get_last_name());
}
bool FIO_test_3_check_the_exception_in_initialization_constructor() {
    bool expected_result = false;
    bool actual_result = true;
    try {
        FIO person("EL08na", "Sidorov a", "Petrovna_");
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool FIO_test_4_throw_when_try_copy_FIO() {
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
bool FIO_test_5_check_the_copy_constructor() {
    FIO person1("Anna", "Dmitrievna", "Danilova");
    FIO person2(person1);
    return TestSystem::check((std::string)"Anna", person2.get_first_name()) &&
        TestSystem::check((std::string)"Dmitrievna",
            person2.get_second_name()) &&
        TestSystem::check((std::string)"Danilova", person2.get_last_name());
}
bool FIO_test_6_check_the_setters() {
    FIO person("Anna", "Dmitrievna", "Danilova");
    person.set_first_name("Elena");
    person.set_second_name("Andreevna");
    person.set_last_name("Osipova");
    return TestSystem::check((std::string)"Elena", person.get_first_name()) &&
        TestSystem::check((std::string)"Andreevna", person.get_second_name())
        && TestSystem::check((std::string)"Osipova", person.get_last_name());
}
bool FIO_test_7_check_the_exception_in_the_setters() {
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
bool FIO_test_8_check_string_conversion_in_setters() {
    FIO person("Anna", "Dmitrievna", "Danilova");
    person.set_first_name("eLENA");
    person.set_second_name("anDreEvnA");
    person.set_last_name("OsIpOvA");
    return TestSystem::check((std::string)"Elena", person.get_first_name()) &&
        TestSystem::check((std::string)"Andreevna", person.get_second_name())
        && TestSystem::check((std::string)"Osipova", person.get_last_name());
}
#endif  // FIO_TESTS

#ifdef DATE_TESTS
bool Date_test_1_check_the_default_constructor() {
    Date date;
    return TestSystem::check(1, date.get_day()) &&
        TestSystem::check(1, date.get_month()) &&
        TestSystem::check(2025, date.get_year());
}
bool Date_test_2_check_the_initialization_constructor() {
    Date date(22, 3, 2006);
    return TestSystem::check(22, date.get_day()) &&
        TestSystem::check(3, date.get_month()) &&
        TestSystem::check(2006, date.get_year());
}
bool Date_test_3_check_the_exception_in_initialization_constructor() {
    bool expected_result = false;
    bool actual_result = true;
    try {
        Date date(29, 2, 2023);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool Date_test_4_throw_when_try_copy_date() {
    Date* date = nullptr;
    bool expected_result = false;
    bool actual_result = true;
    try {
        Date copy_date(*date);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool Date_test_5_check_the_copy_constructor() {
    Date date1(11, 5, 2025);
    Date date2(date1);
    return TestSystem::check(11, date2.get_day()) &&
        TestSystem::check(5, date2.get_month()) &&
        TestSystem::check(2025, date2.get_year());
}
bool Date_test_6_check_the_setters() {
    Date date(8, 11, 1970);
    date.set_date(23, 12, 1973);
    return TestSystem::check(23, date.get_day()) &&
        TestSystem::check(12, date.get_month()) &&
        TestSystem::check(1973, date.get_year());
}
bool Date_test_7_check_the_exception_in_the_setters() {
    Date date;
    bool expected_result = true;
    bool actual_result = true;
    try {
        date.set_date(32, 12, 2007);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        date.set_date(29, 2, 2025);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        date.set_date(2, 13, 1956);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        date.set_date(2, 3, 1756);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    return TestSystem::check(expected_result, actual_result);
}
#endif  // DATE_TESTS

int main() {
#ifdef TVECTOR_TESTS
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
    TestSystem::start_test(test_6_check_for_equivalence,
        "TVector.test_6_check_for_equivalence");
    TestSystem::start_test(test_7_check_for_equivalence,
        "TVector.test_7_check_for_equivalence");
    TestSystem::start_test(test_8_check_for_not_equivalence,
        "TVector.test_8_check_for_not_equivalence");
    TestSystem::start_test(test_9_check_for_not_equivalence,
        "TVector.test_9_check_for_not_equivalence");
    TestSystem::start_test(test_10_check_reserve_with_decreasing_capacity,
        "TVector.test_10_check_reserve_with_decreasing_capacity");
    TestSystem::start_test(test_11_check_reserve_with_increasing_capacity,
        "TVector.test_11_check_reserve_with_increasing_capacity");
    TestSystem::start_test(test_12_check_resize_with_decreasing_size,
        "TVector.test_12_check_resize_with_decreasing_size");
    TestSystem::start_test(
        test_13_check_resize_with_increasing_size_and_capacity,
        "TVector.test_13_check_resize_with_increasing_size_and_capacity");
    TestSystem::start_test(test_14_check_resize_with_filling_in_the_value,
        "TVector.test_14_check_resize_with_filling_in_the_value");
    TestSystem::start_test(test_15_check_shrink_to_fit,
        "TVector.test_15_check_shrink_to_fit");
    TestSystem::start_test(test_16_check_the_assignment_operator,
        "TVector.test_16_check_the_assignment_operator");
    TestSystem::start_test(test_17_check_the_index_conversion_operator,
        "TVector.test_17_check_the_index_conversion_operator");
    TestSystem::start_test(test_18_check_the_index_conversion_operator,
        "TVector.test_18_check_the_index_conversion_operator");
    TestSystem::start_test(test_19_check_the_insertion_at_the_beginning,
        "TVector.test_19_check_the_insertion_at_the_beginning");
    TestSystem::start_test(test_20_check_the_insertion_in_the_middle,
        "TVector.test_20_check_the_insertion_in_the_middle");
    TestSystem::start_test(test_21_check_the_insertion_several_elems,
        "TVector.test_21_check_the_insertion_several_elems");
    TestSystem::start_test(test_22_check_the_insertion_from_the_list,
        "TVector.test_22_check_the_insertion_from_the_list");
    TestSystem::start_test(test_23_check_the_insertion_at_the_end,
        "TVector.test_23_check_the_insertion_at_the_end");
    TestSystem::start_test(
        test_24_check_the_insertion_at_the_beginning_with_memory_reallocation,
        "TVector.test_24_check_the_insertion_at_the_begin_with_reallocation");
    TestSystem::start_test(
        test_25_check_the_insertion_in_the_middle_with_memory_reallocation,
        "TVector.test_25_check_the_insertion_in_the_middle_with_reallocation");
    TestSystem::start_test(
        test_26_check_the_insertion_several_elems_with_memory_reallocation,
        "TVector.test_26_check_the_insertion_several_elems_with_reallocation");
    TestSystem::start_test(
        test_27_check_the_insertion_from_the_list_with_memory_reallocation,
        "TVector.test_27_check_the_insertion_from_the_list_with_reallocation");
    TestSystem::start_test(
        test_28_check_the_insertion_at_the_end_with_memory_reallocation,
        "TVector.test_28_check_the_insertion_at_the_end_with_reallocation");
    TestSystem::start_test(test_29_check_for_deletion_from_the_beginning,
        "TVector.test_29_check_for_deletion_from_the_beginning");
    TestSystem::start_test(test_30_check_for_deletion_from_the_middle,
        "TVector.test_30_check_for_deletion_from_the_middle");
    TestSystem::start_test(
        test_31_check_for_deletion_from_the_beginning_with_memory_reallocation,
        "TVector.test_31_check_for_deletion_from_the_beginning_with_realloc");
    TestSystem::start_test(
        test_32_check_for_deletion_from_the_middle_with_memory_reallocation,
        "TVector.test_32_check_for_deletion_from_the_middle_with_realloc");
    TestSystem::start_test(test_33_check_for_deletion_from_the_back,
        "TVector.test_33_check_for_deletion_from_the_back");
    TestSystem::start_test(test_34_check_for_complete_deletion,
        "TVector.test_34_check_for_complete_deletion");
    TestSystem::start_test(test_35_check_the_insertion_after_deletion,
        "TVector.test_35_check_the_insertion_after_deletion");
    TestSystem::start_test(test_36_check_the_replacement_by_index,
        "TVector.test_36_check_the_replacement_by_index");
    TestSystem::start_test(
        test_37_check_the_replacement_by_index_after_deleted,
        "TVector.test_37_check_the_replacement_by_index_after_deleted");
    TestSystem::start_test(test_38_check_at, "TVector.test_38_check_at");
    TestSystem::start_test(test_39_check_the_exception_in_at,
        "TVector.test_39_check_the_exception_in_at");
    TestSystem::start_test(test_40_check_assign_value,
        "TVector.test_40_check_assign_value");
    TestSystem::start_test(test_41_check_assign_list,
        "TVector.test_41_check_assign_list");
    TestSystem::start_test(
        test_42_check_the_exception_when_going_out_of_bounds,
        "TVector.test_42_check_the_exception_when_going_out_of_bounds");
    TestSystem::start_test(
        test_43_check_for_an_exception_when_interacting_with_an_empty_vector,
        "TVector.test_43_check_except_when_interacting_with_an_empty_vec");
    TestSystem::start_test(test_44_check_the_insertion_into_an_empty_vector,
        "TVector.test_44_check_the_insertion_into_an_empty_vector");
    TestSystem::start_test(test_45_check_shuffle_vector,
        "TVector.test_45_check_shuffle_vector");
    TestSystem::start_test(test_46_check_hoara_sort,
        "TVector.test_46_check_hoara_sort");
    TestSystem::start_test(test_47_check_find_first_element,
        "TVector.test_47_check_find_first_element");
    TestSystem::start_test(
        test_48_check_find_first_element_if_there_is_no_element,
        "TVector.test_48_check_find_first_element_if_there_is_no_element");
    TestSystem::start_test(test_49_check_find_last_element,
        "TVector.test_49_check_find_last_element");
    TestSystem::start_test(
        test_50_check_find_last_element_if_there_is_no_element,
        "TVector.test_50_check_find_last_element_if_there_is_no_element");
    TestSystem::start_test(test_51_check_find_several_elements,
        "TVector.test_51_check_find_several_elements");
    TestSystem::start_test(
        test_52_check_find_several_elements_if_there_is_no_element,
        "TVector.test_52_check_find_several_elements_if_there_is_no_element");
    TestSystem::start_test(test_53_check_find_first_elem_after_deletion,
        "TVector.test_53_check_find_first_elem_after_deletion");
    TestSystem::start_test(test_54_check_find_last_elem_after_deletion,
        "TVector.test_54_check_find_last_elem_after_deletion");
    TestSystem::start_test(test_55_check_find_all_elements_after_deletion,
        "TVector.test_55_check_find_all_elements_after_deletion");
    TestSystem::start_test(test_56_check_the_replacement_by_the_pointer,
        "TVector.test_56_check_the_replacement_by_the_pointer");
    TestSystem::start_test(
        test_57_check_shifted_insert_into_a_full_array_with_deleted_elems,
        "TVector.test_57_check_shift_insert_into_a_array_with_deleted_elems");
    TestSystem::start_test(test_58_check_find_first_element,
        "TVector.test_58_check_find_first_element");
    TestSystem::start_test(
        test_59_check_find_first_element_if_there_is_no_element,
        "TVector.test_59_check_find_first_element_if_there_is_no_element");
    TestSystem::start_test(test_60_check_find_last_element,
        "TVector.test_60_check_find_last_element");
    TestSystem::start_test(
        test_61_check_find_last_element_if_there_is_no_element,
        "TVector.test_61_check_find_last_element_if_there_is_no_element");
    TestSystem::start_test(test_62_check_find_several_elements,
        "TVector.test_62_check_find_several_elements");
    TestSystem::start_test(
        test_63_check_find_several_elements_if_there_is_no_element,
        "TVector.test_63_check_find_several_elements_if_there_is_no_element");
    TestSystem::start_test(test_64_check_find_first_elem_after_deletion,
        "TVector.test_64_check_find_first_elem_after_deletion");
    TestSystem::start_test(test_65_check_find_last_elem_after_deletion,
        "TVector.test_65_check_find_last_elem_after_deletion");
    TestSystem::start_test(test_66_check_find_all_elements_after_deletion,
        "TVector.test_66_check_find_all_elements_after_deletion");
    TestSystem::start_test(
        test_67_check_the_replace_by_the_pointer_after_searching_and_deleting,
        "TVector.test_67_check_the_replace_by_ptr_after_search_and_delete");
    TestSystem::start_test(
        test_68_check_shifted_insert_into_a_full_array_with_deleted_elems,
        "TVector.test_68_check_shift_insert_in_a_array_with_deleted_elems");
    TestSystem::start_test(
        test_69_check_shifted_insert_into_a_full_array_with_deleted_elems,
        "TVector.test_69_check_shift_insert_in_a_array_with_deleted_elems");
    TestSystem::start_test(
        test_70_check_shifted_push_front_into_a_full_array_with_deleted_elems,
        "TVector.test_70_check_shift_push_front_in_a_array_with_deleted_elem");
    TestSystem::start_test(
        test_71_check_shifted_push_back_into_a_full_array_with_deleted_elems,
        "TVector.test_71_check_shift_push_back_in_a_array_with_deleted_elem");
#endif  // TVECTOR_TESTS

#ifdef FIO_TESTS
    TestSystem::start_test(FIO_test_1_check_the_default_constructor,
        "FIO.test_1_check_the_default_constructor");
    TestSystem::start_test(FIO_test_2_check_the_initialization_constructor,
        "FIO.test_2_check_the_initialization_constructor");
    TestSystem::start_test(
        FIO_test_3_check_the_exception_in_initialization_constructor,
        "FIO_test_3_check_the_exception_in_initialization_constructor");
    TestSystem::start_test(FIO_test_4_throw_when_try_copy_FIO,
        "FIO.test_4_throw_when_try_copy_FIO");
    TestSystem::start_test(FIO_test_5_check_the_copy_constructor,
        "FIO.test_5_check_the_copy_constructor");
    TestSystem::start_test(FIO_test_6_check_the_setters,
        "FIO.test_6_check_the_setters");
    TestSystem::start_test(FIO_test_7_check_the_exception_in_the_setters,
        "FIO.test_7_check_the_exception_in_the_setters");
    TestSystem::start_test(FIO_test_8_check_string_conversion_in_setters,
        "FIO.test_8_check_string_conversion_in_setters");
#endif  // FIO_TESTS

#ifdef DATE_TESTS
    TestSystem::start_test(Date_test_1_check_the_default_constructor,
        "Date.test_1_check_the_default_constructor");
    TestSystem::start_test(Date_test_2_check_the_initialization_constructor,
        "Date.test_2_check_the_initialization_constructor");
    TestSystem::start_test(
        Date_test_3_check_the_exception_in_initialization_constructor,
        "Date.test_3_check_the_exception_in_initialization_constructor");
    TestSystem::start_test(Date_test_4_throw_when_try_copy_date,
        "Date.test_4_throw_when_try_copy_date");
    TestSystem::start_test(Date_test_5_check_the_copy_constructor,
        "Date.test_5_check_the_copy_constructor");
    TestSystem::start_test(Date_test_6_check_the_setters,
        "Date.test_6_check_the_setters");
    TestSystem::start_test(Date_test_7_check_the_exception_in_the_setters,
        "Date.test_7_check_the_exception_in_the_setters");
#endif  // DATE_TESTS

    TestSystem::print_init_info();
    TestSystem::print_final_info();
    return 0;
}
