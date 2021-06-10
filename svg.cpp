#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
#include <sstream>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
string make_info_text(){

stringstream buffer;
DWORD mask = 0x0000ffff;
    DWORD info=GetVersion();
    if ((info & 0xa000) == 0) {


    DWORD version = info & mask;

    DWORD platform = info >> 16;

    DWORD mask_minor=0x00ff;
    DWORD version_minor=version & mask_minor;
    DWORD version_major=version >>8;


    buffer<<"Version "<<version_minor<<"."<<version_major<<" (build "<<platform<<")";

    char buff[MAX_COMPUTERNAME_LENGTH+1];
	DWORD size;
	size=sizeof(buff);
	GetComputerName(buff,&size);
    buffer<<buff;

    }
    else cout<<"net"<<endl;
    return buffer.str();
}



void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" <<baseline<< "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "red"){
    cout << "<rect x='" << x << "' y='" <<y<< "' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"'></rect>";
}


void
show_histogram_svg(const vector<size_t>& bins){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    double top = 0;
    size_t max_count = bins[0]; //поиск max из корзин
    for (size_t bin : bins)
        if (bin > max_count)
            max_count = bin;

    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        top += BIN_HEIGHT;
    }

    top=0;
    if (max_count > MAX_ASTERISK ){
        for(size_t bin : bins){
            const double bin_width = static_cast <double> (IMAGE_WIDTH - TEXT_LEFT)/max_count * bin;
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top+=BIN_HEIGHT;
        }
    }
    else{
        for(size_t bin : bins){
            const double bin_width = BLOCK_WIDTH * bin;
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top+=BIN_HEIGHT;

        }
    }

svg_text(TEXT_LEFT,top+BIN_HEIGHT,make_info_text());
    svg_end();
}
