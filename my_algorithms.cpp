#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include "my_algorithms.h"

using namespace std;

namespace my {
    vector<int>::const_iterator binary_search(vector<int>::const_iterator begin, vector<int>::const_iterator end, int item) {
        vector<int>::const_iterator notFound = end;
        while (distance(begin, end) > 0) {
            auto midpoint = begin;
            advance(midpoint, distance(begin, end) / 2);
            if (*midpoint == item) {
                return midpoint;
            }
            else if (*midpoint < item) {
                begin = midpoint;
                begin++;
            }
            else {
                end = midpoint;
            }
        }
        return notFound;
    }

    vector<int> randomIntegers(int lowerBound, int upperBound, int size) {
        mt19937 engine{random_device{}()};
        uniform_int_distribution<int> range{lowerBound, upperBound};

        vector<int> integers;
        for (int i = 0; i < size; i++) {
            integers.push_back(range(engine));
        }

        return integers;
    }

    int generateRandomNumberBetween(int lowerBound, int upperBound) {
        mt19937 engine{random_device{}()};
        uniform_int_distribution<int> range{lowerBound, upperBound};
        return range(engine);
    }
}