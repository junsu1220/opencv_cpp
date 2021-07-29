#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void PointOp();
void SizeOp();
void RectOp();
void RotatedRectOp();
void RangeOp();
void StringOp();

int main()
{
	PointOp();
	SizeOp();
	RectOp();
	RotatedRectOp();
	RangeOp();
	StringOp();

	return 0;
}
// 포인트 클래스는 2차원 평면위에 있는 점의 좌표를 표현하는 템플릿 클래스입니다.
// 클래스내부에 다양한 자료형으로 이름이 재정의 되어 있는데 
// 사용시 어떤 자료형으로 사용할 것인지를 명시해야합니다.
// 즉 2차원 정수 좌표계에서 좌표를 표현하는 자료형이라고 생각하면 좋습니다.
void PointOp()
{
	Point pt1;				// pt1 = (0, 0)
	pt1.x = 5; pt1.y = 10;	// pt1 = (5, 10)
	Point pt2(10, 30);		// pt2 = (10, 30)

	Point pt3 = pt1 + pt2;	// pt3 = [15, 40]
	Point pt4 = pt1 * 2;	// pt4 = [10, 20]

	// dot은 두 점의 내적을 계산하는 멤버함수입니다.
	// 두 점의 내적은 x좌표끼리 곱한 값에 y좌표끼리 곱한 값을 더합니다.
	int d1 = pt1.dot(pt2);	// d1 = 350
	bool b1 = (pt1 == pt2);	// b1 = false

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
}

// size클래스도 다양한 자료형으로 재정의 되어있으며
// size클래스는 정수형 멤버 변수 width, height를 가지고 있는 사각형
// 크기 표현 클래스입니다.
void SizeOp()
{
	// 2차원 정수 좌표계에서 크기를 표현
	Size sz1, sz2(10, 20);			// sz1 = [0 x 0], sz2 = [10 x 20]
	sz1.width = 5; sz1.height = 10;	// sz1 = [5 x 10]

	// 다양한 연산자에 대해 연산자 재정의가 되어있어
	// 사칙연산을 통해 크기를 조정할 수 있습니다.
	Size sz3 = sz1 + sz2;	// sz3 = [15 x 30]
	Size sz4 = sz1 * 2;		// sz4 = [10 x 20]
	int area1 = sz4.area();	// area1 = 200

	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;
}

// 사각형의 위치와 크기 정보를 표현할때 사용하는 클래스입니다.
// 사각형의 좌측상단 점의 좌표를 나타내는 x,y멤버 변수와 
// 사각형의 가로 및 세로 크기를 나타내는 width, height 멤버 변수를 가지고 있습니다. 
void RectOp()
{
	Rect rc1;					// rc1 = [0 x 0 from (0, 0)]
	Rect rc2(10, 10, 60, 40);	// rc2 = [60 x 40 from (10, 10)]

	Rect rc3 = rc1 + Size(50, 40);	// rc3 = [50 x 40 from (0, 0)]
	Rect rc4 = rc2 + Point(10, 10);	// rc4 = [60 x 40 from (20, 20)]

	// &는 두 사각형의 공통적인 사각형
	// |는 두 사각형을 포함하는 최소의 사각형
	Rect rc5 = rc3 & rc4;		// rc5 = [30 x 20 from (10, 10)]
	Rect rc6 = rc3 | rc4;		// rc6 = [80 x 60 from (0, 0)]

	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;
}

// 회전된 사각형을 표현하는 클래스입니다.
// 회전된 사각형의 중심좌표인 center
// 가로 및 세로 크기인 size
// 회전각도 정보인 angle
void RotatedRectOp()
{
	// 템플릿 클래스가 아니며 모든 정보는 float으로 표현합니다.
	// 중심이 40,30이며 가로 40 세로 20, 각도는 30도 오른쪽으로 돌았습니다.
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);
	// 회전된 사각형의 네 꼭지점 좌표가 PTS 배열에 저장됩니다.
	// RotatedRect::points()
	Point2f pts[4];
	rr1.points(pts);
	// 특정 객체를 감싸는 최소크기의 사각형을 바운딩 박스라하며 
	// 바운딩 박스를 구하려면 RotatedRect::boundingRect()함수를 사용합니다.
	Rect br = rr1.boundingRect();
}
// 범위 또는 구간을 표현하는 클래스
// 범위의 시작과 끝인 start변수와 end변수가 있습니다.
void RangeOp()
{
	Range r1(0, 10);
}
// string 클래스 문자열을 저장하고 처리한다
void StringOp()
{
	String str1 = "Hello";
	String str2 = "world";
	String str3 = str1 + " " + str2;	// str3 = "Hello world"

	bool ret = (str2 == "WORLD");
	
	Mat imgs[3];
	for (int i = 0; i < 3; i++) {
		// 특정한 형식의 문자열을 만들고 싶다면 format()함수를 사용한다.
		// 반환값으로는 지정한 형식으로 생성된 문자열이다.
		// 여기서는 bmp 입니다.
		String filename = format("data%02d.bmp", i + 1);
		cout << filename << endl;
		imgs[i] = imread(filename);
	}
}