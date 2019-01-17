#ifndef _HIK_VIDEOPLUGIN_H_
    #define _HIK_VIDEOPLUGIN_H_
#endif

# if defined(VIDEOPLUGIN_LIB)
#  define VIDEOPLUGIN_EXPORT extern "C" __declspec(dllexport)
# else
#  define VIDEOPLUGIN_EXPORT extern "C" __declspec(dllimport)
# endif

#ifndef CALLBACK
    #define CALLBACK __stdcall
#endif  // CALLBACK

#ifndef _IN_
    #define _IN_    // ��ʾ���
#endif

#define VIDEOPLUGIN_SUCCESS 0   // �ɹ�
#define VIDEOPLUGIN_FAIL    -1  // ʧ��


// ��Ϣ�ص�
typedef void(_stdcall *VideoPlugin_MessageCallback)(void* pPluginInstance, char* pRspJsonMsg, void* pUserData);


// ����ʵ��
// ��Σ�
//     pParentWndHandle�������ھ��
// ����ֵ��ʵ��ָ��
VIDEOPLUGIN_EXPORT void* VideoPlugin_CreatePluginInstance(void* pParentWndHandle);

// ����ʵ��
// ��Σ�
//     pPluginInstance��ʵ��ָ��
// ����ֵ����
VIDEOPLUGIN_EXPORT void VideoPlugin_DestroyPluginInstance(_IN_ void* pPluginInstance);

// ��ȡ���ھ��
// ��Σ�
//     pPluginInstance��ʵ��ָ��
// ����ֵ����NULLΪ�ɹ� NULLΪʧ�� 
VIDEOPLUGIN_EXPORT void* VideoPlugin_GetWindowHandle(_IN_ void* pPluginInstance);

// ͨ������ӿ�
// ��Σ�ʵ��ָ��
//      pPluginInstance��ʵ��ָ��
//      pszJsonRequest��json��ʽ�����ģ�֧�ֵĹ����Լ�ʹ�÷�ʽ�����ͨ������ӿڹ���֧�֡�
// ����ֵ��json��ʽ���ģ���ʽ������棬ע����Ҫ���÷��ͷ��ڴ�
VIDEOPLUGIN_EXPORT char* VideoPlguin_GerneralRequest(_IN_ void* pPluginInstance, _IN_ const char* pszJsonRequest);

// ��Ϣ�ص����ýӿ�
// ��Σ�ʵ��ָ��
//      pPluginInstance��ʵ��ָ��
//      fnMsgCB���ص�������ַ
//      pUserData���û�����
// ����ֵ��0-�ɹ� -1-ʧ��
// ��ע���ݲ�����
VIDEOPLUGIN_EXPORT int VideoPlugin_SetMessageCallback(_IN_ void* pPluginInstance, VideoPlugin_MessageCallback pfnMsgCB, void* pUserData);

/////////////////////////////// ͨ������ӿ�(VideoPlguin_RequestInterface)����ֵ///////////////////////////////////////////
/*
{
errorCode: 0,                       // 0 - �ɹ� -1 - ʧ��
errorMessage: "",                   // �������������ֶβ�һ����
data: ""                            // ���ݣ����ֶβ�һ����
}
*/

///////////////////////////////// ͨ������ӿ�(VideoPlguin_RequestInterface)����֧�� /////////////////////////////////
/*
1�����pszJsonRequestΪjson���ĸ�ʽ�����£�
{
funcName: "funcName",   // ���ܱ�ʶ
argument: "argument"    // ���������������json�ַ�����Ҳ���Բ����ڸ��ֶΣ�����Ҫ�������Ĺ��ܣ�
}

2��֧�ֵĹ������£�ע������json����������Ϊʾ�����ݣ���ʵ���г��룩��
1> ��ʼ��
���ܱ�ʶ��funcName����"init",
������argument����
{
appkey: "afsgnhmj34567dgh",       // API�����ṩ��appkey������
secret: "vgkk3g0jaoj0igoigj",     // API�����ṩ��secret������
ip: "10.33.31.4",                 // API����IP��ַ������
port: 800,                        // API���ض˿ڣ�����
playMode: 0,                      // ����ģʽ��������ʾԤ�����ǻطŽ��棩��0-Ԥ�� 1-����¼�񲥷ţ�����Ĭ��Ԥ��
snapDir: "D:\\SnapDir",           // ץͼ�洢·��������ʹ��Ĭ��·��
layout: "2x2",                    // playMode�Ĳ��֣�����ʹ��Ĭ�ϲ���
encryptedFields: "appkey,secret"  // �����˵��ֶ�
}

2> ����ʼ��
���ܱ�ʶ��funcName����"uninit",
������argument�������ô�

3> ��ʼԤ��
���ܱ�ʶ��funcName����"startPreview",
������argument����
{
cameraIndexCode: "afsgnhmj34567dgh",   // ��ص���
streamMode: 0,                    // ����������ʶ��0-������ 1-������
gpuMode: 0,                       // �Ƿ���GPUӲ�⣬�����鿪����0-������ 1-����
transMode, 1                      // ����Э�� 1-TCP 0-UDP
}

4> ��ʼ�ط�
���ܱ�ʶ��funcName����"startPlayback",
������argument����
{
cameraIndexCode: "afsgnhmj34567dgh",   // ��ص���
startTimeStamp: "10237898985",    // ¼���ѯ��ʼʱ�������λ����
endTimeStamp: "10237899985",      // ¼���ѯ����ʱ�������λ����
recordLocation: 0,                // ¼��洢���ͣ��Ǳ�������ѯ���У�0-���Ĵ洢 1-�豸�洢
transMode: 0,                     // ����Э�� 1-TCP 0-UDP
gpuMode: 0,                       // �Ƿ���GPUӲ�⣬�����鿪����0-������ 1-����
}

5> ֹͣȫ��Ԥ��
���ܱ�ʶ��funcName����"stopAllPreview",
������argument�������ô�

6> ֹͣȫ���ط�
���ܱ�ʶ��funcName����"stopAllPlayback",
������argument�������ô�

7> ��ȡRSA��Կ
���ܱ�ʶ��funcName����"getRSAPubKey",
������argument����
{
keyLength: 1024,   // RSA��Կ���ȣ���ѡ1024��2048bit��ע����䷽ʽΪRSA_PKCS1_PADDING
}

*/
