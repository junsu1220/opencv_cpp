#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img; 	// main과 on_mouse에서의 영상 img 선언
Point ptOld;	//on_mouse에서 이전 마우스 이벤트 발생위치 저장위한 변수선언
// 총 4개의 정수형 인자와 한개의 void*타입을 받으며 void*는 사용자데이터의 포인터입니다.
// 첫번째 정수형인자는 type으로 움직이는 경우나,누른경우,떼는경우등의 이벤트타입을 설정합니다.
// 2,3번째 인자는 마우스 이벤트가 발생한 위치의 x,y좌표가 전달됩니다.
// 4번째 플래그는 flag의 열거형상수(특정 버튼 눌려있음)전달됩니다.
void on_mouse(int event, int x, int y, int flags, void*);

int main(void)
{
	img = imread("lenna.bmp");
	// 예외처리
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// setMouseCallBack()이전 마우스 이벤트 받을 창 미리생성 되어있어야합니다.
	namedWindow("img");
	// 셋마우스콜백함수는 미리 생성된 winname창에서 마우스 이벤트가 발생하면
	// 온마우스로 등록된 콜백함수(on_mouse)가 자동으로 호출되도록 설정합니다.
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey();

	return 0;
}
// 마우스 이벤트를 처리하는 함수
void on_mouse(int event, int x, int y, int flags, void*)
{
	// 스위치 써서 다양한 마우스 이벤트를 처리합니다.
	switch (event) {
	case EVENT_LBUTTONDOWN: 	//왼쪽버튼 눌렀을때 
		ptOld = Point(x, y); 	//눌렸을때의 좌표를 pt0ld에 저장
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl; 	//좌표 출력
		break;
	case EVENT_LBUTTONUP:		//왼쪽버튼 땠을때
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl; 	//해당 좌표 출력
		break;
	case EVENT_MOUSEMOVE:	//마우스가 움직이는 경우 이벤트처리구문
		// flags인자에 왼쪽버튼 눌려있음이 설정되어있으면 line()이용해서 
		// img영상에 노란색 마우스 궤적을 그립니다.
		if (flags & EVENT_FLAG_LBUTTON) {		
			// 사용자가 왼쪽버틑 누른 상태에서 움직이면 실행되는 코드 블록
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}
