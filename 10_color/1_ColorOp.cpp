#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void color_op();
void color_inverse();
void color_grayscale();
void color_split();

int main(void)
{
	color_op();
	color_inverse();
	color_grayscale();
	color_split();

	return 0;
}

void color_op()
{
	// butterfly파일을 3채널 BGR컬러로 Mat형식으로 src에 저장합니다.
	Mat img = imread("butterfly.jpg", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Vec3b& pixel = img.at<Vec3b>(0, 0);
	uchar b1 = pixel[0];
	uchar g1 = pixel[1];
	uchar r1 = pixel[2];

	Vec3b* ptr = img.ptr<Vec3b>(0);
	uchar b2 = ptr[0][0];
	uchar g2 = ptr[0][1];
	uchar r2 = ptr[0][2];
}

void color_inverse()
{
	// butterfly파일을 3채널 BGR컬러로 Mat형식으로 src에 저장합니다.
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 반전된영상을 저장할 dst영상을 생성합니다.
	// dst 영상의 모든 픽셀값은 이후 for 반복문에서 설정할 것이므로 
	// 초깃값은 따로 지정하지 않습니다.
	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			// src와 dst영상의 (i,j)좌표 픽셀값을 각각 p1,p2변수에 참조로 받습니다.
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);
			// p1 픽셀의 세 개 성분 값을 모두 반전시켜 p2 픽셀값으로 설정합니다.
			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
			// for문 이후 
			// dst.at<Vec3b>(j,i)=Vec3b(255,255,255)-src.at<Vec3b>(j,i);
			// 로 바꿔 쓸 수 있습니다.
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_grayscale()
{
	// 두번째인자 지정하지 않았으므로 3채널 BGR컬러영상형식으로 불러옵니다.
	Mat src = imread("butterfly.jpg");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	// 컬러를 그레이로 변환하여 dst에 저장합니다.
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_split()
{
	// candies영상을 3채널 컬러로 불러옵니다. 
	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// src영상의 채널을 분할하여 bgr_planes벡터에 저장합니다.
	// bgr_plane[0]에는 파란색 색상 평면, bgr_plane[1]에는 녹색 색상 평면
	// bgr_plane[2]에는 빨간색 색상 평면이 저장됩니다.
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}