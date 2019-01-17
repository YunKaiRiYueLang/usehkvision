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
    #define _IN_    // 表示入参
#endif

typedef long long VIDEO_INT64;  // 统一8字节数据类型

////////////////////////// 错误码定义 ////////////////////////////////
#define VIDEO_ERR_FAIL            -1     // 失败
#define VIDEO_ERR_SUCCESS          0     // 成功
#define VIDEO_ERR_PARAM            1     // 参数错误
#define VIDEO_ERR_INVALID_POINTER  2     // 空指针
#define VIDEO_ERR_NOT_INIT         3     // 未初始化
#define VIDEO_ERR_INVALID_HANDLE   4     // 句柄无效
#define VIDEO_ERR_CREATE_INSTANCE  5     // 创建实例失败
#define VIDEO_ERR_APPLY_MEMORY     6     // 申请内存失败
#define VIDEO_ERR_NET_EXCEPTION    7     // 网络异常
#define VIDEO_ERR_NOT_SUPPORT      8     // 不支持，如只取流时抓图，rtp流查询当前播放时间戳
#define VIDEO_ERR_SET_CALLBACK     9     // 回调设置失败
#define VIDEO_ERR_START_STREAM     10    // 取流异常
#define VIDEO_ERR_STOP_STREAM      11    // 停止取流异常
#define VIDEO_ERR_START_PLAY       12    // 解码异常
#define VIDEO_ERR_STOP_PLAY        13    // 停止解码异常
#define VIDEO_ERR_TIMESTAMP        14    // 时间戳无效
#define VIDEO_ERR_SOUND            15    // 声音相关错误
#define VIDEO_ERR_SNAP             16    // 抓拍失败
#define VIDEO_ERR_GETPLAYTIME      17    // 查询播放时间戳失败
#define VIDEO_ERR_INNER            18    // 内部错误
#define VIDEO_ERR_PLAYCTRL         19    // 播放控制失败
#define VIDEO_ERR_OPER_ORDER       20    // 操作次序不对（如未打开声音就获取音量或设置音量）

////////////////////////// 回调定义 ///////////////////////////////
// 码流回调
// i64PlayHandle：预览或回放接口返回的句柄
// iStreamDataType：码流数据类型，0-码流头 1-码流数据 2-结束标记
// pDataArray：流数据数组（需当成二进制数据来解析）
// iDataLen：流数据长度
// pUserData：用户数据
typedef void(CALLBACK * pfnStreamCallback)(VIDEO_INT64 i64PlayHandle, int iStreamDataType, const char* pDataArray, int iDataLen, void* pUserData);

// 取流、播放消息回调
// i64PlayHandle：预览或回放接口返回的句柄
// iMsg：消息类型，1-播放开始 2-播放结束（视频预览无此消息） 3-播放异常 10-取流开始 11-取流结束 12-取流异常
typedef void(CALLBACK * pfnMsgCallback)(VIDEO_INT64 i64PlayHandle, int iMsg, void* pUserData);

// YUV数据回调
// i64PlayHandle：预览或回放接口返回的句柄
// pDataArray：YUV数据数组（需当成二进制数据来解析）
// iDataLen：流数据长度
// iWidth：图像宽度
// iHeight：图像高度
// iFrameType：图像YUV类型（目前为YV12，值为3）
// iTimeStamp：时间戳
// pUserData：用户数据
typedef void(CALLBACK* pfnDecodedDataCallback)(VIDEO_INT64 i64PlayHandle, const char* pDataArray, int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData);

////////////////////////// 结构体定义 //////////////////////////////////
// 播放请求结构体
typedef struct stPlayReq
{
    int iHardWareDecode;  // 是否开启GPU硬解 0-不开启 1-开启（如果开启硬解，但如显卡不支持等导致错误，SDK内部自动切换成软解，如果不是特别需求，建议不开启硬解）
    pfnStreamCallback fnStream;              // 码流数据回调
    pfnMsgCallback fnMsg;                    // 取流、播放消息回调
    pfnDecodedDataCallback fnDecodedStream;  // 解码后的YUV数据回调
    void* pUserData;                         // 用户数据
    char szResevre[64];                      // 保留参数
}VIDEO_PLAY_REQ, *PVIDEO_PLAY_REQ;

////////////////////////// 接口定义 /////////////////////////////
// SDK初始化
// pszEvn：保留参数，传NULL即可
// 备注：调一次即可，初始化成功情况下重复调直接返回成功
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_Init(_IN_ const char* pszEvn);

// SDK反初始化
// 备注：调一次即可，反初始化成功情况下重复调直接返回成功
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_Fini();

