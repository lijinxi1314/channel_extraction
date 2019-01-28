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
#include <string>
#include "opencv2/opencv.hpp"
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
#include<string>
#include<iostream>
using namespace std;

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>


//CLASSIFIER 수
#define TESTCLASSIFIER 410
//이미지 관련

#define   WIDTH   64//64
#define HEIGHT   128//128
#define   ORIGINAL_WINDOW_SIZE_X   64
#define   ORIGINAL_WINDOW_SIZE_Y   128

#define   TR_IMG_PER_CLASS_POSITIVE   924
#define   TR_IMG_PER_CLASS_NEGATIVE   1499

#define	TR_POS_DIR "F:/MIT/MIT/positive"
#define	TR_NEG_DIR "F:/MIT/MIT/negative"

#define OUT_POS_IMG "F:/MIT/MIT/channel/positive/pos_V"
#define OUT_NEG_IMG "F:/MIT/MIT/channel/negative/neg_V"


//컨피던스 맵 출력 관련
#define	BAR		8
#define	MAXCOLOR	255
#define	QUANTLEVEL	16

//처리 결과 관련
#define	DONE 1
#define	FAIL 0

//////////////////////////////////////////////////////////////////////////////////////

void grayChannel();

/*
gradient magnitude image 생성
*/
void grayChannel() {

	char filepath[300];
	char ofilepath[300];

	for (int i = 1; i < TR_IMG_PER_CLASS_POSITIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_POS_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_POS_IMG, i);//출력 파일


		cout << ofilepath << endl;//파일명 출력 확인


								  //원본 영상 그대로를 받음
		Mat img = imread(filepath, CV_RGB2GRAY);

		// 입력영상을 1차 블러링(가우시안 이용)-> 노이즈 제거
		Mat output;
		cvtColor(img, output, CV_RGB2GRAY);
		cv::imwrite(ofilepath, output);


	}//positive 이미지 저장완료


	for (int i = 1; i < TR_IMG_PER_CLASS_NEGATIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_NEG_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_NEG_IMG, i);//출력 파일


		cout << ofilepath << endl;//파일명 출력 확인


								  //원본 영상 그대로를 받음
		Mat img = imread(filepath, CV_RGB2GRAY);

		// 입력영상을 1차 블러링(가우시안 이용)-> 노이즈 제거
		Mat output;
		cvtColor(img, output, CV_RGB2GRAY);
		cv::imwrite(ofilepath, output);


	}//netgative 이미지 저장완료

}

void LUV() {
	char filepath[300];
	char ofilepath[300];

	for (int i = 1; i < TR_IMG_PER_CLASS_POSITIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_POS_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_POS_IMG, i);//출력 파일


		cout << ofilepath << endl;//파일명 출력 확인


								  //원본 영상 그대로를 받음

		Mat img = imread(filepath, CV_RGB2Luv);

		// 입력영상을 1차 블러링(가우시안 이용)-> 노이즈 제거
		Mat output;
		cvtColor(img, output, CV_RGB2Luv);

		////split
		Mat LUV;
		cvtColor(img, LUV, COLOR_BGR2Luv);
		vector<Mat> LuvPlane;
		split(LUV, LuvPlane);
		/*imshow("Luv-L", LuvPlane[0]);
		imshow("Luv-u", LuvPlane[1]);
		imshow("Luv-v", LuvPlane[2]);*/

		cv::imwrite(ofilepath, LuvPlane[2]);


	}//positive 이미지 저장완료


	for (int i = 1; i < TR_IMG_PER_CLASS_NEGATIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_NEG_DIR, i);//읽을 파일
		sprintf(ofilepath, "%s/%d.bmp", OUT_NEG_IMG, i);//출력 파일


		cout << ofilepath << endl;//파일명 출력 확인


								  //원본 영상 그대로를 받음
		Mat img = imread(filepath, CV_RGB2Luv);

		// 입력영상을 1차 블러링(가우시안 이용)-> 노이즈 제거
		Mat output;
		cvtColor(img, output, CV_RGB2Luv);
		
		Mat LUV;
		cvtColor(img, LUV, COLOR_BGR2Luv);
		vector<Mat> LuvPlane;
		split(LUV, LuvPlane);
		/*imshow("Luv-L", LuvPlane[0]);
		imshow("Luv-u", LuvPlane[1]);
		imshow("Luv-v", LuvPlane[2]);*/

		cv::imwrite(ofilepath, LuvPlane[2]);


	}//netgative 이미지 저장완료
}


int main() {

	LUV();
	cout << "모두 완료" << endl;
	int x;
	cin >> x;
}
