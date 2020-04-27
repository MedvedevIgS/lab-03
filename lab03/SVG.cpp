#include "SVG.h"
#include <iostream>
#include <vector>

using namespace std;

void svg_line(double x_1, double y_1, double x_2, double y_2, size_t width)
{
 cout << "<line x1='"<<x_1<<"' y1='"<<y_1<<"' x2='"<<x_2<<"' y2='"<<y_2<<"' style='stroke-dasharray: 10 10' stroke='blue' stroke-width='"<<width<<"'/>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
 cout << "<rect x='"<< x << "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<< stroke <<"' fill='"<<fill<<"'/>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<< baseline <<"'>"<<text<<"</text>\n";
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins, size_t bin_count)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto INDENT = 5;
    const auto WIDTH_LINE = 3;
    size_t maxbin=bins[0];
    for(size_t j:bins)
        if(maxbin<j)
            maxbin=j;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double x1, x2, y1, y2;
    x1=1;
    y1=1;
    double koeff;
    if(((IMAGE_WIDTH-x1-WIDTH_LINE-TEXT_WIDTH-INDENT-WIDTH_LINE-WIDTH_LINE)/BLOCK_WIDTH)<maxbin)
        koeff=(IMAGE_WIDTH-x1-WIDTH_LINE-TEXT_WIDTH-INDENT-WIDTH_LINE-WIDTH_LINE)/maxbin;
    else
        koeff=BLOCK_WIDTH;
    x2=x1+WIDTH_LINE+TEXT_WIDTH+koeff*maxbin+INDENT+WIDTH_LINE;
    y2=y1+WIDTH_LINE+INDENT+BIN_HEIGHT*bin_count+INDENT+WIDTH_LINE;
    double top = y1+WIDTH_LINE+INDENT;
    for (size_t bin : bins)
    {
    const double bin_width = koeff * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
    top += BIN_HEIGHT;
    }
    svg_end();
}
