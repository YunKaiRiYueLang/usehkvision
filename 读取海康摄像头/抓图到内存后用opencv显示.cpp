/*
Opencv读取海康dvr相机（利用SDK里面的NET_DVR_CaptureJPEGPicture_NEW进行视频抓图）
date: 2019-01-07
purpose:(test) read hk camera
author:wbj
*/

#include <cstdio>  
#include <iostream>  
#include <ctime>  
#include "HCNetSDK.h"  
#include <opencv2/opencv.hpp>
#include<time.h>

using namespace cv;
using namespace std;


//typedef HWND (WINAPI *PROCGETCONSOLEWINDOW)();  
//PROCGETCONSOLEWINDOW GetConsoleWindow;  

int main(int argc, char * argv[])
{
	//---------------------------------------  
	// 初始化  
	NET_DVR_Init();
	//设置连接时间与重连时间  
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	// 注册设备  
	LONG lUserID;
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	lUserID = NET_DVR_Login_V30((char*)"192.168.8.34", 8000, (char*)"admin", (char*)"ferret123", &struDeviceInfo);
	if (lUserID < 0)
	{
		printf("Login error, %d\n", NET_DVR_GetLastError());
		NET_DVR_Cleanup();
		return -1;
	}

	LPNET_DVR_JPEGPARA JpegPara = new NET_DVR_JPEGPARA;
	JpegPara->wPicQuality = 0;
	JpegPara->wPicSize = 9;

	char * Jpeg = new char[200 * 1024];
	DWORD len = 200 * 1024;
	LPDWORD Ret = 0;

	if (!NET_DVR_SetCapturePictureMode(BMP_MODE))
	{
		cout << "Set Capture Picture Mode error!" << endl;
		cout << "The error code is " << NET_DVR_GetLastError() << endl;
	}
	// 截取一张图，本地保存为1111.jpg;
	bool capture = NET_DVR_CaptureJPEGPicture(lUserID,1,JpegPara,(char*)"1111.jpg");  
	vector<char>data(200 * 1024);
	namedWindow("camera", WINDOW_NORMAL);
	while (1)
	{

		clock_t t1 = clock();
		bool capture = NET_DVR_CaptureJPEGPicture_NEW(lUserID, 1, JpegPara, Jpeg, len, Ret);//单帧数据捕获并保存成 JPEG 
		if (!capture)
		{
			printf("Error: NET_DVR_CaptureJPEGPicture_NEW = %d", NET_DVR_GetLastError());
			return -1;
		}
		for (int i = 0; i < 200 * 1024; i++)
			data[i] = Jpeg[i];
		Mat img = imdecode(Mat(data), 1);
		cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	
	}
	return 0;
}


/*
这种方法取一张图要两三百毫秒，实时性是不用想了。release下190ms左右

*/