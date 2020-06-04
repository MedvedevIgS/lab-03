#include "SVG.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

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

string info_text ()
{
    stringstream buff;
    DWORD info=GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    //printf("version %u\n",version);
    DWORD mask_minor = 0x000000ff;
    DWORD mask_major = 0x0000ff00;
    DWORD platform = info >> 16;
    DWORD version_minor = info & mask_minor;
    DWORD version_major = info & mask_major;
    DWORD version_major16 = version_major >> 8;
    if ((info & 0b10000000'00000000'0000000'00000000) == 0)
        {
            DWORD build = platform;
            buff<<"Windows v"<<version_minor<<"."<<version_major16<<" (build "<<build<<")   ";
            //printf("build %u.\n", build);
        }
    char system[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system);
    GetComputerNameA(system, &Size);
    buff<<"Computer name: "<<system<<"\n";
    return buff.str();
}

void show_histogram_svg(const vector<size_t>& bins, size_t bin_count)
{
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 5;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 40;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 20;
    const auto INDENT = 5;
    const auto WIDTH_LINE = 3;
    size_t maxbin=bins[0];
    for(size_t j:bins)
        if(maxbin<j)
            maxbin=j;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double x1, x2, y1, y2;
    x1=5;
    y1=5;
    double koeff;
    if(((IMAGE_WIDTH-x1-WIDTH_LINE-TEXT_WIDTH-INDENT-WIDTH_LINE-WIDTH_LINE)/BLOCK_WIDTH)<maxbin)
        koeff=(IMAGE_WIDTH-x1-WIDTH_LINE-TEXT_WIDTH-INDENT-WIDTH_LINE-WIDTH_LINE)/maxbin;
    else
        koeff=BLOCK_WIDTH;
    x2=x1+WIDTH_LINE+TEXT_WIDTH+koeff*maxbin+INDENT+WIDTH_LINE;
    y2=y1+WIDTH_LINE+INDENT+BIN_HEIGHT*bin_count+INDENT+WIDTH_LINE;
    double top = y1+WIDTH_LINE+INDENT;
    svg_line(x1,y1,x2,y1, WIDTH_LINE);
    svg_line(x1,y2,x2,y2, WIDTH_LINE);
    svg_line(x1,y1,x1,y2, WIDTH_LINE);
    svg_line(x2,y1,x2,y2, WIDTH_LINE);
    for (size_t bin : bins)
    {
    const double bin_width = koeff * bin;
    svg_text(x1+WIDTH_LINE+TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(x1+WIDTH_LINE+TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
    top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT,top+BIN_HEIGHT,info_text());
    svg_end();
}
