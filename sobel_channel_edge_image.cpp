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
#include<stdio.h>
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
#define OUT_POS_S45 "F:/MIT/MIT/pos_sobel_45"
#define OUT_NEG_S45 "F:/MIT/MIT/neg_sobel_45"


//컨피던스 맵 출력 관련
#define	BAR		8
#define	MAXCOLOR	255
#define	QUANTLEVEL	16

//처리 결과 관련
#define	DONE 1
#define	FAIL 0

//////////////////////////////////////////////////////////////////////////////////////
typedef unsigned char  BYTE;


void SobelEdge(const Mat& imageIn, Mat& imageOut)
{
	int nWidth = imageIn.col;
	int nHeight = imageIn.row;

	int nWStep = 2;

	// Sobel 마스크
	int Gx[9], Gy[9];
	Gx[0] = -1; Gx[1] = 0; Gx[2] = 1;
	Gx[3] = -2; Gx[4] = 0; Gx[5] = 2;
	Gx[6] = -1; Gx[7] = 0; Gx[8] = 1;

	Gy[0] = 1; Gy[1] = 2; Gy[2] = 1;
	Gy[3] = 0; Gy[4] = 0; Gy[5] = 0;
	Gy[6] = -1; Gy[7] = -2; Gy[8] = -1;

	BYTE* pIn = imageIn.at<BYTE>ptr();
	BYTE* pOut = imageOut.GetPtr();

	for (int r = 1; r<nHeight - 1; r++) // 영상 경계는 제외
	{
		for (int c = 1; c<nWidth - 1; c++) // 영상 경계는 제외
		{
			int sumX = 0;
			int sumY = 0;
			for (int y = 0; y<3; y++)
			{
				for (int x = 0; x<3; x++)
				{
					int py = r - 1 + y;
					int px = c - 1 + x;
					//영상과 Sobel 마스크와의 회선 연산 수행
					if (px >= 0 && px<nWidth && py >= 0 && py<nHeight)
					{
						sumX += Gx[y * 3 + x] * pIn[py*nWStep + px];
						sumY += Gy[y * 3 + x] * pIn[py*nWStep + px];
					}
				}
			}
			pOut[c] = sqrt((double)(sumX*sumX + sumY*sumY) / 32);
			//미분 벡터의 크기를 이용하여 경계선의 세기 계산
		}
		pOut += nWStep;
	}
}
