#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void writeData();
void readData();

// String filename = "mydata.xml";
// String filename = "mydata.yml";
String filename = "mydata.json";		//저장할 파일네임을 미리설정함

int main(void)
{
	writeData();
	readData();

	return 0;
}

void writeData()
{
	// 파일에 저장할 데이터 변수 선언합니다.
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);
	// 파일 스토어 객체를 선언하고 
	// open함수의 열거형상수 인자를 통해 쓰기방식으로 생성합니다.
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE);
	// 예외처리
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
	// << 연산자를 통해 실제 저장할 준비한 데이터를 파일에 저장합니다.
	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;
	// 데이터 저장이 끝나면 파일을 닫습니다.
	fs.release();
}
// 데이터파일을 불러옵니다.
void readData()
{
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;
	// FileStorage 객체 fs를 선언하면서 mydata를 읽기모드로 생성합니다.
	FileStorage fs(filename, FileStorage::READ);
	// 예외처리
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
	// 객체이름 >> 데이터형식에 맞는 변수 이름
	// [], >> 연산자를 이용하여 파일에서 데이터를 읽습니다.
	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();
	// 파일로부터 잘읽었나 확인하기 위해 콘솔창에 출력합니다.
	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n" << mat1 << endl;
}
