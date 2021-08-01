#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	// 영상의 비트 단위 논리 연산 입력으로 사용할 영상을
	// 그레이스케일로 불러와 src1,2에 Mat형식으로 저장
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	// 예외처리
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	
	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;
	// 논리곱,합,배타적논리합,부정 을 구하고 그 결과를 src1,2,3,4에 저장합니다.
	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);
	// 결과 영상을 새 창으로 나타내고 키입력있으면 프로그램 종료합니다.
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}
