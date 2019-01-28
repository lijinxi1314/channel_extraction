#pragma once
#include "AdaBooster.h"
#include "CrossValidator.h"
#include "FeatureParser.h"
#include "FeatureVector.h"
#include "sorting.h"
#include "StrongClassifier.h"
#include "TrainingData.h"
#include "WeakClassifier.h"
#include "Element.h"
#include <iostream>
#include <fstream>
#include<stdio.h>
#include<iostream>
#include "ConfidenceCell.h"
#include "ConfidenceMap.h"
using namespace std;
#include <string>
#include "opencv2/opencv.hpp"
using namespace cv;

//CLASSIFIER 수
#define TESTCLASSIFIER 410
//이미지 관련

#define   WIDTH   64//64
#define HEIGHT   128//128
#define   ORIGINAL_WINDOW_SIZE_X   64
#define   ORIGINAL_WINDOW_SIZE_Y   128


//#define   TR_IMG_PER_CLASS   100

#define   TR_IMG_PER_CLASS_POSITIVE   924
#define   TR_IMG_PER_CLASS_NEGATIVE   1499
//#define	TR_POS_DIR "F:/Pedestrian detection/Pedestrian detection/PedestrianDetection/face/trainingSet/faces"
#//define	TR_NEG_DIR "F:/Pedestrian detection/Pedestrian detection/PedestrianDetection/face/trainingSet/nonFaces"

#define	TR_POS_DIR "F:/MIT/MIT/positive"
#define	TR_NEG_DIR "F:/MIT/MIT/negative1"
#define OUT_POS_GM "F:/MIT/MIT/pos_gradient_magnitude"
#define OUT_NEG_GM "F:/MIT/MIT/neg_gradient_magnitude"


//컨피던스 맵 출력 관련
#define	BAR		8
#define	MAXCOLOR	255
#define	QUANTLEVEL	16

//처리 결과 관련
#define	DONE 1
#define	FAIL 0

//////////////////////////////////////////////////////////////////////////////////////

void gradientChannel();

/*
gradient magnitude image 생성
*/
void gradientChannel() {

	char filepath[300];
	char ofilepath[300];

	for (int i = 1; i < TR_IMG_PER_CLASS_NEGATIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		//sprintf(filepath, "%s/%d.bmp", TR_POS_DIR, i);//읽을 파일
		//sprintf(ofilepath, "%s/%d.bmp", OUT_POS_GM, i);//출력 파일
		
		//neg
		sprintf(filepath, "%s/%d.bmp", TR_NEG_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_NEG_GM, i);//출력 파일

		cout << ofilepath << endl;//파일명 출력 확인

								  //원본 영상 그대로를 받음
		Mat img = imread(filepath, CV_LOAD_IMAGE_COLOR);

		// 입력영상을 1차 블러링(가우시안 이용)-> 노이즈 제거
		GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);

		// convert it to grayscale (CV_8UC3 -> CV_8UC1)
		//Mat input_gray;
		cvtColor(img, img, COLOR_RGB2GRAY);//gray image 로 변환

										   //x,y의 gradient 계산
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S; // use 16 bits unsigned to avoid overflow

							 //Scharr( input_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
		Sobel(img, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x); // CV_16S -> CV_8U

											 //Scharr( input_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
		Sobel(img, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y); // CV_16S -> // CV_16S -> CV_8U

											 // x와 y방향의 absolute gradient image를 추가하여 출력영상 생성
		Mat output;
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, output);

		// show image
		//imshow("Image", output);
		//waitKey();

		//image 저장
		imwrite(ofilepath,output);


	}//positive 이미지 저장완료

}


//int main() {
//
//	gradientChannel();
//	cout << "모두 완료" << endl;
//	
//	int x;
//	cin >> x;
//}
