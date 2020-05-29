#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

void svg_line(double x_1, double y_1, double x_2, double y_2, size_t width);

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

void svg_text(double left, double baseline, string text);

void svg_begin(double width, double height);

void svg_end();

void show_histogram_svg(const vector<size_t>& bins, size_t bin_count);

#endif // SVG_H_INCLUDED
