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
    #define _IN_    // 表示入参
#endif

#define VIDEOPLUGIN_SUCCESS 0   // 成功
#define VIDEOPLUGIN_FAIL    -1  // 失败


// 消息回调
typedef void(_stdcall *VideoPlugin_MessageCallback)(void* pPluginInstance, char* pRspJsonMsg, void* pUserData);


// 创建实例
// 入参：
//     pParentWndHandle：父窗口句柄
// 返回值：实例指针
VIDEOPLUGIN_EXPORT void* VideoPlugin_CreatePluginInstance(void* pParentWndHandle);

// 销毁实例
// 入参：
//     pPluginInstance：实例指针
// 返回值：无
VIDEOPLUGIN_EXPORT void VideoPlugin_DestroyPluginInstance(_IN_ void* pPluginInstance);

// 获取窗口句柄
// 入参：
//     pPluginInstance：实例指针
// 返回值：非NULL为成功 NULL为失败 
VIDEOPLUGIN_EXPORT void* VideoPlugin_GetWindowHandle(_IN_ void* pPluginInstance);

// 通用请求接口
// 入参：实例指针
//      pPluginInstance：实例指针
//      pszJsonRequest：json格式请求报文，支持的功能以及使用方式详见“通用请求接口功能支持”
// 返回值：json格式报文，格式详见下面，注意需要调用方释放内存
VIDEOPLUGIN_EXPORT char* VideoPlguin_GerneralRequest(_IN_ void* pPluginInstance, _IN_ const char* pszJsonRequest);

// 消息回调设置接口
// 入参：实例指针
//      pPluginInstance：实例指针
//      fnMsgCB：回调函数地址
//      pUserData：用户数据
// 返回值：0-成功 -1-失败
// 备注：暂不启用
VIDEOPLUGIN_EXPORT int VideoPlugin_SetMessageCallback(_IN_ void* pPluginInstance, VideoPlugin_MessageCallback pfnMsgCB, void* pUserData);

/////////////////////////////// 通用请求接口(VideoPlguin_RequestInterface)返回值///////////////////////////////////////////
/*
{
errorCode: 0,                       // 0 - 成功 -1 - 失败
errorMessage: "",                   // 错误描述，此字段不一定有
data: ""                            // 数据，此字段不一定有
}
*/

///////////////////////////////// 通用请求接口(VideoPlguin_RequestInterface)功能支持 /////////////////////////////////
/*
1、入参pszJsonRequest为json报文格式，如下：
{
funcName: "funcName",   // 功能标识
argument: "argument"    // 参数，这里可以是json字符串，也可以不存在该字段（不需要带参数的功能）
}

2、支持的功能如下（注：以下json报文中数据为示例数据，与实际有出入）：
1> 初始化
功能标识（funcName）："init",
参数（argument）：
{
appkey: "afsgnhmj34567dgh",       // API网关提供的appkey，必填
secret: "vgkk3g0jaoj0igoigj",     // API网关提供的secret，必填
ip: "10.33.31.4",                 // API网关IP地址，必填
port: 800,                        // API网关端口，必填
playMode: 0,                      // 播放模式（决定显示预览还是回放界面），0-预览 1-网络录像播放，不填默认预览
snapDir: "D:\\SnapDir",           // 抓图存储路径，不填使用默认路径
layout: "2x2",                    // playMode的布局，不填使用默认布局
encryptedFields: "appkey,secret"  // 加密了的字段
}

2> 反初始化
功能标识（funcName）："uninit",
参数（argument）：不用传

3> 开始预览
功能标识（funcName）："startPreview",
参数（argument）：
{
cameraIndexCode: "afsgnhmj34567dgh",   // 监控点编号
streamMode: 0,                    // 主子码流标识，0-主码流 1-子码流
gpuMode: 0,                       // 是否开启GPU硬解，不建议开启，0-不开启 1-开启
transMode, 1                      // 传输协议 1-TCP 0-UDP
}

4> 开始回放
功能标识（funcName）："startPlayback",
参数（argument）：
{
cameraIndexCode: "afsgnhmj34567dgh",   // 监控点编号
startTimeStamp: "10237898985",    // 录像查询开始时间戳，单位：秒
endTimeStamp: "10237899985",      // 录像查询结束时间戳，单位：秒
recordLocation: 0,                // 录像存储类型，非必填，不填查询所有，0-中心存储 1-设备存储
transMode: 0,                     // 传输协议 1-TCP 0-UDP
gpuMode: 0,                       // 是否开启GPU硬解，不建议开启，0-不开启 1-开启
}

5> 停止全部预览
功能标识（funcName）："stopAllPreview",
参数（argument）：不用传

6> 停止全部回放
功能标识（funcName）："stopAllPlayback",
参数（argument）：不用传

7> 获取RSA公钥
功能标识（funcName）："getRSAPubKey",
参数（argument）：
{
keyLength: 1024,   // RSA秘钥长度，可选1024、2048bit，注意填充方式为RSA_PKCS1_PADDING
}

*/
