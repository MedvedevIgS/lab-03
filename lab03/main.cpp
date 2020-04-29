#include <iostream>
#include <vector>
#include "histogram.h"
#include "SVG.h"

using namespace std;

vector<double> input_numbers(size_t count)
 {
 vector<double> result(count);
    cerr << "Enter numbers: ";
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
 return result;
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

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    if (number_count==0)
        return 1;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    if (bin_count==0)
        return 1;
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_count);
    return 0;
}
