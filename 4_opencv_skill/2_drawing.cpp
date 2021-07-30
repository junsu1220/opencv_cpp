#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawLines();
void drawPolys();
void drawText1();
void drawText2();
// 영상의특징을 분석해서 정보를 추출할때
// 영상 출력 창위에 바로 정보를 표현하기 위해 지금 파트를 배웁니다.
int main(void)
{
	drawLines();
	drawPolys();
	drawText1();
	drawText2();

	return 0;
}

void drawLines()
{
	// 400*400 크기의 3채널 컬러 영상을 생성합니다. 모든픽셀은 흰색입니다.(도화지역할)
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	// (그려지는 영상, 시작점, 끝점, 선색상, 선 두께, 선타입(선이 조금 더 선명해지거나 함))
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);
	// (화살표를 그립니다, 마지막은 전체직선길이에 대한 화살표길이의 비율입니다)
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);
	// 다양한 모양의 마커를 그립니다. 마지막 인자가 마커 모양입니다.
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);	//십자가
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);	//45도 회전 십자가
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);	//십자가와 45십자가 합친거
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);	//마름모
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);		//정사각형
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);	//위로뾰족삼각형
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);	//아래뾰족삼각형

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}
// 이번에는 도형을 그립니다.
void drawPolys()
{
	// 400*400영상 생성(도화지)
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	// 사각형(입출력영상, pt1,2로 대각점도 가능하고 Rect로 사각형 표현해도가능, 사각형 색상,
	// 사각형 외곽선 두께 음수면 내부를 채웁니다, 선타입, 좌표값의 축소 비율)
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);
	// 원(입출력영상, 원의 중심, 원의 반지름, 원의 색상, 원외곽선두께 -면 내부채웁니다, 선타입, 축소비율)
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);
	// 타원(입출력영상, 타원중심, 타원반지름(x축,y축), 타원회전각도,
	// 호의 시작각도(x축기준,시계방향), 호의 끝각도(x축기준,시계방향)
	// 타원 색상, 외곽선 두께 -면 채움, 선타입, 축소비율)
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	// 임의의 다각형 그립니다.
	// 다각형은 vector<Point> 자료형에 저장하여 전달합니다.
	// 자료형 선언
	vector<Point> pts;
	// 총 6개의 꼭지점 지정
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	// 다각형(입출력영상, 미리만든포인트, 트루면 열려있는 다각형 폴스면 닫혀있음, 선색상, 선두께 -면 채움)
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}
// 영상에 직접 문자열을 출력합니다.
void drawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));
	// (입출력영상, 출력할 문자열, 문자열을 출력할 위치의 좌측하단좌표,
	// 폰트종류, 폰트크기확대축소비율, 색상, 선두께, 선타입)
	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void drawText2()
{
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));
	
	const String text = "Hello, OpenCV";	//출력문자열
	int fontFace = FONT_HERSHEY_TRIPLEX;	//폰트종류
	double fontScale = 2.0;		//크기비율
	int thickness = 1;		//선두께

	// 출력할 문자열의 사각형 크기 sizeText에 저장
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	// 출력할 대상영상의 크기를 sizeImg에 저장
	Size sizeImg = img.size();
	
	// Text와 Img를 이용해 문자열을 출력할 좌표를 계산
	// org는 사각형 좌측 하단 좌표를 계산하였습니다.
	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	// 위에서의 org포인트를 이용해서 중앙에 문자열 표시
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(0, 255, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
	// 그리기함수는 영상의 픽셀값을 변경시키므로 원본영상의 픽셀값은 복구못합니다.
	// 원본을 백업하려면 Mat::clone() 또는 Mat::copyTo()함수를 사용해야 합니다.
}