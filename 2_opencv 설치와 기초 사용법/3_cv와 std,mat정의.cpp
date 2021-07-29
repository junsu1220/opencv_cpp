#include "opencv2/opencv.hpp"
#include <iostream>

// 다수의 opencv 함수와 Mat 클래스는 cv 네임스페이스로 선언되었기에
// 매번 함수의 앞에 cv::를 붙이면 힘드므로 
// using namespace cv, 같은이유로 std를 붙여 생략합니다.
using namespace cv;
using namespace std;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;
	// mat 클래스는 다양한 자료형의 행렬을 
	// 표현할 수 있는 범용 행렬 클래스
	// bmp파일에 저장된 영상을 화면에 출력하기 위해서는 
	// 일단 mat 객체를 생성하고, mat객체를 화면에 출력하는
	// opencv 함수를 호출하면 됩니다.
	Mat img;
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("image");
	imshow("image", img);

	waitKey();

	return 0;
}
