#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void VecOp();
void ScalarOp();

int main(void)
{
	VecOp();
	ScalarOp();

	return 0;
}
// 작은 개수의 원소로 구성된 벡터를 표현하는 vec 템플릿 클래스
void VecOp()
{
	// Vec'3''b'에서 '3'은 채널수 다시 말해 정수형 데이터를 몇개 가지고 있는가 이고
	// 'b'는 자료형을 의미하며 여기서는 uchar입니다.
	// p1은 p1.val배열원소가 모두 0으로 초기화되었고
	// p2는 p2.val[0]==0, p2.val[1]==0, p2.val[2]==255 입니다.
	Vec3b p1, p2(0, 0, 255);
	// 이후 p1의 첫번째 원소를 100으로 바꿉니다.
	p1[0] = 100;
	cout << "p1: " << p1 << endl;	//p1: [100, 0, 0]
	cout << "p2: " << p2 << endl;	//p2: [0, 0, 255]
}
// mat다음으로 자주 사용되는 클래스인 scalar입니다.
// scalar는 4채널이하의 영상에서 픽셀값을 표현하는 용도로 자주 사용됩니다.
void ScalarOp()
{
	// scalar클래스 타입의 변수에 128로 초기화 [128, 0, 0, 0]
	Scalar gray = 128;
	cout << "gray: " << gray << endl;
	// 초기화 [0, 255, 255, 0]
	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl;
	// yellow 변수를 mat 클래스 생성자의 네번째 인자로 전달하여,
	// 노란색으로 초기화된 256*256크기의 컬러 영상 img1을 생성합니다.
	Mat img1(256, 256, CV_8UC3, yellow);

	// 연산자 재정의를 사용해 yellow[]에 접근합니다.
	for (int i = 0; i < 4; i++)
		cout << yellow.val[i] << ", " << yellow[i] << endl;
}
