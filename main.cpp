#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()    //删除camer
{
	cout << "Built with OpenCV " << CV_VERSION << endl;

	VideoCapture capture(1);
	if (!capture.isOpened())
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	while (true)
	{
		Mat src, dst, temp;
		capture >> src;
		const char* INPUT_T = "input image";
		const char* OUTPUT_T = "result image";
		const char* match_t = "template match-demo";
		int match_method = TM_SQDIFF;
		bool flag = 0;
		if (!src.empty())
		{
			temp = imread("F:/code study/OpenCV4/opencvStudyFile/picture/黑块.jpg");
			//namedWindow(INPUT_T, WINDOW_AUTOSIZE);
			//namedWindow(OUTPUT_T, WINDOW_NORMAL);
			namedWindow(match_t, WINDOW_AUTOSIZE);
			//imshow(INPUT_T, temp);

			int width = src.cols - temp.cols + 1;
			int height = src.rows - temp.rows + 1;

			Mat result(width, height, CV_32FC1);

			matchTemplate(src, temp, result, match_method, Mat());
			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

			Point minLoc;
			Point maxLoc;
			double min, max;
			src.copyTo(dst);
			Point temLoc;
			minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
			if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
				temLoc = minLoc;
			}
			else {
				temLoc = maxLoc;
			}
			
			// 绘制矩形
			rectangle(dst, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
			//rectangle(result, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
			//imshow(OUTPUT_T, result);
			imshow(match_t, dst);
			cout << "x:" << temLoc.x/3.0 << "       y:" << temLoc.y/3.0 << endl;
			flag = 1;
				if (flag == 1)
				{

					//cout << "x:" <<temLoc.x<<"y:"<< temLoc.y << endl;


					//cin>>flag;
					flag = 0;
				}
		}

		if (waitKey(30) > 0)
		{
			break;
		}
	}

	return 0;
}