// 视频预览（支持取实时流、回调取流与播放的消息，以及回调YUV数据，需要播放请求参数中指定）
// pszUrl：预览URL
// hWnd：视频预览的Windows窗口句柄
// pstPlayReq：播放请求参数，具体参数详见结构体定义
// 备注：预览无播放结束消息
// 成功返回大于0的预览句柄，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_StartPreview(_IN_ const char* pszUrl, _IN_ void* hWnd, _IN_ PVIDEO_PLAY_REQ pstPlayReq);

// 停止预览（停止取流，停止回调消息，停止回调YUV数据）
// i64PlayHandle：预览句柄，来源于Video_StartPreview返回值
// 备注：预览无播放结束消息，当调停止预览接口成功就可以认为是播放结束了
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_StopPreview(_IN_ VIDEO_INT64 i64PlayHandle);

// 网络录像回放（支持取网络录像流、回调取流与播放的消息，以及回调YUV数据，需要播放请求参数中指定）
// pszUrl：回放URL
// hWnd：网络录像回放的Window窗口句柄
// i64StartTimeStamp：查询录像时的开始时间戳，单位：秒
// i64EndTimeStamp：查询录像时的结束时间戳，单位：秒
// pstPlayReq：播放请求参数，详细参数详见结构体定义
// 成功返回大于0的回放句柄，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_StartPlayback(_IN_ const char* pszUrl, _IN_ void* hWnd, _IN_ VIDEO_INT64 i64StartTimeStamp, _IN_ VIDEO_INT64 i64EndTimeStamp, _IN_ PVIDEO_PLAY_REQ pstPlayReq);

// 停止网络录像回放（停止取流，停止回调消息，停止回调YUV数据）
// i64PlayHandle：网络录像回放句柄，来源于Video_StartPlayback接口
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_StopPlayback(_IN_ VIDEO_INT64 i64PlayHandle);

// 网络录像播放控制
// i64PlayHandle：网络录像回放句柄，来源于Video_StartPlayback接口
// iCtrlType：控制类型，0-暂停播放 1-恢复播放 2-定位播放 3-倍速播放
// i64Param：播放控制参数。当iCtrlType为0和1时无效；当iCtrlType为2时，该参数为定位播放时间戳；当iCtrlType为3时，该参数为倍速（播放速度从慢到快分别为：-16、-8、-4、-2、1、2、4、8、16）
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_PlayCtrl(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iCtrlType, _IN_ VIDEO_INT64 i64Param);

// 查询网络录像回放当前播放时间戳（单位：秒）
// i64PlayHandle：网络录像回放句柄，来源于Video_StartPlayback接口
// 成功返回时间戳，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE VIDEO_INT64 CALLBACK Video_GetCurrentPlayTime(_IN_ VIDEO_INT64 i64PlayHandle);

// 播放抓图（支持视频预览和网络录像回放播放抓图）
// i64PlayHandle：视频预览或网络录像回放句柄，来源于Video_StartPreview或Video_StartPlayback接口
// pszAbsoluteFile：抓图图片文件绝对路径名称，只支持“bmp”和“jpg”后缀，如“D:\\SnapShot\test.bmp”，“D:\\SnapShot\test.jpg”
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_PlaySnap(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ const char* pszAbsoluteFile);

// 共享式声音控制（即支持打开多路的声音）
// i64PlayHandle：视频预览或网络录像回放句柄，来源于Video_StartPreview或Video_StartPlayback接口
// iCtrlType：控制类型，0-打开声音 1-关闭声音
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_SoundCtrl(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iCtrlType);

// 获取音量
// i64PlayHandle：视频预览或网络录像回放句柄，来源于Video_StartPreview或Video_StartPlayback接口
// 成功返回音量值（取值范围为[0 100]），失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_GetVolume(_IN_ VIDEO_INT64 i64PlayHandle);

// 设置音量
// i64PlayHandle：视频预览或网络录像回放句柄，来源于Video_StartPreview或Video_StartPlayback接口
// iVolume：音量值，范围应在[0 100]，如果超出范围，SDK内部使用音量最大或最小值来替代
// 成功返回VIDEO_ERR_SUCCESS，失败返回VIDEO_ERR_FAIL，失败了通过Video_GetLastError查询错误码
VIDEOSDK_DECLARE int CALLBACK Video_SetVolume(_IN_ VIDEO_INT64 i64PlayHandle, _IN_ int iVolume);

// 获取错误码
// 返回错误码值
VIDEOSDK_DECLARE int CALLBACK Video_GetLastError();

#endif  // HIK_VIDEOSDK_H