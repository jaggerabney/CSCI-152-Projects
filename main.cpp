#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "my_algorithms.h"

using namespace std;

static const int ITERATIONS = 10;

ofstream fout {"data.csv", ios::out};

void measureRuntime(int size) {
    fout << size << ",";
    
    vector<int> list = my::randomIntegers(0, size * 10, size);
    int target = my::generateRandomNumberBetween(0, size * 10);

    int find_if_comparisons = 0;
    int binary_search_comparisons = 0;

    auto find_if_predicate = [target, &find_if_comparisons](const int& value) {
        find_if_comparisons++;
        return (target == value);
    };
    auto binary_search_compare = [target, &binary_search_comparisons](const int& value) {
        binary_search_comparisons++;
        if (value < target) {
            return -1;
        } else if (value == target) {
            return 0;
        } else {
            return 1;
        }
    };

    auto cfi_runtime_us = my::averageRuntimeOf(my::find_if<vector<int>::const_iterator, function<bool(int)>>, list.begin(), list.end(), find_if_predicate);
    auto cfi_comparisons = find_if_comparisons / my::EXECUTIONS;

    fout << cfi_runtime_us << ",";
    fout << cfi_comparisons << ",";
    find_if_comparisons = 0;

    auto sfi_runtime_ms = my::averageRuntimeOf(std::find_if<vector<int>::const_iterator, function<bool(int)>>, list.begin(), list.end(), find_if_predicate);
    auto sfi_comparisons = find_if_comparisons / my::EXECUTIONS;

    fout << sfi_runtime_ms << ",";
    fout << sfi_comparisons << ",";
    find_if_comparisons = 0;

    sort(list.begin(), list.end());

    auto cbs_runtime_us = my::averageRuntimeOf(my::binary_search_if<vector<int>::const_iterator, function<int(int)>>, list.begin(), list.end(), binary_search_compare);
    auto cbs_comparisons = binary_search_comparisons / my::EXECUTIONS;

    fout << cbs_runtime_us << ",";
    fout << cbs_comparisons << ",";
    binary_search_comparisons = 0;

    // the std binary search necessitated its own compare function because things can't be easy, i guess
    int std_binary_search_comparisons = 0;
    auto sbs_runtime_us = my::averageRuntimeOf(std::binary_search<vector<int>::const_iterator, int, function<int(int, int)>>,
        list.begin(), list.end(), target, [&std_binary_search_comparisons](const int& value1, const int& value2) {
            // i think this is right?
            std_binary_search_comparisons++;
            return (value1 == value2);
        });
    fout << sbs_runtime_us << ",";
    fout << std_binary_search_comparisons / my::EXECUTIONS << "\n";
}


int main() {
    fout << "Size,MyFindTime,MyFindIter,StdFindTime,StdFindIter,MyBinTime,MyBinIter,StdBinTime,StdBinIter\n";
    for (int i = 1000; i <= 1000000; i += 1000) {
        cout << i << "\n";
        measureRuntime(i);
    }
}
