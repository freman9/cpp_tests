#ifndef TALS_INCLUDED
#define TALS_INCLUDED

#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <functional>

using namespace std::chrono_literals;

//-------------------------
#include <windows.h>

#define RED 4
#define YELLOW 6
#define GREY 8
#define BLUE 9
#define WHITE 15

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#define debug(name) printer(#name, "=>", (name), "\n")

#define debugVec(name)    \
    printer(#name, "=>"); \
    printerVec(name);

template <int color = WHITE, typename T>
void printerVec(std::vector<T> vec)
{
    if (color != WHITE)
        SetConsoleTextAttribute(hConsole, color);

    for (auto &&i : vec)
        std::cout << " " << i;

    std::cout << "\n";

    if (color != WHITE)
        SetConsoleTextAttribute(hConsole, WHITE);
}

template <int color = WHITE, typename... Args>
void printer(Args &&...args)
{
    if (color != WHITE)
        SetConsoleTextAttribute(hConsole, color);

    (std::cout << ... << args);

    if (color != WHITE)
        SetConsoleTextAttribute(hConsole, WHITE);
}
//-------------------------

// namespace tals
//{
std::string unitTest(const std::function<std::vector<bool>()> func, const std::string name, const bool verbose = true)
{
    if (verbose)
    {
        printer("---------------------------------\n");
        printer("running unit tests for ", name, "\n");
    }

    bool summary = true;
    for (auto &&elem : func())
    {
        if (elem != true)
        {
            summary = false;
            if (verbose)
                printer<RED>("fail ");
        }
        else if (verbose)
            printer<BLUE>("pass ");
    }

    if (verbose)
        printer("\n---------------------------------\n");

    return summary ? "pass" : "fail";
}

auto stop_watch_start = std::chrono::high_resolution_clock::now();
double stopWatch(const bool state, const bool verbose = true)
{
    if (state)
    {
        stop_watch_start = std::chrono::high_resolution_clock::now();
        return 1;
    }
    else
    {
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - stop_watch_start;

        if (verbose)
            printer("running time ", diff.count(), " sec\n");

        return diff.count();
    }
}
std::vector<bool> test_stopWatch()
{
    std::vector<bool> unit_test_result_vec;

    std::vector<int> try_vec(7, 2);
    double result = stopWatch(true);
    unit_test_result_vec.emplace_back((result == 1) ? true : false);

    result = stopWatch(false);
    debug(result);
    unit_test_result_vec.emplace_back(((result > 0) && (result < 1)) ? true : false);

    return unit_test_result_vec;
}
// debug(unitTest(&test_stopWatch, "stopWatch()"));

template <typename T>
std::vector<T> vectorSplitter(const T vector_to_split, const size_t num_of_splits)
{
    std::vector<T> vectors_to_return(num_of_splits);

    auto range = vector_to_split.size() / num_of_splits;

    for (size_t i = 0; i < vector_to_split.size(); i++)
    {
        auto idx = i / range;

        if (idx >= num_of_splits)
            idx = num_of_splits - 1;

        vectors_to_return[idx].emplace_back(vector_to_split[i]);
    }

    return vectors_to_return;
}
std::vector<bool> test_vectorSplitter()
{
    std::vector<bool> unit_test_result_vec;

    std::vector<int> try_vec(7, 2);
    std::vector<std::vector<int>> result = vectorSplitter(try_vec, 3);
    unit_test_result_vec.emplace_back((result.size() == 3) ? true : false);

    result = vectorSplitter(try_vec, 7);
    unit_test_result_vec.emplace_back((result.size() == 7) ? true : false);

    unit_test_result_vec.emplace_back((result[0][0] == 2) ? true : false);

    return unit_test_result_vec;
}
// debug(unitTest(&test_vectorSplitter, "vectorSplitter()"));

static thread_local std::mt19937 generator(time(nullptr)); // seed for tsRand()
int tsRand(const int min, const int max)                   // thread safe random generator
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
std::vector<bool> test_tsRand()
{
    std::vector<bool> unit_test_result_vec;

    int result;

    result = tsRand(0, 10);
    unit_test_result_vec.emplace_back((((result >= 0) && (result) <= 10)) ? true : false);

    result = tsRand(-1000, 0);
    unit_test_result_vec.emplace_back((((result >= -1000) && (result) <= 0)) ? true : false);

    result = tsRand(1, 1);
    unit_test_result_vec.emplace_back((((result >= 1) && (result) <= 1)) ? true : false);

    return unit_test_result_vec;
}
// debug(unitTest(&test_tsRand, "tsRand()"));

//}
#endif