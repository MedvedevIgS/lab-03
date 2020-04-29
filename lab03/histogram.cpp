#include "histogram.h"
#include <vector>

using namespace std;

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

void find_minmax(vector<double> numbers, double& min, double& max)
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
