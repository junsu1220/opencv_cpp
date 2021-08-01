#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histogram_stretching();
void histogram_equalization();

int main(void)
{
	histogram_stretching();
	histogram_equalization();

	return 0;
}

Mat calcGrayHist(const Mat& img)
{
    // CV_Assert 함수를 이용 그레이스케일영상인지 검사합니다.
	CV_Assert(img.type() == CV_8UC1);
    // calcHist 함수에 전달할 인자를 생성하는 구문입니다.
    // 히스토그램 정보를 저장할 Mat타입 변수 hist를 선언합니다.
	Mat hist;
	// 히스토그램 구할 채널번호를 담은 채널배열을 생성합니다.
	// 그레이 영상은 한개의 채널이므로 0부터시작, 0하나입니다.
	int channels[] = { 0 };
	// 1차원 행렬이므로 1입니다. dimension
	int dims = 1;
	// 256은 채널 값의 범위를 256 빈으로 나누어 구하겠다는 의미입니다.
	const int histSize[] = { 256 };
	// 최솟값과 최댓값인 0,256을 적습니다.
	float graylevel[] = { 0, 256 };
	// ranges는 위에서의 graylevel 배열이름을 갖는 배열입니다.
	const float* ranges[] = { graylevel };
    // calcHist()룰 써서 img영상의 히스토그램을 구하고 결과를 hist변수에 저장합니다.
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
    // hist 변환
	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void histogram_equalization()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
