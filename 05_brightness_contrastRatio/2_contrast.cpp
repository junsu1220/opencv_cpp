#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contrast1();
void contrast2();

int main(void)
{
	contrast1();
	contrast2();

	return 0;
}

void contrast1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 입력 영상 src의 모든 픽셀값에 2.0을 곱하여
    // 결과 영상 dst를 생성합니다.
    // 연산자 재정의이므로 포화연산도 적용됩니다.
	float s = 2.f;
	Mat dst = s * src;
    // 픽셀값이 포화되어 흰색으로 나타나는 영역이 매우많습니다.
    // 따라서 단순히 일정상수를 곱하는 것은 실전에서 잘 사용되지 않습니다.
	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void contrast2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 알파가 -1에서 0사이이면 명암비 감소
    // 알파가 0보다 크면 명암비를 증가시킵니다.
    // 명암비증가에서는 128보다 크면 더욱밝게 128보다 작으면 더욱 어둡게 합니다.
    // 명암비감소에서는 128보다 크면 픽셀값을 작게 , 128보다 작으면 픽셀값을 128에 가깝게 증가시킵니다.
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;
    // 중간 픽셀값이 많으므로 포화연산의 영향은 실제로 잘 받지 않습니다.
	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}
