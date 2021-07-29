#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
	MatOp1();
	MatOp2();
	MatOp3();
	MatOp4();
	MatOp5();
	MatOp6();
	MatOp7();

	return 0;
}

void MatOp1()
{
	// 기본적인 비어있는 행렬입니다.
	Mat img1; 	// empty matrix
	// 2는 그레이스케일에서 사용하는 타입입니다.
	Mat img2(480, 640, CV_8UC1);		// unsigned char, 1-channel
	// 3은 트루컬러에서 사용하는 타입입니다.
	Mat img3(480, 640, CV_8UC3);		// unsigned char, 3-channels
	// 행렬의 크기를 지정할때 size클래스를 사용할 수도 있습니다.
	Mat img4(Size(640, 480), CV_8UC3);	// Size(width, height)

	// 행렬의 모든원소값에 쓰레기값이 아닌 초기화를 하기위해
	// Scalar를 사용합니다. 
	// 5는 픽셀값 128의 그레이스케일
	// 6은 모든 픽셀이 0,0,255인 빨간색 트루컬러 스케일입니다.B,G,R.
	Mat img5(480, 640, CV_8UC1, Scalar(128));		// initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));	// initial values, red

	// Mat::zeros()는 새로 생성할 행렬의 크기와 타입정보를 인자로 받습니다.
	// Mat클래스의 정적변수라 Mat::을 붙여야합니다.
	// 반환값은 Mat타입의 변수에 할당할 수 있습니다.
	// 0으로 초기화된 3x3정수형 행렬
	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	// 0's matrix
	// 모든원소가 1로 초기화된 행렬
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	// 1's matrix
	// 단위행렬을 반환합니다!
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	// identity matrix

	// 먼저 작은 배열 data[]를 만들고
	// 이 배열의 원소개수도 맞고 자료형도 같은 mat을 만듭니다.
	// 이렇게 하면 외부 메모리 공간과 mat객체의 값이 상호 공유됩니다.
	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	// Mat_클래스를 사용하는 방법
	// Mat_클래스는 <<연산자와 콤마(,)를 이용하여 간단하게 행렬 설정

	// Mat_<float>(2, 3);
	// mat5_ << 1, 2, 3, 4, 5, 6;
	// Mat mat5 = mat5_; 를 mat5_안쓰고 한줄로 줄이면
	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	// 초기화리스트를 사용한 행렬초기화 방법 mat5와 같은 행렬입니다.(uchar)빼고
	Mat mat6 = Mat_<uchar>({2, 3}, { 1, 2, 3, 4, 5, 6 });

	// Mat::create()함수는 일단 기존 메모리공간을 해제한 후
	// 새로운 행렬 데이터 저장을 위한 메모리공간을 할당합니다.
	mat4.create(256, 256, CV_8UC3);	// uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	// float, 1-channel
	// Mat::create()는 새로 만들고 초기화기능 없기에
	// Mat::setTo()멤버 함수를 이용하여 행렬 전체 원소값을 초기화 할 수 있습니다.
	// Scalar클래스는 앞에서 정의했습니다. 255,0,0은 파란색에 해당합니다.
	// 모든 픽셀을 파란색으로 설정하고 모든 원소값을 1.f로 설정합니다.
	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}

void MatOp2()
{
	// 강아지 사진이 담겨있는 파일을 불러와서 Mat타입의 변수 img1에 저장합니다.
	Mat img1 = imread("dog.bmp");
	// 얕은 복사, 행렬의 원소데이터를 공유한다.
	Mat img2 = img1;
	Mat img3;
	// 이 또한 얕은복사
	img3 = img1;

	// 픽셀데이터를 공유하는 것이 아닌 메모리공간을 새로 할당하고 싶다면
	// Mat::clone , Mat::copyTo 를 사용합니다. (깊은 복사)
	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);
	// 처음의 영상의 모든 픽셀을 노란색으로 칠합니다.
	img1.setTo(Scalar(0, 255, 255));	// yellow
	// 얕은복사인 2,3은 노란색이지만
	// 깊은복사인 4,5는 원본 그대로입니다.
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}

void MatOp3()
{
	// 고양이영상을 3채널 컬러형태로 불러와서 img1에 저장합니다.
	Mat img1 = imread("cat.bmp");
	// 예외처리
	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 괄호 연산자 재정의로 동작합니다.
	// (220,120)좌표로부터 340*240크기만큼의 
	// 사각형 부분 영상을 추출합니다.
	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();
	// 이때 괄호연산자로 얻은 추출 영상은 얕은 복사이므로 
	// 원본의 부분영상의 픽셀값을 변경하면 원본영상의 픽셀값도 함께 변경됩니다.
	img2 = ~img2;
	// 추출영상을 바꿔도 원본의 부분영상도 바뀝니다.
	// 하지만 뒤에 .clone() 을 붙여서 사용한 img3는 변하지 않습니다.
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	
	// 여기엔 없지만 Mat::rowRange(), Mat::colRange(), Mat::row(), Mat::col()은
	// 지정범위의 행이나 열로 구성된 행렬을 반환하거나 1행짜리,1열짜리 행렬을 복사해 만들수 있습니다.
	// 얕은복사이므로 메모리를 따로 할당하려면 Mat::clone() 함수와 함께 사용해야 합니다.
	waitKey();
	destroyAllWindows();
}

