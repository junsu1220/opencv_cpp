#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void hough_lines();
void hough_line_segments();
void hough_circles();

int main(void)
{
	hough_lines();
	hough_line_segments();
	hough_circles();

	return 0;
}

void hough_lines()
{
	// building.jpg영상을 그레이스케일형식으로 불러와 Mat형식으로 src에 저장합니다.
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 케니 에지 검출기를 이용하여 구한 에지 영상을 edge에 저장합니다.
	Mat edge;
	Canny(src, edge, 50, 150);
	// HoughLines() 함수를 이용하여 직선의 방정식 파라미터 rho와 theta정보를
	// line에 저장합니다. 축적배열은 rho간격은 1픽셀,theta는 1도 단위로 처리합니다.
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);

	Mat dst;
	// 그레이스케일 에지 영상 edge를 BGR 3채널 컬러 영상으로 변환 후 dst에 저장합니다.
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	// HoughLines() 함수에 의해 구해진 직선의 개수만큼 for 반복문을 수행합니다.
	for (size_t i = 0; i < lines.size(); i++) {
		// 직선의 방정식 파라미터에서 rho를 변수 r에, theta를 변수 t에 저장합니다.
		// x0와 y0는 원점에서 직선에 수선을 내렸을때 만나는 점의 좌표입니다.
		// pt1과 pt2에는 (x0, y0)에서 충분히 멀리 떨어져있는 직선상의 두 점 좌표가 저장됩니다.

		// for문은 hough에서 구한 로세타값을이용하여 직선상의 양 끝 두점ptr1,2를 구하고
		// 그 점을 이용해 빨간색 실선을 그리기위한 코드입니다.
		float rho = lines[i][0], theta = lines[i][1];
		float cos_t = cos(theta), sin_t = sin(theta);
		float x0 = rho * cos_t, y0 = rho * sin_t;
		float alpha = 1000;

		Point pt1(cvRound(x0 - alpha * sin_t), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 + alpha * sin_t), cvRound(y0 - alpha * cos_t));
		// 검출된 직선을 두께가 2인 빨간색 실선으로 그립니다.
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
	// HoughLines()의 다섯번째 인자 직선 검출 임계값을 250보다 작게 잡으면
	// 더 많은 직선을 확인할 수 있습니다. 
}
// HoughLinesP의 maxLineGap인자는 살짝 끊어진 두 직선을 하나의 직선으로 간주하고자 할때 사용합니다.
void hough_line_segments()
{
	// building.jpg 영상을 그레이스케일 형식으로 불러와 src에 저장합니다.
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	// 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	// 케니에지검출기를 이용하여 구한 에지 영상을 edge에 저장합니다.
	Canny(src, edge, 50, 150);
	// HoughLineP()함수를 이용하여 모든 직선성분의 시작점과 끝점의 좌표를 구합니다.
	vector<Vec4i> lines;	// 시작점 끝점 정보 저장할 출력벡터 설정
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	// 그레이스케일 에지영상을 BGR 3채널 컬러 영상으로 변환하여 dst에 저장합니다.
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	// HoughLinesP()에 의해 구해진 모든 직선성분을 dst위에 빨간색 직선으로 그립니다.
	// 범위기반 반복문으로써 익숙해지면 좋습니다.(벡터,배열등의 모든원소를하나씩 꺼내어 사용함)
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_circles()
{
	// coins.png 동전 영상을 불러와 Mat 형식 src에 저장합니다.
	Mat src = imread("coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	// src의 잡음을 제거하는 용도로 blur()함수를 적용합니다.
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	// HoughCircles()를 이용해서 원을 검출합니다.
	// 축적배열을 입력영상과 같은크기로 하고 
	// 두 원의 중심점 거리가 50픽셀보다 작으면 검출하지 않습니다.
	// 케니에지 검출기의 높은 임계값은 150으로 지정하고, 축적배열원소값이 30보다 크면
	// 원의 중심점으로 선택합니다. 검출된 원의 중심좌표와 반지름 정보는 circles변수에 저장됩니다.
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	// 입력 영상 src를 3채널 컬러영상으로 변환하여 dst에 저장합니다.
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	// dst 영상 위에 검출된 원을 빨간색으로 그립니다.
	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
