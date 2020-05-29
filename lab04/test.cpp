#include "histogram.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_make_histogram_empty ()
{
    size_t bin_count = 10;
    auto bin = make_histogram ({}, bin_count);
    assert(bin[0] > 0);
}

void test_make_histogram_ones ()
{
    size_t bin_count = 3;
    auto bin = make_histogram ({1}, bin_count);
    assert(bin[0] > 0);
}

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_otricala()
{
    double min=0;
    double max=0;
    find_minmax({-1,-2,-3},min,max);
    assert(max == -1);
    assert(min == -3);
}
void test_same()
{
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void test_ones()
{
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void test_empty ()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

int main()
{
    test_positive();
    test_ones();
    test_same();
    test_empty();
}
