#ifndef HIK_VIDEOSDK_H
#define HIK_VIDEOSDK_H

#if (defined(WIN32) || defined(WIN64))
    #if defined(VIDEOSDK_EXPORTS)
        #define VIDEOSDK_DECLARE extern "C" __declspec(dllexport)
    #else
        #define VIDEOSDK_DECLARE extern "C" __declspec(dllimport)
    #endif // defined(VIDEOSDK_EXPORTS)

    #ifndef CALLBACK
        #define CALLBACK __stdcall
    #endif  // CALLBACK
#else
    #define ISCSDK_DECLARE extern "C"
    #ifndef CALLBACK
        #define CALLBACK
    #endif  // CALLBACK
#endif  // (defined(WIN32) || defined(WIN64))

#ifndef _IN_
    #define _IN_    // ��ʾ���
#endif

typedef long long VIDEO_INT64;  // ͳһ8�ֽ���������

////////////////////////// �����붨�� ////////////////////////////////
#define VIDEO_ERR_FAIL            -1     // ʧ��
#define VIDEO_ERR_SUCCESS          0     // �ɹ�
#define VIDEO_ERR_PARAM            1     // ��������
#define VIDEO_ERR_INVALID_POINTER  2     // ��ָ��
#define VIDEO_ERR_NOT_INIT         3     // δ��ʼ��
#define VIDEO_ERR_INVALID_HANDLE   4     // �����Ч
#define VIDEO_ERR_CREATE_INSTANCE  5     // ����ʵ��ʧ��
#define VIDEO_ERR_APPLY_MEMORY     6     // �����ڴ�ʧ��
#define VIDEO_ERR_NET_EXCEPTION    7     // �����쳣
#define VIDEO_ERR_NOT_SUPPORT      8     // ��֧�֣���ֻȡ��ʱץͼ��rtp����ѯ��ǰ����ʱ���
#define VIDEO_ERR_SET_CALLBACK     9     // �ص�����ʧ��
#define VIDEO_ERR_START_STREAM     10    // ȡ���쳣
#define VIDEO_ERR_STOP_STREAM      11    // ֹͣȡ���쳣
#define VIDEO_ERR_START_PLAY       12    // �����쳣
#define VIDEO_ERR_STOP_PLAY        13    // ֹͣ�����쳣
#define VIDEO_ERR_TIMESTAMP        14    // ʱ�����Ч
#define VIDEO_ERR_SOUND            15    // ������ش���
#define VIDEO_ERR_SNAP             16    // ץ��ʧ��
#define VIDEO_ERR_GETPLAYTIME      17    // ��ѯ����ʱ���ʧ��
#define VIDEO_ERR_INNER            18    // �ڲ�����
#define VIDEO_ERR_PLAYCTRL         19    // ���ſ���ʧ��
#define VIDEO_ERR_OPER_ORDER       20    // �������򲻶ԣ���δ�������ͻ�ȡ����������������

////////////////////////// �ص����� ///////////////////////////////
// �����ص�
// i64PlayHandle��Ԥ����طŽӿڷ��صľ��
// iStreamDataType�������������ͣ�0-����ͷ 1-�������� 2-�������
// pDataArray�����������飨�赱�ɶ�����������������
// iDataLen�������ݳ���
// pUserData���û�����
typedef void(CALLBACK * pfnStreamCallback)(VIDEO_INT64 i64PlayHandle, int iStreamDataType, const char* pDataArray, int iDataLen, void* pUserData);

// ȡ����������Ϣ�ص�
// i64PlayHandle��Ԥ����طŽӿڷ��صľ��
// iMsg����Ϣ���ͣ�1-���ſ�ʼ 2-���Ž�������ƵԤ���޴���Ϣ�� 3-�����쳣 10-ȡ����ʼ 11-ȡ������ 12-ȡ���쳣
typedef void(CALLBACK * pfnMsgCallback)(VIDEO_INT64 i64PlayHandle, int iMsg, void* pUserData);

// YUV���ݻص�
// i64PlayHandle��Ԥ����طŽӿڷ��صľ��
// pDataArray��YUV�������飨�赱�ɶ�����������������
// iDataLen�������ݳ���
// iWidth��ͼ����
// iHeight��ͼ��߶�
// iFrameType��ͼ��YUV���ͣ�ĿǰΪYV12��ֵΪ3��
// iTimeStamp��ʱ���
// pUserData���û�����
typedef void(CALLBACK* pfnDecodedDataCallback)(VIDEO_INT64 i64PlayHandle, const char* pDataArray, int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData);

////////////////////////// �ṹ�嶨�� //////////////////////////////////
// ��������ṹ��
typedef struct stPlayReq
{
    int iHardWareDecode;  // �Ƿ���GPUӲ�� 0-������ 1-�������������Ӳ�⣬�����Կ���֧�ֵȵ��´���SDK�ڲ��Զ��л�����⣬��������ر����󣬽��鲻����Ӳ�⣩
    pfnStreamCallback fnStream;              // �������ݻص�
    pfnMsgCallback fnMsg;                    // ȡ����������Ϣ�ص�
    pfnDecodedDataCallback fnDecodedStream;  // ������YUV���ݻص�
    void* pUserData;                         // �û�����
    char szResevre[64];                      // ��������
}VIDEO_PLAY_REQ, *PVIDEO_PLAY_REQ;

////////////////////////// �ӿڶ��� /////////////////////////////
// SDK��ʼ��
// pszEvn��������������NULL����
// ��ע����һ�μ��ɣ���ʼ���ɹ�������ظ���ֱ�ӷ��سɹ�
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_Init(_IN_ const char* pszEvn);

