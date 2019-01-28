//#include "stdafx.h"
#include<iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include "math.h"
#define  PI 3.1415926
#define  N 8
using namespace std;
using namespace cv;

void m_filer(double *src, int height, int width, double *mask_rel, double *mask_img, int mW, int mH, int k,int m)
{
	IplImage *tmp;
	double a, b, c;
	char res[20];       //保存的图像名称

	tmp = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			a = 0.0;
			b = 0.0;
			c = 0.0;
			//去掉靠近边界的行列，无法滤波，超出范围 卷积
			if (i > int(mH / 2) && i < height - int(mH / 2) && j > int(mW) && j < width - int(mW / 2))
			{
				for (int m = 0; m < mH; m++)
				{
					for (int n = 0; n < mW; n++)
					{
						//printf("%f\n",src[(i+m-int(mH/2))*width+(j+n-int(mW))]);
						a += src[(i + m - int(mH / 2))*width + (j + n - int(mW))] * mask_rel[m*mW + n];
						b += src[(i + m - int(mH / 2))*width + (j + n - int(mW))] * mask_img[m*mW + n];
						//printf("%f,%f\n",a,b);
					}
				}
			}
			c = sqrt(a*a + b*b);
			c /= mW*mH;
			tmp->imageData[i*width + j] = (unsigned char)c;
		}
	}
	if (k == 0){
		sprintf(res, "gabor0/%d.bmp", m);
	//	printf("end0 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}
	else if (k == 1){
		sprintf(res, "gabor1/%d.bmp", m);
	//	printf("end1 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}
	else if (k == 2){
		sprintf(res, "gabor2/%d.bmp", m);
	//	printf("end2 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}
	else if (k == 3){
		sprintf(res, "gabor3/%d.bmp", m);
	//	printf("end3 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}

	else if (k == 4){
		sprintf(res, "gabor4/%d.bmp", m);
	//	printf("end4 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}

	else if (k == 5){
		sprintf(res, "gabor5/%d.bmp", m);
	//	printf("end5 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}

	else if (k == 6){
		sprintf(res, "gabor6/%d.bmp", m);
	//	printf("end6 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}
	else if (k == 7){
		sprintf(res, "gabor7/%d.bmp", m);
	//	printf("end7 ");
		cvSaveImage(res, tmp);
		cvReleaseImage(&tmp);
	}


}
	

int main(int argc, char* argv[])
{
	IplImage *src;
	char filepath[200];
	double *rel, *img, *src_data, xtmp, ytmp, tmp1, tmp2, tmp3, re, im;
	double Theta, sigma, Gamma, Lambda, Phi;        //公式中的5个参数
	int gabor_height, gabor_width, x, y;
	for (int m = 1; m < 1500; m++){
		sprintf(filepath, "F:\\MIT\\positive\\%d.bmp",m);
		src = cvLoadImage(filepath, CV_LOAD_IMAGE_GRAYSCALE);
		gabor_height = 10;
		gabor_width = 10;
		Gamma = 1.0;
		Lambda = 10.0;
		sigma = 100;
		Phi = 0;

		rel = (double *)malloc(sizeof(double)*gabor_width*gabor_height);//实数部分
		img = (double *)malloc(sizeof(double)*gabor_width*gabor_height);//虚数部分
		src_data = (double *)malloc(sizeof(double)*src->widthStep*src->height); //图像数据 

		for (int i = 0; i < src->height; i++)
		{
			for (int j = 0; j < src->widthStep; j++)
			{
				src_data[i*src->widthStep + j] = (unsigned char)src->imageData[i*src->widthStep + j];
				//printf("%f\n",src_data[i*src->widthStep+j]);
			}
		}

		//构造gabor函数
		for (int k = 0; k < N; k++)                   //定义N方向
		{
			Theta = PI*((double)k / N);      //0*PI/8,1*PI/8,2*PI/8,3*PI/8,4*PI/8,5*PI/8,6*PI/8,7*PI/8
			for (int i = 0; i < gabor_height; i++)    //定义模版大小
			{
				for (int j = 0; j < gabor_width; j++)
				{
					x = j - gabor_width / 2; //-5,-4,-3,-2,-1,0,+1,+2,+3,+4
					y = i - gabor_height / 2;//-5,-4,-3,-2,-1,0,+1,+2,+3,+4

					xtmp = (double)x*cos(Theta) + (double)y*sin(Theta);
					ytmp = (double)y*cos(Theta) - (double)x*sin(Theta);

					tmp1 = exp(-(pow(xtmp, 2) + pow(ytmp*Gamma, 2)) / (2 * pow(sigma, 2)));
					tmp2 = cos(2 * PI*xtmp / Lambda + Phi);
					tmp3 = sin(2 * PI*xtmp / Lambda + Phi);

					re = tmp1*tmp2;
					im = tmp1*tmp3;

					rel[i*gabor_width + j] = re;
					img[i*gabor_width + j] = im;
					//printf("%f,%f\n",re,im);
				}
			}
			//用不同方向的GABOR函数对图像滤波并保存图片
			m_filer(src_data, src->height, src->width, rel, img, 10, 10, k, m);
		}

		free(rel);
		free(img);
		free(src_data);
	}
	

	return 0;
}
