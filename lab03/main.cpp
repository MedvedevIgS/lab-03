#include <iostream>
#include <vector>

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

void find_minmax(vector<double>& numbers, double& min, double& max)
{
  min = numbers[0];
  max = numbers[0];
    for (double number : numbers)
 {
        if (number < min)
        {
            min = number;
        }
        if (number > max)
        {
            max = number;
        }
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
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count);
    return 0;
}
