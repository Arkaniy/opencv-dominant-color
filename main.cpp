#include "opencv2/opencv.hpp"
#include <iomanip>
#include <iostream>

using namespace cv;

unsigned long createRGB(char r, char g, char b) {
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int main(int argc, char *argv[]) {
    Mat img;
    if(argc != 2 || !(img=imread(argv[1], 1)).data)
        return -1;

    int hbins = 90;
    int channels[] = {0};
    int histSize[] = {hbins};
    float hranges[] = { 0, 180 };
    const float* ranges[] = { hranges };

    MatND hist;
    cvtColor(img, img, CV_BGR2HSV);
    calcHist( &img, 1, channels,  Mat(), hist, 1, histSize, ranges, true, false );
    normalize(hist, hist, 0, 255, CV_MINMAX);

    Mat buf(1, hbins, CV_8UC3);
    for( int i = 0; i <  hbins; i++) {
        buf.at< Vec3b>(i) = Vec3b(saturate_cast< uchar>(i*180./hbins), 255, 255);
    }
    cvtColor(buf, buf, CV_HSV2BGR);

    char maxR = 0, maxG = 0, maxB = 0, maxV = 0;

    for( int i = 0; i <  hbins; i++ ) {
        int val = saturate_cast<int>(hist.at< float>(i)*hbins/255);
        if (val > maxV) {
            maxV = val;
            maxR = buf.at< Vec3b>(i)[2];
            maxG = buf.at< Vec3b>(i)[1];
            maxB = buf.at< Vec3b>(i)[0];
        }
    }

    std::cout << "RGB: " << maxR << ' ' << maxG << ' ' << maxB << '\n';
    std::cout << "#" << std::hex << std::setw(6) << std::setfill('0') << createRGB(maxR, maxG, maxB) << '\n';
}
