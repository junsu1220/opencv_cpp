#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void affine_transform();
void affine_translation();
void affine_shear();
void affine_scale();
void affine_rotation();
void affine_flip();

int main(void)
{
	affine_transform();
	affine_translation();
	affine_shear();
	affine_scale();
	affine_rotation();
	affine_flip();

	return 0;
}

void affine_transform()
{
	// tekapo.bmp파일을 3채널 컬러영상으로 불러와 src에 저장합니다.
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 입력 영상과 출력 영상에서의 세 점 좌표를 저장할 srcPts와 dstPts배열을 선언합니다.
	Point2f srcPts[3], dstPts[3];
	// srcPts 배열에 입력영상의 좌측,우측상단,우측하단의좌표를 저장합니다.
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	// dstPts 배열에 srcPts 점들이 이동할 좌표를 저장합니다. y축은 내려가면서 +입니다.
	// (0,0)->(50,50)///(639,0)->(540,100)///(639,479)->(590,430)
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);
	// 2*3 어파인 변환 행렬을 M에 저장합니다.
	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	// 어파인 변환 행렬 M을 이용하여 src 영상을 어파인 변환하여 dst에 저장합니다.
	// warpAffine()함수의 네번째 인자에 Size()를 지정하여 
	// dst와 src의 영상크기가 같게 했습니다.
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
// 이동 변환
void affine_translation()
{
	// tekapo.bmp 파일을 3채널 컬러 영상으로 불러와 src에 저장합니다.
	Mat src = imread("tekapo.bmp");
	// 예외 처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 가로로 150픽셀, 세로로 100픽셀 이동하는 어파인 변환 행렬 M을 생성합니다.
	Mat M = Mat_<double>({ 2, 3 }, { 1, 0, 150, 0, 1, 100 });

	Mat dst;
	// src영상을 이동변환을 하여 dst영상을 생성합니다. 영상크기는 같게 설정했습니다.
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_shear()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 가로 밀림정도를 0.3으로 설정한 전단 변환 행렬M을 생성합니다.
	double mx = 0.3;
	Mat M = Mat_<double>({ 2, 3 }, { 1, mx, 0, 0, 1, 0 });

	Mat dst;
	// 행렬M을 이용하여 어파인변환을 수행합니다. 
	// 전단변환에 의해 입력영상의 일부가 잘리지 않도록 결과 영상 크기를
	// cvRound(src.cols + src.rows * mx) 형태로 지정하였습니다.
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_scale()
{
	// rose.bmp를 3채널 컬러영상으로 불러와 src영상에 저장합니다.
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	// src를 4배,4배확대하여 dst1을 생성
	// 크기가 480*320->1920*1280, 보간법은 최근방 이웃 보간법
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	// 기본 양산형 보간법
	resize(src, dst2, Size(1920, 1280));
	// 3차 회선 보간법
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	// 란초스 보간법
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	// src와 dst1,2,3,4 를 출력합니다. (400,500)좌표로부터 
	// 400*400크기의 부분영상을 화면에 출력합니다.
	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));		// 영상은 미세하게 좋으나 
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));		// 연산속도가 느림

	waitKey();
	destroyAllWindows();
}

void affine_rotation()
{
	// tekapo.bmp 호수 영상을 3채널 컬러영상으로 불러와 Mat 형식 src 변수에 저장합니다.
	Mat src = imread("tekapo.bmp");
	// 예외처리
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 영상의 중심 좌표를 가리키는 변수 cp를 선언합니다.
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	// cp좌표를 기준으로 반시계 방향으로 20도 
	// 회전하는 변환 행렬 M을 생성합니다.
	Mat M = getRotationMatrix2D(cp, 20, 1);
	// 변환행렬 M을 이용하여 src영상을 어파인 변환하고,
	// 그 결과를 dst에 저장합니다.
	// dst영상 크기는 src와 같게 설정합니다.
	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_flip()
{
	Mat src = imread("eastsea.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	// flip()함수에 전달할 flipCode 세 개를 정수형 배열에 저장합니다.
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		// flipCode 배열에 저장된 정수값을 이용하여 대칭변환을 수행합니다.
		flip(src, dst, flipCode[i]);
		// 대칭변환 결과 영상위에 flipCode 값을 출력합니다.
		// 1은 좌우대칭 0은 상하대칭 -1은 상하와 좌우 모두를 뒤집었습니다.
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}