// SDK����ʼ��
// ��ע����һ�μ��ɣ�����ʼ���ɹ�������ظ���ֱ�ӷ��سɹ�
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_Fini();

// ��ƵԤ����֧��ȡʵʱ�����ص�ȡ���벥�ŵ���Ϣ���Լ��ص�YUV���ݣ���Ҫ�������������ָ����
// pszUrl��Ԥ��URL
// hWnd����ƵԤ����Windows���ھ��
// pstPlayReq��������������������������ṹ�嶨��
// ��ע��Ԥ���޲��Ž�����Ϣ
// �ɹ����ش���0��Ԥ�������ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_StartPreview(_IN_ const char* pszUrl, _IN_ void* hWnd, _IN_ PVIDEO_PLAY_REQ pstPlayReq);

// ֹͣԤ����ֹͣȡ����ֹͣ�ص���Ϣ��ֹͣ�ص�YUV���ݣ�
// i64PlayHandle��Ԥ���������Դ��Video_StartPreview����ֵ
// ��ע��Ԥ���޲��Ž�����Ϣ������ֹͣԤ���ӿڳɹ��Ϳ�����Ϊ�ǲ��Ž�����
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_StopPreview(_IN_ VIDEO_INT64 i64PlayHandle);

// ����¼��طţ�֧��ȡ����¼�������ص�ȡ���벥�ŵ���Ϣ���Լ��ص�YUV���ݣ���Ҫ�������������ָ����
// pszUrl���ط�URL
// hWnd������¼��طŵ�Window���ھ��
// i64StartTimeStamp����ѯ¼��ʱ�Ŀ�ʼʱ�������λ����
// i64EndTimeStamp����ѯ¼��ʱ�Ľ���ʱ�������λ����
// pstPlayReq�����������������ϸ��������ṹ�嶨��
// �ɹ����ش���0�Ļطž����ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_StartPlayback(_IN_ const char* pszUrl, _IN_ void* hWnd, _IN_ VIDEO_INT64 i64StartTimeStamp, _IN_ VIDEO_INT64 i64EndTimeStamp, _IN_ PVIDEO_PLAY_REQ pstPlayReq);

// ֹͣ����¼��طţ�ֹͣȡ����ֹͣ�ص���Ϣ��ֹͣ�ص�YUV���ݣ�
// i64PlayHandle������¼��طž������Դ��Video_StartPlayback�ӿ�
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_StopPlayback(_IN_ VIDEO_INT64 i64PlayHandle);

// ����¼�񲥷ſ���
// i64PlayHandle������¼��طž������Դ��Video_StartPlayback�ӿ�
// iCtrlType���������ͣ�0-��ͣ���� 1-�ָ����� 2-��λ���� 3-���ٲ���
// i64Param�����ſ��Ʋ�������iCtrlTypeΪ0��1ʱ��Ч����iCtrlTypeΪ2ʱ���ò���Ϊ��λ����ʱ�������iCtrlTypeΪ3ʱ���ò���Ϊ���٣������ٶȴ�������ֱ�Ϊ��-16��-8��-4��-2��1��2��4��8��16��
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_PlayCtrl(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iCtrlType, _IN_ VIDEO_INT64 i64Param);

// ��ѯ����¼��طŵ�ǰ����ʱ�������λ���룩
// i64PlayHandle������¼��طž������Դ��Video_StartPlayback�ӿ�
// �ɹ�����ʱ�����ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_GetCurrentPlayTime(_IN_ VIDEO_INT64 i64PlayHandle);

// ����ץͼ��֧����ƵԤ��������¼��طŲ���ץͼ��
// i64PlayHandle����ƵԤ��������¼��طž������Դ��Video_StartPreview��Video_StartPlayback�ӿ�
// pszAbsoluteFile��ץͼͼƬ�ļ�����·�����ƣ�ֻ֧�֡�bmp���͡�jpg����׺���硰D:\\SnapShot\test.bmp������D:\\SnapShot\test.jpg��
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_PlaySnap(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ const char* pszAbsoluteFile);

// ����ʽ�������ƣ���֧�ִ򿪶�·��������
// i64PlayHandle����ƵԤ��������¼��طž������Դ��Video_StartPreview��Video_StartPlayback�ӿ�
// iCtrlType���������ͣ�0-������ 1-�ر�����
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_SoundCtrl(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iCtrlType);

// ��ȡ����
// i64PlayHandle����ƵԤ��������¼��طž������Դ��Video_StartPreview��Video_StartPlayback�ӿ�
// �ɹ���������ֵ��ȡֵ��ΧΪ[0 100]����ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_GetVolume(_IN_ VIDEO_INT64 i64PlayHandle);

// ��������
// i64PlayHandle����ƵԤ��������¼��طž������Դ��Video_StartPreview��Video_StartPlayback�ӿ�
// iVolume������ֵ����ΧӦ��[0 100]�����������Χ��SDK�ڲ�ʹ������������Сֵ�����
// �ɹ�����VIDEO_ERR_SUCCESS��ʧ�ܷ���VIDEO_ERR_FAIL��ʧ����ͨ��Video_GetLastError��ѯ������
VIDEOSDK_DECLARE int CALLBACK Video_SetVolume(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iVolume);

// ��ȡ������
// ���ش�����ֵ
VIDEOSDK_DECLARE int CALLBACK Video_GetLastError();

#endif  // HIK_VIDEOSDK_H