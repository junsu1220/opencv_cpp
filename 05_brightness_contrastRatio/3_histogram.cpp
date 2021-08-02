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
	// hist 는 CV_32FC1타입을 갖는 256*1크기의 행렬
	return hist;
}
// calc에서 구한 hist를 막대그래프 형태로 나타내는 함수
// 최대빈도수를 표현하는 막대그래프길이가 100픽셀이 되도록 그래프를 그림
Mat getGrayHistImage(const Mat& hist)
{
	// hist행렬이 CV_32FC1인지 256개의 빈인지 체크합니다.
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	// hist행렬 원소의 최댓값을 histMax변수에 저장합니다.
	double histMax;
	minMaxLoc(hist, 0, &histMax);
	// 흰색으로 초기화된 256*100크기의 새 영상 imgHist를 생성합니다.
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	// for과 line()을 이용하여 각각의 빈에 대한 히스토그램 그래프를 그립니다.
	for (int i = 0; i < 256; i++) {
		// 최댓값을 100픽셀으로 설정하고 나머지 막대그래프는 100픽셀보다 짧은길이의 직선이 됩니다.
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}
	// hist행렬로투터 구한 256*100 크기의 히스토그램 영상 imgHist를 반환합니다.
	return imgHist;
}

void histogram_stretching()
{
	// hawkes.bmp파일을 그레이스케일 형식으로 불러와서 Mat형식 src에 저장합니다.
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 입력 영상 src에서 그레이스케일 최솟값과 최댓값을 구하여 gmin과 gmax에 저장합니다.
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	// 히스토그램 수식을 그대로 적용하여 결과 영상 dst를 생성합니다.
	Mat dst = (src - gmin) * 255 / (gmax - gmin);
	// 입력 영상과 히스토그램 스트레칭 결과영상, 그리고 각각의 히스토그램을 화면에 출력합니다.
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void histogram_equalization()
{
	// hawkes.bmp를 그레이스케일 형태로 불러와서 src에 저장합니다.
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 히스토그램 평활화를 수행한 결과를 dst에 저장합니다.
	Mat dst;
	equalizeHist(src, dst);
	// 입력영상과 히스토그램 평활화 결과 영상, 그리고 각각의 히스토그램을 화면에 출력합니다.
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
