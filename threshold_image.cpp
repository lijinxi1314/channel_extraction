#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
#include<iostream>
using namespace std;
#define   TR_IMG_PER_CLASS_POSITIVE   924
#define   TR_IMG_PER_CLASS_NEGATIVE   1499

#define OUT_POS_DIR  "F:/MIT/MIT/channel/positive/pos_threshold" /////바꿀부분
#define OUT_NEG_DIR  "F:/MIT/MIT/channel/negative/neg_threshold" /////바꿀부분

#define	TR_POS_DIR "F:/MIT/MIT/positive"
#define	TR_NEG_DIR "F:/MIT/MIT/negative"

int main()

{
	char filepath[300];
	char ofilepath[300];

	for (int i = 1; i < TR_IMG_PER_CLASS_POSITIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_POS_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_POS_DIR, i);//출력 파일

														//이미지 파일을 불러와 그레이 이미지로 변환한다.  
		Mat input_gray_image = imread(filepath, IMREAD_GRAYSCALE);
		Mat result_binary_image;

		//threshold값을 127로 해서 이진화 한다.

		//입력 이미지의 특정 필셀값이 threshold값보다 크면 결과 

		//이미지상의 같은 위치의 픽셀값을 255로 한다.

		//thshold값보다 작을 경우에는 0이 된다.

		threshold(input_gray_image, result_binary_image, 127, 255, THRESH_BINARY);
		imwrite(ofilepath, result_binary_image);
	}

	cout << "\n positive 완료" << endl;

	for (int i = 1; i < TR_IMG_PER_CLASS_NEGATIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//neg
		sprintf(filepath, "%s/%d.bmp", TR_NEG_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_NEG_DIR, i);//출력 파일
		
		//이미지 파일을 불러와 그레이 이미지로 변환한다.  
		Mat input_gray_image = imread(filepath, IMREAD_GRAYSCALE);
		Mat result_binary_image;

		//threshold값을 127로 해서 이진화 한다.

		//입력 이미지의 특정 필셀값이 threshold값보다 크면 결과 

		//이미지상의 같은 위치의 픽셀값을 255로 한다.

		//thshold값보다 작을 경우에는 0이 된다.

		threshold(input_gray_image, result_binary_image, 127, 255, THRESH_BINARY);
		imwrite(ofilepath,result_binary_image);
	}

	cout << "\n negative 완료" << endl;


	//아무키나 누를 때 까지 대기한다.

	while (cvWaitKey(0) < 0);

}
