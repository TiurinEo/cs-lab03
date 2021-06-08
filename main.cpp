#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
#include <sstream>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
vector<size_t>
make_histogram(vector<double> numbers,size_t bin_count){
double min,max;
find_minmax(numbers,min,max);
double bin_size= (max-min)/bin_count;
    double max_count=0;

vector<size_t> bins(bin_count);
size_t number_count=numbers.size();
    for (size_t i=0;i<number_count;i++){
        bool found = false;
    for (size_t j=0;(j<bin_count) && !found;j++){
            auto low=min+j*bin_size;
            auto hi=min+(1+j)*bin_size;
        if((numbers[i]>=low)&&(numbers[i]<hi)){
            bins[j]++;
            found=true;
           }
           if (bins[j]>max_count) max_count=bins[j];
        }
        if (!found) {
        bins[bin_count - 1]++;
    }
    }
    return bins;
}
void
show_histogram_text(vector<size_t> bins){

    size_t bin_count=bins.size();
    for (size_t i=0;i<bin_count;i++){
            if (bins[i]<100)
            cout<<" ";
    if (bins[i]<10)
        cout<<" ";
    cout<<bins[i]<<"|";
        for (size_t j=0;j<bins[i];j++)
cout<<"*";
            cout<<endl;
    }


}
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


    buffer<<"Version "<<version_minor<<"."<<version_major<<" (build "<<platform<<")"<<endl;

    char buff[MAX_COMPUTERNAME_LENGTH+1];
	DWORD size;
	size=sizeof(buff);
	GetComputerName(buff,&size);
    buffer<<buff;

    }
    else cout<<"net"<<endl;
    return buffer.str();
}

int main()
{


    size_t number_count, bin_count;
    cerr<<"Enter number count:";
    cin>>number_count;
    const auto numbers = input_numbers(number_count);
    cerr<<"Enter bin count:";
    cin>>bin_count;
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
    return 0;
}
