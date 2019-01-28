#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.h"

#define	NUM_BINS	9
#define	NUM_CELL_X	20
#define	NUM_CELL_Y	20
#define PI	3.14
#define MASK_SIZE	3

int xMask[MASK_SIZE][MASK_SIZE] = {
	{ 1, 0, -1 },
	{ 2, 0, -2 },
	{ 1, 0, -1 }
};

int yMask[MASK_SIZE][MASK_SIZE] = {
	{ 1, 2, 1 },
	{ 0, 0, 0 },
	{ -1, -2, -1 }
};

typedef struct {
	float* feature;
	int label;
}HOGDescriptor;

int extractHOGFromImg(char* filename, char* ofilename)
{
	IplImage* oImg = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if (oImg == nullptr)
		return -1;

	IplImage* pImg = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);
	IplImage* eXImg = cvCloneImage(oImg);
	IplImage* eYImg = cvCloneImage(oImg);

	

	int height = oImg->height;
	int width = oImg->width;

	float* edgeXImg = new float[height * width];
	float* edgeYImg = new float[height * width];
	float* magImg = new float[height * width];
	float* oriImg = new float[height * width];

	for (int i = 0; i < height * width; i++)
	{
		edgeXImg[i] = edgeYImg[i] = magImg[i] = oriImg[i] = 0;
		eXImg->imageData[i] = (unsigned char)0;
		eYImg->imageData[i] = (unsigned char)0;
	}

	for (int i = 1; i< height - 1; i++)
		for (int j = 0; j < width - 1; j++)
		{
			int xDiff = 0;
			int yDiff = 0;
			for (int a = 0; a < MASK_SIZE; a++)
			{
				for (int b = 0; b < MASK_SIZE; b++)
				{
					xDiff += (unsigned char)(oImg->imageData[(i + a - 1)*width + (j + b - 1)]) * xMask[a][b];
					yDiff += (unsigned char)(oImg->imageData[(i + a - 1)*width + (j + b - 1)]) * yMask[a][b];
				}
			}

			edgeXImg[i*width + j] = xDiff;
			edgeYImg[i*width + j] = yDiff;

			eXImg->imageData[i*width + j] = (unsigned char)((xDiff < 0 ? -1 * xDiff : xDiff) > 255 ? 255 : xDiff);
			eYImg->imageData[i*width + j] = (unsigned char)((yDiff < 0 ? -1 * yDiff : yDiff) > 255 ? 255 : yDiff);

			magImg[i*width + j] = sqrt(xDiff * xDiff + yDiff*yDiff);

			if (magImg[i*width + j] < 50)
				xDiff = -200;

			if (xDiff != 0)
				oriImg[i*width + j] = atan2(yDiff, xDiff); //-pi to pi
		}

	int xCellSize = floor((float)width / (float)NUM_CELL_X);
	int yCellSize = floor((float)height / (float)NUM_CELL_Y);

	float binPerDegree = 360.0f / (float)NUM_BINS;
	float histogram[NUM_BINS];
	for (int i = 0; i < NUM_CELL_Y; i++)
	{
		for (int j = 0; j < NUM_CELL_X; j++)
		{
			for (int a = 0; a < NUM_BINS; a++)
				histogram[a] = 0;

			for (int a = 0; a < yCellSize; a++)
			{
				for (int b = 0; b < xCellSize; b++)
				{
			
					if (oriImg[(i*yCellSize + a)*width + (j*xCellSize + b)] == -200)
						continue;

					if (oriImg[(i*yCellSize + a)*width + (j*xCellSize + b)] < 0)
						oriImg[(i*yCellSize + a)*width + (j*xCellSize + b)] += 2.0*PI; //0 - 2pi

					float degree = oriImg[(i*yCellSize + a)*width + (j*xCellSize + b)] * 360.0f / (2.0 * PI);
					int index = floor(degree / binPerDegree);
					if (index < 0)
						index = 0;

					histogram[index] += magImg[(i*yCellSize + a)*width + (j*xCellSize + b)];
				}
			}

			float maxVal = 0;
			int zeroCnt = 0;
			for (int a = 0; a < NUM_BINS; a++)
			{
				histogram[a] /= (float)(yCellSize * xCellSize);

				if (histogram[a] == 0)
					zeroCnt++;
				maxVal = histogram[a] > maxVal ? histogram[a] : maxVal;
			}

			if (zeroCnt > floor((float)NUM_BINS / 2.0f))
			{
				continue;
			}
			
			float smallAxis = (float)(xCellSize > yCellSize ? yCellSize : xCellSize) / 2.0f;
			for (int a = 0; a < NUM_BINS; a++)
			{
				if (maxVal == 0)
					continue;
				histogram[a] = (histogram[a] * smallAxis) / maxVal; //(float)(yCellSize * xCellSize);
			}

			
			int sPtX = j*xCellSize + xCellSize / 2;
			int sPtY = i*yCellSize + yCellSize / 2;

			for (int a = 0; a < NUM_BINS; a++)
			{
				float degree = (a * binPerDegree);
				degree = degree > 180.0f ? degree - 360 : degree;
				float vPtX = cos(degree * PI / 180.0)*histogram[a];
				float vPtY = sin(degree * PI / 180.0)*histogram[a];

				vPtX = vPtX > width ? width - 1 : vPtX;
				vPtY = vPtY > height ? height - 1 : vPtY;
				cvLine(pImg, cvPoint(sPtX, sPtY), cvPoint(sPtX + vPtX, sPtY + vPtY),
					CV_RGB(255, 0, 0), 1, 8, 0);
			}
		}
	}
	
	cvSaveImage(ofilename, pImg);
	cvReleaseImage(&pImg);
	cvReleaseImage(&oImg);
	return 1;
}

#define STR_DIR2 "C:/Users/EunjeongKo/Desktop/јѕј­Бо_assistive/experiment/Combined"

int main()
{
	char ifilename[300];
	char ofilename[300];
	for (int i = 0; i < 100; i++)
	{
		sprintf(ifilename, "%s/%d.bmp", STR_DIR2, i);
		sprintf(ofilename, "%s/%d_fil_result.bmp", STR_DIR2, i);
		extractHOGFromImg(ifilename, ofilename);
		cout << "Done: " << ifilename << endl;
	}
	return 0;
}
