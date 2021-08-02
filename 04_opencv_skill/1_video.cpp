#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();

int main(void)
{
	camera_in();
	video_in();
	camera_in_video_out();

	return 0;
}

void camera_in()
{
	// 비디오객체생성과 장치를 여는 것을 동시에 함
	// VideoCapture cap;
	// cap.open(0);
	VideoCapture cap(0);
	// 예외처리코드
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}
	// 프레임을 출력합니다.
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	// mat 타입의 변수 선언
	Mat frame, inversed;
	while (true) {
		// 카메라 장치로부터 1프레임씩 받아 frame 변수에 저장합니다.
		// 프레임이 없다면 if문을 통해 빠져나갑니다.
		// >>연산자 재정의를 이용했습니다.
		cap >> frame;
		if (frame.empty())
			break;
		// 받은 프레임들을 inversed에 반전하여 넣습니다.
		inversed = ~frame;
		// !!!카메라 및 동영상 처리는 결국 매 프레임에 대한 정지 영상 처리와 
		// 같은 구조입니다!!!
		imshow("frame", frame);
		imshow("inversed", inversed);
		// 사용자로부터 10ms 동안 키보드 입력을 대기합니다.
		if (waitKey(10) == 27) // ESC key 누르면 while 빠져나감
			break;
	}

	destroyAllWindows(); 	//모든 창을 닫습니다.
}
// 동영상은 코덱을 이용하여 압축을 합니다.
// 코덱은 동영상을 압축하거나 압축을 해제하여 프레임을 받아오기도 합니다.
// 
void video_in()
{
	// 파일을 불러와 cap객체를 생성합니다.
	// 위와 다른점은 이미 있는 영상을 이용한다는 점입니다.
	VideoCapture cap("stopwatch.avi");
	// 안 열릴경우 예외처리
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}
	// 비디오 프레임의 가로,세로 크기, 전체 프레임수를 출력합니다.
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;
	// 동영상의 fps값을 확인하여 출력합니다.
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	// 계산한 fps를 통해 프레임 사이의 시간간격을 계산합니다.(delay)
	int delay = cvRound(1000 / fps);
	// Mat 형식의 변수선언
	Mat frame, inversed;
	while (true) {
		// 카메라 장치로부터 한 프레임을 받아
		// 프레임 변수에 저장
		cap >> frame;
		if (frame.empty())
			break;
		// 프레임을 반전하여 inversed에 저장
		inversed = ~frame;
		// 정지영상을 화면에 출력
		imshow("frame", frame);
		imshow("inversed", inversed);
		// 반복문 빠져나가는 코드
		if (waitKey(delay) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}
// 카메라로부터 프레임을 받아 동영상파일로 저장합니다.
void camera_in_video_out()
{
	// 시스템의 기본카메라를 사용합니다
	// 카메라 객체 생성
	VideoCapture cap(0);
	// 안 열릴경우의 예외처리
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}
	// 카메라 프레임의 가로,세로,프레임값을 받아옵니다.
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);
	// 원래는 
	// VideoWriter video; 	타입의 변수선언

	// int fourcc = VideoWriter::fourcc('D','I','V','X');
	// ㄴ코덱을 표현하는 4-문자코드, 4개의 문자를 묶어서 fourcc생성

	// video.open("output.mp4", fourcc, fps, Size(w,h)); 	위의 설정으로 생성

	// 위의 3줄 코드를 2줄로 줄인것이 아래코드들입니다.(delay 빼고)
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	// 딜레이 계산, 매 프레임사이의 시간간격
	int delay = cvRound(1000 / fps);
	// 저장할 동영상 파일 생성
	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	//예외 처리
	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}
	// Mat형식 선언
	Mat frame, inversed;
	while (true) {
		//카메라로부터 한 프레임 받아 frame에 저장
		cap >> frame; 	
		// 예외처리
		if (frame.empty())
			break;
		// 프레임 반전후 저장(inversed)
		inversed = ~frame;
		// 반전된 영상을 출력 동영상에 연산자 재정의를 이용해
		// 추가합니다.
		outputVideo << inversed;
		// 화면은 두개가 나옵니다.
		imshow("frame", frame);
		imshow("inversed", inversed);
		// esc 누르면 while 빠져나감
		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}
