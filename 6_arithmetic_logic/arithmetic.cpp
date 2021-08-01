#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	// 영상의 산술연산입력으로 사용할 영상을 그레이스케일로 불러와 src1,2에 저장합니다.
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	//예외처리
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;
	// src1과 src2영상을 이용하여 덧셈, 평균,
	// 뺄셈, 차이 연산을 수행하고 그 결과를 각각 dst1,2,3,4 변수에 저장합니다.
	add(src1, src2, dst1);
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
	subtract(src1, src2, dst3);
	absdiff(src1, src2, dst4);
	// 연산결과를 각각 새창에 나타냅니다.
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}
