#pragma once

#include <opencv2/opencv.hpp> 
#include <iostream>  
#include <string> 

using namespace std;
using namespace cv;

namespace OpencvApi{

	static int HSV[11][6] = {
		0, 180, 0, 255, 0, 46,	//black
		0, 180, 0, 43, 46, 220,	//grey
		0, 180, 0, 30, 221, 255,//white

		0, 10, 43, 255, 46, 255,	//red
		156, 180, 43, 255, 46, 255, //red

		11, 25, 43, 255, 46, 255,	//orange
		26, 34, 43, 255, 46, 255,	//yellow
		35, 77, 43, 255, 46, 255,	//green
		78, 99, 43, 255, 46, 255,	//cyan
		100, 124, 43, 255, 46, 255, //blue
		125, 155, 43, 255, 46, 255	//purple
	};
	

	class ColorExtract{	
	public:	
		void get()
		{
			Mat matSrc = imread("color.BMP", IMREAD_UNCHANGED);
			Mat matHsv;
			cvtColor(matSrc, matHsv, COLOR_BGR2HSV);

			vector<int> colorVec;
			colorVec.push_back(matHsv.at<uchar>(0, 0));
			colorVec.push_back(matHsv.at<uchar>(0, 1));
			colorVec.push_back(matHsv.at<uchar>(0, 2));

			if ((colorVec[0] >= 0 && colorVec[0] <= 180)
				&& (colorVec[1] >= 0 && colorVec[1] <= 255)
				&& (colorVec[2] >= 0 && colorVec[2] <= 46)){

				cout << "黑" << endl;
			}
			else if ((colorVec[0] >= 0 && colorVec[0] <= 180)
				&& (colorVec[1] >= 0 && colorVec[1] <= 43)
				&& (colorVec[2] >= 46 && colorVec[2] <= 220)){

				cout << "灰" << endl;
			}
			else if ((colorVec[0] >= 0 && colorVec[0] <= 180)
				&& (colorVec[1] >= 0 && colorVec[1] <= 30)
				&& (colorVec[2] >= 221 && colorVec[2] <= 255)){

				cout << "白" << endl;
			}
			else if (((colorVec[0] >= 0 && colorVec[0] <= 10) || (colorVec[0] >= 156 && colorVec[0] <= 180))
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "红" << endl;

			}
			else if ((colorVec[0] >= 11 && colorVec[0] <= 25)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "橙" << endl;
			}
			else if ((colorVec[0] >= 26 && colorVec[0] <= 34)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "黄" << endl;
			}
			else if ((colorVec[0] >= 35 && colorVec[0] <= 77)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "绿" << endl;
			}
			else if ((colorVec[0] >= 78 && colorVec[0] <= 99)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "青" << endl;
			}
			else if ((colorVec[0] >= 100 && colorVec[0] <= 124)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "蓝" << endl;
			}
			else if ((colorVec[0] >= 125 && colorVec[0] <= 155)
				&& (colorVec[1] >= 43 && colorVec[1] <= 255)
				&& (colorVec[2] >= 46 && colorVec[2] <= 255)){

				cout << "紫" << endl;
			}
			else{

				cout << "未知" << endl;
			}

			getchar();


		}