void MatOp4()
{
	// 모든원소값이 0인 CV_8UC1타입의 행렬 mat1 정의
	// 각 원소는 uchar 자료형을 사용합니다.
	// 이 행렬의 모든 원소값을 1만큼 증가 시킵니다.
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
	// 이중 반복문을 써서 j,i의 값을 올리고 
	// Mat::at()가 행렬원소를 참조로 반환하므로 
	// Mat::at()함수의 반환값을 변경하면 mat1의 행렬원소값도 변경됩니다.
	// 각 원소가 uchar이라 <uchar>를 넣었습니다.
	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}
	// 또 하나의 행렬 원소 접근법으로 Mat::ptr()이 있습니다.
	// Mat행렬에서 특정 행의 첫번째 원소 주소를 반환합니다. 
	// 모든 원소값을 1만큼 증가 하는 코드입니다.
	// 바깥쪽 반복문은 각행의 번호를 나타내며 그 행의 첫번째 원소 주소를
	// 포인터형 변수p에 저장하고 p를 1차원 배열처럼 사용하여 접근한 후
	// 두번째 반복문에서 열에 접근해서 원소값을 1씩 올립니다.
	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}
	// 행렬의 모든 원소를 참조하는 경우는 ptr이 
	// 행렬의 임의 원소에 빈번하게 접근하는 경우는 at가 좋습니다.

	// at,ptr사용시 함수인자로 전달된 값이 행렬의 크기를 벗어나면 에러가 발생합니다.
	// 이때 Mat행렬 원소 참조를 위한 반복자 변수를 만들어서 크기에 상관없이
	// 행렬 전체 원소를 차례대로 참조합니다.
	// begin으로 행렬의 첫번째 원소위치를 end로 마지막 원소 바로 다음위치를 얻을 수 있습니다.
	// 아래 코드 또한 행렬의 모든 원소를 1씩 증가시키는 코드인데
	// MatIterator 타입 변수 it를 선언합니다, 반복자변수 it가 가리키는 원소 값을 참조하기 위해
	// (*it)형태로 코드를 작성합니다.
	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}
	// MatIterator_반복자는 동작속도면에서 ptr보다 느리고 at처럼 임의의 위치에 못가서 사용성이 높지 않습니다.

	cout << "mat1:\n" << mat1 << endl;
}

void MatOp5()
{
	Mat img1 = imread("lenna.bmp");

	cout << "Width: " << img1.cols << endl;		//512출력
	cout << "Height: " << img1.rows << endl;	//512출력
	cout << "Channels: " << img1.channels() << endl;	//행렬의 채널 수를 반환합니다.

	// 레나영상이 그레이인지 컬러인지 알아보는 코드
	// imread에서 두번째 인자를 설정하지 않았으므로 컬러입니다.
	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;
	// data변수는 행렬 원소데이터가 저장되어 있는 메모리공간의 시작 주소를 가리킵니다.
	// 따라서 활용하면 행렬원소를 직접 참조할 수 있지만 연산을 잘못하면 
	// 에러가 발생하므로 앞의 at,ptr을 사용하는 것이 권장됩니다.

	// 여기서 나오는 data[]는 앞에서의 행렬 만드는 법에 나오는 data입니다. 포인터아님
	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	// 2x2행렬의 float을 쓰는 mat1
	Mat mat1(2, 2, CV_32FC1, data);
	// cout << Mat객체이름 
	// Mat1 모든 원소 출력
	cout << "mat1:\n" << mat1 << endl;
}

void MatOp6()
{
	// data배열로 2x2행렬 mat1을 생성합니다.
	float data[] = { 1, 1, 2, 3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
	// mat1행렬의 역행렬을 구하여 mat2에 저장합니다.
	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;
	
	// 행렬의 행과 열을 서로 교환하는 전치행렬을 구하여 출력합니다.
	cout << "mat1.t():\n" << mat1.t() << endl;
	// 연산자 재정의로 행렬의 산술연산을 수행하고 출력합니다.
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;
}

void MatOp7()
{
	// 레나를 그레이로 불러옴
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// convertTo()로 픽셀값을 float으로 바꾸어 연산의 정확도를 높입니다.
	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);
	// reshape()함수는 행렬 원소 데이터를 복사하여 그 데이터를 참조하는 
	// 행렬을 반환합니다. 그래서 반환된것을 수정하면 원본도 수정됩니다.
	// 3x4 가 1x12행렬 mat2로 변경되었습니다.
	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;
	// resize()는 행렬의 모양이 아닌 단순히 크기를 변경합니다.
	// 인자값이 기존 행 개수 보다 작으면 아래쪽 행을 제거하고
	// 크면 아래쪽에 행을 추가합니다.
	// 3x4였지만 5x4로 변경되고 새로운 행의 원소는 전부 100입니다.
	mat1.resize(5, 100);
	cout << "mat1:\n" << mat1 << endl;

	// mat3는 모든 원소가 255로 구성된 1행 4열 행렬입니다.
	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	// 기존 5x4의 mat1의 아래에 mat3행렬을 추가합니다.(push_back)
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;
	// 반대로 제거할때는 (pop_back)을 씁니다.
}
