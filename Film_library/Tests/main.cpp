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

bool test_1_check_the_default_constructor() {
    TVector<float> vec;
    return TestSystem::check(static_cast < size_t>(0), vec.size()) &&
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
    return TestSystem::check(static_cast < size_t>(5), vec.size()) &&
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
    return TestSystem::check(static_cast < size_t>(4), vec.size()) &&
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
    return TestSystem::check(static_cast < size_t>(5), vec2.size()) &&
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
bool test_19_check_the_insertion_at_the_beginning_with_memory_reallocation() {
    TVector<int> vec(15, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    vec.push_front(55);
    TVector<int> res(16,
        { 55, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_20_check_the_insertion_in_the_middle_with_memory_reallocation() {
    TVector<int> vec(15, { 6, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    vec.insert(3, 44);
    TVector<int> res(16, { 6, 2, 3, 44, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_21_check_the_insertion_several_elems_with_memory_reallocation() {
    TVector<int> vec(14, { 6, 2, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    vec.insert(2, 4, 99);
    TVector<int> res(18,
        { 6, 2, 99, 99, 99, 99, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_22_check_the_insertion_from_the_list_with_memory_reallocation() {
    TVector<int> vec(13, { 6, 2, 3, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    vec.insert(3, { 11, 22, 33 });
    TVector<int> res(16,
        { 6, 2, 3, 11, 22, 33, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_23_check_the_insertion_at_the_end_with_memory_reallocation() {
    TVector<int> vec(15, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6 });
    vec.push_back(9);
    TVector<int> res(16, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6, 9 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(static_cast<size_t>(30), vec.capacity()) &&
        TestSystem::check(expected_result, actual_result);
}
bool test_24_check_for_deletion_from_the_beginning_with_memory_reallocation() {
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
bool test_25_check_for_deletion_from_the_middle_with_memory_reallocation() {
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
bool test_26_check_for_deletion_from_the_back() {
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
bool test_27_check_for_complete_deletion() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.clear();
    TVector<int> res;
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(static_cast<size_t>(0), vec.size());
}
bool test_28_check_the_insertion_after_deletion() {
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
bool test_29_check_the_replacement_by_index() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.replace(4, 77);
    TVector<int> res({ 1, 2, 3, 4, 77, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_30_check_the_replacement_by_index_after_deleted() {
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
bool test_31_check_at() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    int res = vec.at(4);
    bool expected_result = true;
    bool actual_result = (res == 5);
    return TestSystem::check(expected_result, actual_result);
}
bool test_32_check_assign_value() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign(4, 66);
    TVector<int> res({ 66, 66, 66, 66 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_33_check_assign_list() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign({ 11, 22, 33, 44, 55, 66 });
    TVector<int> res({ 11, 22, 33, 44, 55, 66 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_34_check_the_exception_when_going_out_of_bounds() {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool actual_result = true;
    bool expected_result = true;
    try {
        vec.insert(11, { 2, 3, 4 });
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.insert(11, 2, 77);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.insert(12, 55);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.erase(12);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.erase(7, 18);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.replace(12, 8);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_35_check_for_an_exception_when_interacting_with_an_empty_vector() {
    TVector<int> vec;
    bool actual_result = true;
    bool expected_result = true;
    try {
        vec.pop_front();
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.pop_back();
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.clear();
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.erase(10);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.erase(7, 18);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    try {
        vec.replace(12, 8);
        actual_result &= false;
    }
    catch (const std::exception& ex) {
        actual_result &= true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_36_check_the_insertion_into_an_empty_vector() {
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
bool test_37_check_shuffle_vector() {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    TVector<int> vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    bool expected_result = true;
    shuffle(vec2);
    bool actual_result = (vec1 != vec2);
    return TestSystem::check(expected_result, actual_result);
}
bool test_38_check_hoara_sort() {
    TVector<int> vec({ 2, 7, 3, 9, 28, 38, 93, 9, 6, 4, 2 });
    hoara_sort(vec);
    TVector<int> res({ 2, 2, 3, 4, 6, 7, 9, 9, 28, 38, 93 });
    bool expected_result = true;
    bool actual_result = (vec == res);
    return TestSystem::check(expected_result, actual_result);
}
bool test_39_check_find_first_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    size_t pos = find_first_elem(vec, 5);
    return TestSystem::check(static_cast<size_t>(2), pos);
}
bool test_40_check_find_first_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    bool expected_result = true;
    bool actual_result = false;
    try {
        size_t pos = find_first_elem(vec, 11);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_41_check_find_last_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    size_t pos = find_last_elem(vec, 5);
    return TestSystem::check(static_cast < size_t>(4), pos);
}
bool test_42_check_find_last_element_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    bool expected_result = true;
    bool actual_result = false;
    try {
        size_t pos = find_last_elem(vec, 11);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_43_check_find_several_elements() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    size_t* actual_indexes = find_elem(vec, 5);
    size_t expected_indexes[] = { 3, 2, 4, 8 };
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
bool test_44_check_find_several_elements_if_there_is_no_element() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    bool expected_result = true;
    bool actual_result = false;
    try {
        size_t* actual_indexes = find_elem(vec, 15);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_45_check_the_exception_when_accessing_the_index() {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    bool expected_result = true;
    bool actual_result_1 = false;
    bool actual_result_2 = false;
    try {
        size_t value = vec[10];
    }
    catch (const std::exception& ex) {
        actual_result_1 = true;
    }
    try {
        vec[10] = 55;
    }
    catch (const std::exception& ex) {
        actual_result_2 = true;
    }
    return TestSystem::check
    (expected_result, actual_result_1 && actual_result_2);
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
    TestSystem::
        start_test(test_13_check_resize_with_increasing_size_and_capacity,
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
    TestSystem::start_test(
        test_19_check_the_insertion_at_the_beginning_with_memory_reallocation,
        "TVector.test_19_check_the_insertion_at_the_begin_with_reallocation");
    TestSystem::start_test(
        test_20_check_the_insertion_in_the_middle_with_memory_reallocation,
        "TVector.test_20_check_the_insertion_in_the_middle_with_reallocation");
    TestSystem::start_test(
        test_21_check_the_insertion_several_elems_with_memory_reallocation,
        "TVector.test_21_check_the_insertion_several_elems_with_reallocation");
    TestSystem::start_test(
        test_22_check_the_insertion_from_the_list_with_memory_reallocation,
        "TVector.test_22_check_the_insertion_from_the_list_with_reallocation");
    TestSystem::start_test(
        test_23_check_the_insertion_at_the_end_with_memory_reallocation,
        "TVector.test_23_check_the_insertion_at_the_end_with_reallocation");
    TestSystem::start_test(
        test_24_check_for_deletion_from_the_beginning_with_memory_reallocation,
        "TVector.test_24_check_for_deletion_from_the_beginning_with_realloc");
    TestSystem::start_test(
        test_25_check_for_deletion_from_the_middle_with_memory_reallocation,
        "TVector.test_25_check_for_deletion_from_the_middle_with_realloc");
    TestSystem::start_test(test_26_check_for_deletion_from_the_back,
        "TVector.test_26_check_for_deletion_from_the_back");
    TestSystem::start_test(test_27_check_for_complete_deletion,
        "TVector.test_27_check_for_complete_deletion");
    TestSystem::start_test(test_28_check_the_insertion_after_deletion,
        "TVector.test_28_check_the_insertion_after_deletion");
    TestSystem::start_test(test_29_check_the_replacement_by_index,
        "TVector.test_29_check_the_replacement_by_index");
    TestSystem::start_test(
        test_30_check_the_replacement_by_index_after_deleted,
        "TVector.test_30_check_the_replacement_by_index_after_deleted");
    TestSystem::start_test(test_31_check_at, "TVector.test_31_check_at");
    TestSystem::start_test(test_32_check_assign_value,
        "TVector.test_32_check_assign_value");
    TestSystem::start_test(test_33_check_assign_list,
        "TVector.test_33_check_assign_list");
    TestSystem::start_test(
        test_34_check_the_exception_when_going_out_of_bounds,
        "TVector.test_34_check_the_exception_when_going_out_of_bounds");
    TestSystem::start_test(
        test_35_check_for_an_exception_when_interacting_with_an_empty_vector,
        "TVector.test_35_check_except_when_interacting_with_an_empty_vec");
    TestSystem::start_test(test_36_check_the_insertion_into_an_empty_vector,
        "TVector.test_36_check_the_insertion_into_an_empty_vector");
    TestSystem::start_test(test_37_check_shuffle_vector,
        "TVector.test_37_check_shuffle_vector");
    TestSystem::start_test(test_38_check_hoara_sort,
        "TVector.test_38_check_hoara_sort");
    TestSystem::start_test(test_39_check_find_first_element,
        "TVector.test_39_check_find_first_element");
    TestSystem::start_test(
        test_40_check_find_first_element_if_there_is_no_element,
        "TVector.test_40_check_find_first_element_if_there_is_no_element");
    TestSystem::start_test(test_41_check_find_last_element,
        "TVector.test_41_check_find_last_element");
    TestSystem::start_test(
        test_42_check_find_last_element_if_there_is_no_element,
        "TVector.test_42_check_find_last_element_if_there_is_no_element");
    TestSystem::start_test(test_43_check_find_several_elements,
        "TVector.test_43_check_find_several_elements");
    TestSystem::start_test(
        test_44_check_find_several_elements_if_there_is_no_element,
        "TVector.test_44_check_find_several_elements_if_there_is_no_element");
    TestSystem::start_test(
        test_45_check_the_exception_when_accessing_the_index,
        "TVector.test_45_check_the_exception_when_accessing_the_index");
    TestSystem::print_init_info();
    TestSystem::print_final_info();
    return 0;
}
