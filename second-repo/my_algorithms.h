#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

namespace my {
    static const int EXECUTIONS = 5;

    // takes a beginning and end iterator, as well as a callback function (predicate)
    // in its current implementation, a value passed to the predicate is compared to an internal comparator
    // as specified in the passed lambda function - something like [comparator = n](const int& value) { return (value == comparator)}
    template <typename iteratorType, typename predicate>
    iteratorType find_if(iteratorType it, iteratorType end, predicate pred) {
        for (; it != end; it++) {
            if (pred(*it)) {
                return it;
            }
        }
        return end;
    }

    // I don't know what a predicate that can return multiple values is called
    // Maybe just a evaluator or something? Please let me know, my Google-fu has failed me
    template <typename iteratorType, typename multiPredicate>
    iteratorType binary_search_if(iteratorType begin, iteratorType end, multiPredicate multiPred) {
        auto notFound = end;
        while (distance(begin, end) > 0) {
            auto midpoint = begin;
            advance(midpoint, distance(begin, end) / 2);
            auto result = multiPred(*midpoint);
            if (result == 0) {
                return midpoint;
            } else if (result < 0) {
                begin = midpoint;
                begin++;
            } else {
                end = midpoint;
            }
        }
        return notFound;
    }

    vector<int> randomIntegers(int lowerBound, int upperBound, int size);

    int generateRandomNumberBetween(int lowerBound, int upperBound);

    template <typename callbackFunction, typename... arguments>
    chrono::duration<_int64, micro> runtimeOf(callbackFunction&& function, arguments&&... args) {
        auto start = chrono::steady_clock::now();
        forward<decltype(function)>(function)(forward<decltype(args)>(args)...);
        auto end = chrono::steady_clock::now();
        auto timeElapsed = chrono::duration_cast<chrono::microseconds>(end - start);
        return timeElapsed;
    }

    template <typename callbackFunction, typename... arguments>
    double averageRuntimeOf(callbackFunction&& function, arguments&&... args) {
       double sum = 0.0;
       for (int i = 0; i < EXECUTIONS; i++) {
            auto runtime = runtimeOf(function, args...).count();
            sum += runtime;
       }
       return sum / EXECUTIONS;
    }
}