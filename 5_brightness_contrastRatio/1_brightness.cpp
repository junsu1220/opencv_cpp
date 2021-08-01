#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void* userdata);

int main(void)
{
	brightness1();
	brightness2();
	brightness3();
	brightness4();

	return 0;
}
// 영상의 밝기를 100만큼 증가
void brightness1()
{
    // 레나영상을 그레이스케일로 불러와 src에 저장합니다.
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
    // 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // src영상의 모든픽셀값을 100만큼 증가시킨 결과 영상을 dst에 저장합니다.
    // 연산자 재정의가 되어 있습니다. 포화연산까지 수행합니다.
    // 어둡게 하려면 -100 하면됩니다, 자기 자신이 밝아지려면 +=.
	Mat dst = src + 100;
    // src와 dst 영상을 각각 새창에 출력하고 키입력까지 기다립니다.
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
    //영상출력창을 닫습니다.
	destroyAllWindows();
}
// 포화 연산을 고려하지 않은 영상의 밝기 증가 직접 구현
void brightness2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 입력 영상 src와 크기, 타입이 같은 결과 영상 dst를 생성합니다.
	Mat dst(src.rows, src.cols, src.type());
    // 영상전체를 스캔하면서 입력영상의 픽셀값에
    // 100을 더하여 결과 영상 픽셀값으로 설정합니다.
    // 앞에서 배운 at을 응용합니다.
    // j가 y축좌표이고 i가 x축좌표입니다.
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
			// int v = src.at<uchar>(j, i) + 100;
			// dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
			// 60라인 대신에 61,62라인을 쓰면 포화연산의 문제점을 해결할 수 있습니다.
		}
	}
    // 밝은 픽셀 주변에서 급격하게 어두운픽셀이 나타나는 것은
    // 포화연산을 수행하지 않았기 때문입니다.
	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}
// 포화연산을 고려한 영상의 밝기 증가 직접 구형
void brightness3()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
		    // 밝기 조절된 픽셀값에 saturate_cast() 함수를 이용하여
		    // 포화연산을 수행한후 결과 영상 값으로 설정합니다.
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
	// 새로운 기능을 직접 구현해야하는 경우가 발생하기 때문에
	// 영상의 픽셀값을 직접 참조하고 변경하는 방법은 반드시 기억하고 있어야합니다.
}

void brightness4()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 결과 영상을 출력하고 트랙바를 부착할 dst창을 미리 생성합니다.
	namedWindow("dst");
	// dst 창에 트랙바를 부착하고 트랙바로 조절할 콜백함수를 등록합니다.
	// 입력 영상 src의 주소를 트랙바 콜백함수의 사용자 데이터로 설정합니다.
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	// dst창에 레나영상이 정상적으로 표시되게
	// 강제로 on_brightness() 함수를 호출합니다.
	// 이 호출이 없으면 트랙바를 움직여야 레나영상이 나옵니다.
	on_brightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}
// 트랙바 콜백 함수에서 밝기 조절된 결과 영상 dst를 화면에 출력합니다.
void on_brightness(int pos, void* userdata)
{
    // 트랙바에서 src가 userdata와
    // pos로 조절됩니다.
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}
