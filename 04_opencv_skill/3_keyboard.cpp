#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	// 그레이로 불러서 img에 저장
	Mat img = imread("lenna.bmp");
	//예외처리
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");
	imshow("img", img);
	// 반복
	while (true) {
		// WaitKey()함수의 반환값을 keycode 변수를 저장합니다.
		int keycode = waitKey();
		// i,I 누르면 영상이 반전
		if (keycode == 'i' || keycode == 'I') {
			img = ~img;
			imshow("img", img);
		}
		// esc,q,Q 누르면 반복문 빠져나감
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
			break;
		}
	}

	return 0;
}
