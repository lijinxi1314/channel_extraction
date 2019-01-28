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
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "canny.h"
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


//컨피던스 맵 출력 관련
#define	BAR		8
#define	MAXCOLOR	255
#define	QUANTLEVEL	16

//처리 결과 관련
#define	DONE 1
#define	FAIL 0

//////////////////////////////////////////////////////////////////////////////////////

int main() {

	char filepath[300];

	for (int i = 1; i < TR_IMG_PER_CLASS_POSITIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	{
		//pos
		sprintf(filepath, "%s/%d.bmp", TR_POS_DIR, i);//읽을 파일
						 
		canny cny(filepath,i);
	}
	cout << "\n positive 완료" << endl;
	
	//for (int i = 1; i < TR_IMG_PER_CLASS_NEGATIVE + 1; i++)//positive 영상 924개 //negative 영상 1499개
	//{
	//	
	//	//neg
	//	sprintf(filepath, "%s/%d.bmp", TR_NEG_DIR, i);//읽을 파일
	//												
	//	canny cny(filepath, i);
	//}
	//cout << "\n negative 완료" << endl;

	int x;
	cin >> x;

	return 0;
}
