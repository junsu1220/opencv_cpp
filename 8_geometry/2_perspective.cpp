#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
// 입력 영상을 저장할 변수 src를 Mat형식으로 전역변수로 선언합니다.
Mat src;
// 입력과 출력에서의 네 점 좌표를 저장할 배열을 선언합니다.
Point2f srcPts[4], dstPts[4];

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	src = imread("card.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// src창을 미리 생성한후 src창에 마우스 콜백함수를 등록합니다.
	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	// cnt는 마우스 왼쪽 버튼이 눌린 횟수를 저장하는 변수입니다.
	static int cnt = 0;
	//마우스 이벤트중 왼쪽버튼이 눌리는 이벤트에만 처리합니다.
	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			// src창에서 왼쪽버튼 눌린좌표를 srcQuad배열에 저장합니다.
			// 좌측상단부터 시계방향으로 클릭해야합니다.(그렇게 코딩했음)
			// cnt 1 추가합니다.
			srcPts[cnt++] = Point2f(x, y);
			// 왼쪽버튼 눌린위치에 반지름 5인 빨간색 원을 그립니다.
			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("src", src);
			// 4번 눌리면 if문 수행합니다.
			if (cnt == 4) {
				// 투시 변환하여 만들 결과 영상의 가로와 세로 크기를 w와 h변수에 저장합니다.
				int w = 200, h = 300;
				// src창에서 선택한 4꼭지점이 이동할 결과영상좌표를 설정합니다.
				dstPts[0] = Point2f(0, 0);
				dstPts[1] = Point2f(w - 1, 0);
				dstPts[2] = Point2f(w - 1, h - 1);
				dstPts[3] = Point2f(0, h - 1);

				// 3*3 투시변환행렬을 pers 변수에 저장합니다.
				Mat pers = getPerspectiveTransform(srcPts, dstPts);
				// 투시변환을 수행하여 w*h크기의 결과 영상 dst를 생성합니다.
				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));

				imshow("dst", dst);
			}
		}
	}
}