		void getOne(int HSV[], int flag)
		{
			Mat imgOriginal = imread("cable.jpg", IMREAD_COLOR);

			int m = imgOriginal.rows;
			int n = imgOriginal.cols;
			Rect rect(0, 0, n*0.5, m*1);
			Mat temp(imgOriginal, rect);
			namedWindow("roi");
			imshow("roi", temp);


			Mat imgHSV;
			vector<Mat> hsvSplit;
			cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

			split(imgHSV, hsvSplit);
			equalizeHist(hsvSplit[2], hsvSplit[2]);
			merge(hsvSplit, imgHSV);

			Mat imgThresholded;
			
			inRange(imgHSV, Scalar(HSV[0], HSV[2], HSV[4]), Scalar(HSV[1], HSV[3], HSV[5]), imgThresholded);
			imshow("Thresholded1", imgThresholded);
			
			Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
			if (flag)
			{		
				morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
			}
			else
			{
				dilate(imgThresholded, imgThresholded, element);
			}
									
			imshow("Thresholded2", imgThresholded);
			imshow("Original", imgOriginal);
			
			vector<vector<Point> > contours_out;
			vector<Vec4i> hierarchy;
			findContours(imgThresholded, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

			for (size_t k = 0; k < contours_out.size(); k++)
			{
				Rect ret1 = boundingRect(Mat(contours_out[k]));

				int avgX = (ret1.x + ret1.x + ret1.width)/2; 

				int avgY = (ret1.y + ret1.y + ret1.height)/2;

				cout << "x:" << avgX << "   y:" << avgY << endl;
			}

			cout << " ****** " << endl;

			waitKey(1);
		
		}
	
		bool checkColor(int HSV[],QString path){

			Mat imgOriginal = imread(path.toStdString(), IMREAD_COLOR);

			Mat imgHSV;
			vector<Mat> hsvSplit;
			cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

			split(imgHSV, hsvSplit);
			equalizeHist(hsvSplit[2], hsvSplit[2]);
			merge(hsvSplit, imgHSV);

			Mat imgThresholded;

			inRange(imgHSV, Scalar(HSV[0], HSV[2], HSV[4]), Scalar(HSV[1], HSV[3], HSV[5]), imgThresholded);
			imshow("Thresholded1", imgThresholded);

			Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
			
			morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
			//dilate(imgThresholded, imgThresholded, element);
			
			imshow("Thresholded2", imgThresholded);
			imshow("Original", imgOriginal);

			vector<vector<Point> > contours_out;
			vector<Vec4i> hierarchy;
			findContours(imgThresholded, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

			waitKey(1);

			if (contours_out.size() > 0)
			{
				return true;
			}
			
			return false;
		}	
};

	class CableExtract
	{
	public:
		void get()
		{
			/*
			Mat src_all;

			Mat src = imread("cable.jpg", IMREAD_COLOR);

			//从src中截取一个区域,等比例缩放
			int cor = src.cols * 0.2;
			float ratio = src.rows / src.cols;
			Mat srctemp(src, Rect(cor, (int)(cor*ratio), src.cols - 2 * cor, src.rows - 2 * (int)(cor*ratio)));
			Size dsize = Size(src.cols, src.rows);
			resize(srctemp, src_all, dsize);

			int position = 50;
			src_all.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
			Rect tRect(0, position, 192, position + 20);
			Mat roi(bgr, tRect);
			imwrite("roi.jpg", roi);

			cvtColor(roi, hsv, CV_BGR2HSV);

			float hh[1920] = { 0 };
			float ss[1920] = { 0 };
			float vv[1920] = { 0 };
			float var[1920] = { 0 };
			for (int i = 0; i < hsv.size().width; i++)
			{
				float h, s, v;
				h = 0;
				s = 0;
				v = 0;
				for (int j = 0; j < 2; j++)   //hsv.size().height
				{
					Vec3f vec3f = hsv.at<Vec3f>(j, i);
					h += vec3f[0];
					s += vec3f[1];
					v += vec3f[2];
				}
				hh[i] = h;
				ss[i] = s * 255;
				vv[i] = v * 255;
			}



			float x[1920] = { 0 };
			float y[1920] = { 0 };
			float z[1920] = { 0 };
			float xx[1920] = { 0 };
			float yy[1920] = { 0 };
			float zz[1920] = { 0 };
			float sum[1920] = { 0 };
			for (int i = 3; i < 1917; i++)
			{
				x[i] = abs(hh[i + 3] - hh[i - 3]);
				xx[i] = (hh[i + 3] + hh[i + 2] + hh[i + 1] + hh[i - 3] + hh[i - 2] + hh[i - 1] - 6 * hh[i]);
				y[i] = (ss[i + 3] + ss[i + 2] + ss[i + 1] + ss[i - 3] + ss[i - 2] + ss[i - 1] - 6 * ss[i]);
				if (ss[i] < 50) y[i] = 0;
				if (vv[i] < 100) y[i] = 1;

				yy[i] = abs(ss[i + 3] - ss[i - 3]);
				if (ss[i] < 50) yy[i] = 0;

				z[i] = (vv[i + 3] + vv[i + 2] + vv[i + 1] + vv[i - 3] + vv[i - 2] + vv[i - 1] - 6 * vv[i]);
				zz[i] = abs(vv[i + 3] - vv[i - 3]);

				sum[i] = abs(x[i] * xx[i] * y[i] * yy[i] * z[i] * zz[i]);

				if (sum[i] > 400000000)
					sum[i] = 400000000;
				sum[i] /= 1000000000;
				sum[i] *= 25;
				if (sum[i] < 10) sum[i] = 0;
			}

			int count = 0;
			int tempcount = 0;
			int left[50] = { 0 };
			int right[50] = { 0 };
			for (int i = 1; i < 1920; i++)
			{
				if (sum[i] - sum[i - 1] < 0 && sum[i] == 0)
				{
					tempcount = count;
					left[tempcount] = i;
				}

				if (sum[i] - sum[i - 1] > 0 && sum[i - 1] == 0)
				{
					right[tempcount] = i;
					count++;
				}
			}

			*/


			//使用欧式距离的方法判断颜色
			struct colorspace
			{
				string colorname;
				float  h;
				float  s;
				float  v;
			};

			//需要事先标定
			colorspace cs[11] = {
				//颜色	  h    s    v
				{ "黑色", 236, 0, 0 },
				{ "白色", 236, 0, 1 },
				{ "灰色", 236, 0, 0.5 },
				{ "褐色", 10, 0.47, 0.30 },
				{ "橘色", 19, 0.73, 0.68 },
				{ "黄色", 56, 0.69, 0.65 },
				{ "绿色", 160, 0.95, 0.34 },
				{ "蓝色", 226, 0.98, 0.45 },
				{ "紫色", 285, 0.50, 0.31 },
				{ "红色", 340, 0.83, 0.66 },
				{ "背景", 105, 0.05, 0.54 } };

			//对框选区域进行颜色识别	
			/*
			for (int c = 0; c < 10; c++)
			{
				float h, s, v;
				h = 0;
				s = 0;
				v = 0;
				for (int i = leftborder.at(c); i < rightborder.at(c); i++)
				{
					for (int j = 0; j < 5; j++)   //hsv.size().height
					{
						Vec3f vec3f = hsv.at<Vec3f>(j, i);
						h += vec3f[0];
						s += vec3f[1];
						v += vec3f[2];
					}
				}


				h = h / (20 * (rightborder.at(c) - leftborder.at(c)));
				s = s / (20 * (rightborder.at(c) - leftborder.at(c)));
				v = v / (20 * (rightborder.at(c) - leftborder.at(c)));
				cout << h << " " << s << " " << v << endl;

				int minindex = 0;
				int mindistance = 40;

				for (int i = 0; i < 11; i++)       //背景不参与运算
				{
					int distance = (h - cs[i].h)*(h - cs[i].h) +
						(s - cs[i].s)*(s - cs[i].s) * 129 +
						(v - cs[i].v)*(v - cs[i].v) * 129;
					if (distance < mindistance)
					{
						minindex = i;
						mindistance = distance;
					}
				}
				
				cout << cs[minindex].colorname << endl;
			}
			*/

		}
	};

};

