#include <cstdlib>
#include <cstring>
#include <iostream>
#include "HCNetSDK.h"//����sdk
#include "plaympeg4.h"//���ſ�
#include <opencv2\opencv.hpp>
#include<time.h>

using namespace std;
using namespace cv;

LONG nPort = -1;

volatile int gbHandling = 3;
clock_t t1 = clock();
//����ص� ��ƵΪYUV����(YV12)��ת��ΪBGR����
void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{/*
	if (gbHandling)// �����֡ȡһ֡���ֲ���ȡͼ��������
	{
		gbHandling--;
		return;
	}
*/
	long lFrameType = pFrameInfo->nType;
	if (lFrameType == T_YV12)
	{
		Mat pImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
		Mat src(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, pBuf);
		cvtColor(src, pImg, CV_YUV2BGR_YV12);
		cout << clock() - t1 << endl;
		//  Sleep(-1);
		imshow("IPCamera", pImg);
		t1 = clock();
		waitKey(1);
	}
	//gbHandling = 3;

}


///ʵʱ���ص�
void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ

		if (!PlayM4_GetPort(&nPort))  //��ȡ���ſ�δʹ�õ�ͨ����
		{
			break;
		}
		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(nPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				break;
			}

			if (!PlayM4_OpenStream(nPort, pBuffer, dwBufSize,  1024 * 1024)) //�����ӿ�
			{
				break;
			}

			if (!PlayM4_Play(nPort, NULL)) //���ſ�ʼ
			{
				break;
			}
			if (!PlayM4_SetDecCallBack(nPort, DecCBFun))
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA:   //��������
		if (dwBufSize > 0 && nPort != -1)
		{
			if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
			{
				cout << "error" << PlayM4_GetLastError(nPort) << endl;
				break;
			}
		}
		break;
	//default: //��������
	//	if (dwBufSize > 0 && nPort != -1)
	//	{
	//		waitKey(1);
	//		if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))// ����
	//		{
	//			break;
	//		}
	//	}
	//	break;
	}
}


//void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
//{
//	char tempbuf[256] = { 0 };
//	switch (dwType)
//	{
//	case EXCEPTION_RECONNECT:    //Ԥ��ʱ����
//		printf("----------reconnect--------%d\n", time(NULL));
//		break;
//	default:
//		break;
//	}
//}

void main()
{

	//---------------------------------------
	// ��ʼ��
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);


	//---------------------------------------
	// ע���豸
	LONG lUserID;
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	lUserID = NET_DVR_Login_V30((char*)"192.168.8.34", 8000, (char*)"admin", (char*)"ferret123", &struDeviceInfo);
	if (lUserID < 0)
	{
		printf("Login error, %d\n", NET_DVR_GetLastError());
		NET_DVR_Cleanup();
		return;
	}

	//---------------------------------------
	//�����쳣��Ϣ�ص�����
	//NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

	//---------------------------------------
	//����Ԥ�������ûص�������
	LONG lRealPlayHandle;
	namedWindow("Mywindow", 0);
	cvNamedWindow("IPCamera", 0);
	
	HWND  h = (HWND)cvGetWindowHandle("Mywindow");// ��ȡ���ھ����һ�����ڶ���ı�ʶ��


	if (h == 0)
	{
		cout << "���ڴ���ʧ��" << endl;
	}


	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = h;         //��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	struPlayInfo.lChannel = 1;           //Ԥ��ͨ����
	struPlayInfo.dwStreamType = 0;       //0-��������1-��������2-����3��3-����4���Դ�����
	struPlayInfo.dwLinkMode = 0;         //0- TCP��ʽ��1- UDP��ʽ��2- �ಥ��ʽ��3- RTP��ʽ��4-RTP/RTSP��5-RSTP/HTTP

	lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, fRealDataCallBack, NULL);

	if (lRealPlayHandle < 0)
	{
		printf("NET_DVR_RealPlay_V40 error\n");
		printf("%d\n", NET_DVR_GetLastError());
		NET_DVR_Logout(lUserID);
		NET_DVR_Cleanup();
		return;
	}
	waitKey();

	//Sleep(-1);
	//---------------------------------------
	//�ر�Ԥ��
	NET_DVR_StopRealPlay(lRealPlayHandle);
	//ע���û�
	NET_DVR_Logout(lUserID);
	//�ͷ�SDK��Դ
	NET_DVR_Cleanup();

	return;
}



/*
���������ͼ��ÿ֡�ʴ��150ms��Ҳ���㲻��ʵʱ�Ե�Ҫ���������ô�� ����

*/