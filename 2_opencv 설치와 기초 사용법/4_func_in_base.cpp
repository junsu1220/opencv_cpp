#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
    // imread 반환값은 불러온 영상 데이터(mat객체)
    // 인자로 불러올 영상 파일 이름을 받습니다.
    // 만약 다른 폴더라면 절대경로 혹은 상대경로형식으로 불러와야 합니다.
    // 추가로 플래그를 인자로 받는데 여러가지 옵션을 줄 수 있습니다.
	img = imread("lenna.bmp");

    // 여기서는 사용되지 않았지만 imwrite()함수가 있습니다. mat객체에 저장된
    // 영상데이터를 파일로 저장하기위해 사용하는 함수로 1인자로 저장할 영상파일이름
    // 2인자로 저장할 영상데이터 객체, 3인자로 저장할 영상파일 형식에 의존적인
    // 파라미터값을 받는데 예를 들어 jpg 파일의 압축률을 95%로 하고 싶을때
    // vecter<int> params;
    // params.push_back(IMWRITE_JPEG_QUALITY);
    // params.push_back(95);
    // imwrite("lenna.jpg",img,params);
    // 의 방식으로 쓰면 됩니다.

    // imread로 lenna.bmp 파일을 불러온 후 정상적인지 확인하기 위해 
    // Mat::empty()함수를 사용했습니다.
    // 반환값으로 true or false 를 반환합니다.
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

    // 영상출력을 위해 빈창을 생성하고 인자로 창의 이름을 받습니다.
	// 2인자로 창의 속성을 지정할 수 있는데 생략하면 자동으로 AUTOSIZE로 지정됩니다.
    namedWindow("image");
    
    // destroyWindow() 인자로 소멸시킬 창이름을 받아 종료시킵니다.
    
    // moveWindow() 인자로 위치를 이동할 창이름과 창이 이동할 위치의 x좌표 y좌표의 값을 받습니다.

    // resizeWindow() 인자로 크기를 변경할 창의 이름과 창의 가로크기 세로크기를 받습니다.

    // 영상을 출력할 대상 창이름과 출력할 영상데이터(mat객체)의 값을 받습니다.
	imshow("image", img);

    // 키입력을 기다릴 시간을 입력으로 받고 눌린 키값을 반환합니다. 
    // if와 함께 esc=27을 이용하여 창을 끌때 사용합니다.
	waitKey();

	return 0;
}