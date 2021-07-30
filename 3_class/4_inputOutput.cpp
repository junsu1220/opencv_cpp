#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void InputArrayOp();
void printMat(InputArray _mat);

int main(void)
{
	InputArrayOp();

	return 0;
}
// InputArray와 OutputArray는 주로 함수의 입출력으로 사용됩니다.
void InputArrayOp()
{
	// data1 배열값을 원소로 갖는 2*3 행렬 mat1을 생성합니다.
	uchar data1[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat1(2, 3, CV_8UC1, data1);
	// _mat으로보내 출력
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}

void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat();
	cout << mat << endl;
}
