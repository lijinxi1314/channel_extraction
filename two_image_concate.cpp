
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <iostream> 
using namespace cv;
using namespace std;
#define DIR "c:\\users\\lijinxi\\desktop\\new"
int main() {
	Mat img = imread("c:\\users\\lijinxi\\desktop\\new\\aachen_000116_000019_leftimg8bit.png");
	
	char path1[100];
	char path2[100];
	for (int i = 1; i < 25; i++) {
		sprintf(path1, "%s\\%d.jpg", DIR, i);
		sprintf(path2, "%s\\new_%d.jpg", DIR, i);
		Mat img2 = imread(path1);
		Mat img3;
		Mat img4;
		cv::resize(img2, img3, Size(2048, 1024));
		addWeighted(img, 0.6, img3, 0.4, 0., img4);
	//	imshow("hua", img);
		imwrite(path2, img4);

	}
	//
	////imshow("hua", img);
	waitKey();
}





////
//////int main()
//////{
//////	//【0】定义相关变量 
//////	Mat ac, ahand;
//////	//【1】读取原始图像并检查图像是否读取成功  
//////	ac = imread("C:\\Users\\lijinxi\\Desktop\\image\\aachen_000116_000019_leftImg8bit.png");
//////	ahand = imread("C:\\Users\\lijinxi\\Desktop\\image\\a130.png");
//////	//if (ahand.empty() && ac.empty())		//检验两幅图像是否同时存在
//////	//{
//////	//	cout << "error\n";
//////	//	return -1;
//////	//}
//////	imshow("1ac", ac);	
//////
//////	//imshow("2ahand", ahand);
//////	//【4】调整ahand的大小与ac的大小一致，融合函数addWeighted()要求输入的两个图形尺寸必须相同  
//////	resize(ahand, ahand, Size(ac.cols, ac.rows));
//////	//【5】利用addWeighted()函数对两幅图像进行融合
//////	//addWeighted(ac, 0.6, ahand, 0.4, 0., ac); //最后融合效果显示在ac图像上
//////	//										  /*
//////	//										  若不想毁坏原始ac图像，也可建立一个与ac图像类型尺寸一样的新图像，将融合后的图像保存到上面。
//////	//										  建立方法：
//////	//										  Mat newImage(ac.size(), ac.type());	//newImage与ac类型尺寸相同
//////	//										  */
//////	namedWindow("con");
////////	imshow("con",ac);
//////	
//////	waitKey();
//////	return 0;
//////
//////}
