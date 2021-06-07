#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double>
input_numbers(istream& in, size_t count) {

    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in,bool prompt) {
    Input data;
    if(prompt) cout<<"HELP"<<endl;
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr<<"Enter bin count:";
    in>>data.bin_count;

    return data;
}
vector<size_t>
make_histogram(Input a){
double min,max;
find_minmax(a.numbers,min,max);
double bin_size= (max-min)/a.bin_count;
    double max_count=0;

vector<size_t> bins(a.bin_count);
size_t number_count=a.numbers.size();
    for (size_t i=0;i<number_count;i++){
        bool found = false;
    for (size_t j=0;(j<a.bin_count) && !found;j++){
            auto low=min+j*bin_size;
            auto hi=min+(1+j)*bin_size;
        if((a.numbers[i]>=low)&&(a.numbers[i]<hi)){
            bins[j]++;
            found=true;
           }
           if (bins[j]>max_count) max_count=bins[j];
        }
        if (!found) {
        bins[a.bin_count - 1]++;
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


int main(int argc, char* argv[])
{
    if (argc>1){
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
if(curl) {
  CURLcode res;
  curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}
    }
    const auto input = read_input(cin,true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
}
