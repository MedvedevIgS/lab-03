#include <iostream>
#include <vector>
#include "histogram.h"
#include "SVG.h"

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double> input_numbers(istream& in, size_t count)
 {
 vector<double> result(count);
    cerr << "Enter numbers: ";
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
 return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter column count: ";
    cin >> data.bin_count;

    return data;
}

void show_histogram_text(vector<size_t> bins)
{
  const size_t SCREEN_WIDTH = 80;
  const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
  size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
    return;
}

vector<size_t> make_histogram(vector<double> numbers, size_t bin_count)
{
    vector<size_t> bins(bin_count);
    double max, min;
    find_minmax(numbers, min, max);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}


int main()
{
    const auto data = read_input(cin);
    const auto bins = make_histogram(data.numbers, data.bin_count);
    show_histogram_svg(bins, data.bin_count);
    return 0;
}
