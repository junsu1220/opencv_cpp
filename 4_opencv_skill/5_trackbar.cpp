#include "opencv2/opencv.hpp"
#include <iostream>
// 프로그램 동작중에 트랙바를 이용 사용자 입력을 받습니다.
using namespace cv;
using namespace std;
// 트랙바 콜백 함수를 선언합니다.
void on_level_change(int pos, void* userdata);

int main(void)
{
	// 픽셀값이 0으로 초기화된 400*400크기의 영상 img를 생성합니다.
	Mat img = Mat::zeros(400, 400, CV_8UC1);
	// 트랙바를 부착할 이미지창을 미리생성합니다.
	namedWindow("image");
	// 트랙바를 생성하고 트랙바 콜백함수를 등록합니다.
	// 트랙바이름은 level이고 image에 붙입니다.
	// 트랙바 위치를받을 정수형변수주소는 0
	// 트랙바 최대위치는 16입니다.
	// 트랙바 위치가 바뀔때마다 호출되게 만들 콜백함수이름(함수의 포인터),on_level_change
	// 콜백함수에 전달할 사용자 데이터의 포인터, 여기서는 img객체의 주소입니다.
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img);
	
	// img영상을 image창에 출력하고, 키입력 있을때까지 유지합니다.
	imshow("image", img);
	waitKey();

	return 0;
}
// 콜백함수, 트랙바 위치 바뀔때마다 자동으로 호출됨
// 1인자에는 현재트랙바 위치정보
// 2인자에는 createTracbar()에서 지정한 사용자 데이터 포인터값이 전달됩니다.
void on_level_change(int pos, void* userdata)
{
	// void*타입의 인자 userdata를 Mat*타입으로 형변환한 후 img변수로 참조합니다.
	Mat img = *(Mat*)userdata;
	// 트랙바 위치 pos에 16을 곱한값을 img 영상의 전체 픽셀값으로 설정합니다.
	// 255보다 크면 포화연산이 적용됩니다.
	img.setTo(pos * 16);
	// 픽셀값이 설정된 img영상을 image 창에 출력합니다.
	imshow("image", img);

	// 트랙바 생성 이후 트랙바의 현재위치를 알고싶다면 getTrackbarPos()
	// 트랙바 위치를 강제로 특정 위치로 옮기고 싶다면 setTrackbarPos()를 쓰면됩니다.
}
