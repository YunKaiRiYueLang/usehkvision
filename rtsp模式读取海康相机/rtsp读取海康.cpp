/*该相机支持rtsp协议,不用海康的sdk也可以获取解码图像*/
/*使用queue保证图像的处理顺序FIFO,处理的速度总是需要比传送的速度块*/

#include<opencv2/opencv.hpp>
#include<time.h>
#include<thread>
#include<queue>



using cv::Mat;
using std::queue;


cv::Mat frame;
queue<cv::Mat> queuesrc;

void secondthread()
{
	for(;;)
	{

		if (queuesrc.empty())		{continue;}		/*检查stack对象是否为空*/
		Mat image = queuesrc.front();
		queuesrc.pop();
		if (image.data == NULL) { continue; }		/*检查图像是否为空*/

		cv::resize(image, image, cv::Size(320, 240));
		cv::imshow("test", image);
		if (cv::waitKey(1)==27)
		{
			exit(0);
		}
		std::cout << "test" << std::endl;
	}
}

int main()
{
	cv::VideoCapture HkCamera("rtsp://admin:a1234567@192.168.8.6/h256/ch1/sub/av_stream");
	double t1 = clock();
	int num = 100;
	int index = 1;
	bool firststart = true;


	while (true)
	{
		HkCamera >> frame;
		queuesrc.push(frame);
		cv::imshow("hkcamera", frame);
		if (firststart)
		{
			firststart = false;
			std::thread process(secondthread);
			process.detach();
		}
		cv::waitKey(10);
		index++;
		if (index == 100)
		{
			std::cout << "获取100帧用时" << clock() - t1 << std::endl;
			std::cout << frame.size() << std::endl;
			t1 = clock();
			index = 0;
		}
	}
}