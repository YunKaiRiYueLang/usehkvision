/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  日志库旧接口
 *          
 *  @note   create file
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:30:44
 *
 *  @change log
 *
 */
#ifndef __HLOG1_H__
#define __HLOG1_H__

#include "hlogconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn int hlog_init(const char* name, char async = false)
     *  @brief 兼容旧接口, 不执行任何操作
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false)
     *  @brief 兼容旧接口, 不执行任何操作
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn int hlog_fini()
     *  @brief 兼容旧接口, 不执行任何操作
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn int hlog_set_callback(HLOG_CB callback)
     *  @brief 设置日志的回调函数
     *  @param[in] callback 用于处理日志信息的回调函数
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn int hlog_level(HLOG_LEVEL level)
     *  @brief 兼容旧接口, 不执行任何操作
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
     *  @brief 写日志格式化数据
     *  @param[in] level 日志级别
     *  @param[in] module 日志模块
     *  @param[in] format 日志格式化字符串, 后接可变参数
     *  @return HLOG_OK, 成功; 否则, 失败
     *  @note hlog_format会调用hlog_set_callback传入的回调函数
     *  @warning 使用者必须保证输入的格式化字符串和可变参数相匹配
     *  @sa hlog_format_ex
     */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn int HLOG_API hlog_format(int level, const char* module, const char* format, ...)
     *
     *  @brief 写日志格式化数据, 功能和hlog_format相同，只是接口参数定义更加通用
     *  @param[in] level 日志级别
     *  @param[in] module 日志模块
     *  @param[in] format 日志格式化字符串, 后接可变参数
     *  @return HLOG_OK, 成功; 否则, 失败
     *  @note hlog_format会调用hlog_set_callback传入的回调函数
     *  @warning 使用者必须保证输入的格式化字符串和可变参数相匹配
     *  @sa hlog_format
     */
    HLOG_DECLARE int HLOG_API hlog_format_ex(int level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn int HLOG_API hlog_std_format(
     *          int level,
     *          const char* module,
     *          const char* function_name,
     *          int line_no,
     *          const char* instance_id,
     *          int status,
     *          const char* format,
     *          ... );
     *
     *  @brief      新规范的日志接口
     *  @param[in]  level, 日志级别
     *  @param[in]  module, 日志模块
     *  @param[in]  function_name, 函数
     *  @param[in]  line_no, 行号
     *  @param[in]  instance_id, 调用/请求实例ID
     *  @param[in]  status, 状态码
     *  @param[in]  format, 日志格式化字符串, 后接可变参数
     *  @return     HLOG_OK, 成功; 否则, 失败
     *  @warning    使用者必须保证输入的格式化字符串和可变参数相匹配
     */
    HLOG_DECLARE int HLOG_API hlog_std_format(
        int level,
        const char* module,
        const char* function_name,
        int line_no,
        const char* instance_id,
        int status,
        const char* format,
        ... ) LOG_CHECK_FMT(7, 8);

    /** 
     *  @brief      新软件集成规范下的运行日志接口
     *  @param[in]  level, 日志级别
     *  @param[in]  module, 日志模块
	 *  @param[in]  file_name, 文件名 (无信息填写NULL 或 "")
     *  @param[in]  function_name, 函数名 (无信息填写NULL 或 "")
     *  @param[in]  line_no, 行号
     *  @param[in]  error_code, 错误码 (无信息填写NULL 或 "")
	 *  @param[in]  trace_id,   跟踪信息中的trace_id (无信息填写NULL 或 "")
	 *  @param[in]  span_id,    跟踪信息中的span_id (无信息填写NULL 或 "")
     *  @param[in]  format, 日志格式化字符串, 后接可变参数
     *  @return     HLOG_OK, 成功; 否则, 失败
     *  @warning    使用者必须保证输入的格式化字符串和可变参数相匹配
     */
	HLOG_DECLARE int HLOG_API hlog_format_std_log(
		HLOG_LEVEL level,
		const char* module,
		const char* function_name,
		const char* file_name,
		int line_no,
		const char* trace_id,
		const char* span_id,
		const char* error_code,
		const char* format,
		... ) LOG_CHECK_FMT(9, 10);

	    /** 
     *  @brief      新软件集成规范下的运行日志接口（自动填写跟踪信息）
     *  @param[in]  level, 日志级别
     *  @param[in]  module, 日志模块
	 *  @param[in]  file_name, 文件名 (无信息填写NULL 或 "")
     *  @param[in]  function_name, 函数名 (无信息填写NULL 或 "")
     *  @param[in]  line_no, 行号
     *  @param[in]  error_code, 错误码 (无信息填写NULL 或 "")
     *  @param[in]  format, 日志格式化字符串, 后接可变参数
     *  @return     HLOG_OK, 成功; 否则, 失败
     *  @warning    使用者必须保证输入的格式化字符串和可变参数相匹配
     */
	HLOG_DECLARE int HLOG_API hlog_format_std_log_auto_trace(
		HLOG_LEVEL level,
		const char* module,
		const char* file_name,
		const char* function_name,
		int line_no,
		const char* error_code,
		const char* format,
		... ) LOG_CHECK_FMT(7, 8);

    /** @fn int hlog_message(HLOG_LEVEL level, const char* module, const char* message)
     *  @brief 写日志字符串
     *  @param[in] level 日志级别
     *  @param[in] module 日志模块
     *  @param[in] message 日志字符串
     *  @return HLOG_OK, 成功; 否则, 失败
     *  @note hlog_message不会调用hlog_set_callback传入的回调函数
     *  @warning 在使用该接口时, 不应在message中携带%n等格式化输出的字符,
     *           否则可能有崩溃的风险, 如果不能确定输入的内容, 那么请使用
     *           hlog_message_ex接口
     *  @sa hlog_message_ex
     */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn int hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message)
     *  @brief 写日志字符串
     *  @param[in] level 日志级别
     *  @param[in] module 日志模块
     *  @param[in] message 日志字符串
     *  @return HLOG_OK, 成功; 否则, 失败
     *  @sa hlog_message
     */
    HLOG_DECLARE int HLOG_API hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn void HLOG_API hlog_set_configfile_name(const char* config_file_name)
     *  @brief 多进程共享一个配置文件时会出现日志文件滚动错误, 为了规避这一错误, 
     *         特加上此接口, 不建议用这个接口, 如果仅是一个进程, 则最好用一个配
     *         置文件
     *  @param[in] config_file_name 配置文件名
     */
    HLOG_DECLARE void HLOG_API hlog_set_configfile_name(const char* config_file_name);

    /** @fn void HLOG_API hlog_set_immediate_flush(int immediate_flush);
     *
     *  @brief      设置是否立即刷写日志到文件（接口预留，暂未实现）
     *  @param[in]  immediate_flush, 是否立即刷写日志到文件, 0-false, else-true
     *  @warning    如果在日志配置文件中启用了日志缓冲区，而又在退出时段比较关注
     *              日志的即时性，那么可以考虑使用该接口控制进程回到立即写日志的
     *              状态
     *  @sa         hlog_flush_and_finalize
     */
    HLOG_DECLARE void HLOG_API hlog_set_immediate_flush(int immediate_flush);

    /** @fn void HLOG_API hlog_flush_and_finalize();
     *
     *  @brief      刷写缓存中最后的日志并反初始化日志库
     *  @warning    如果在日志配置文件中启用了日志缓冲区，那么必须在程序退出前
     *              调用该接口将缓冲区的日志刷写到日志文件中
     *  @sa         hlog_set_immediate_flush
     */
    HLOG_DECLARE void HLOG_API hlog_flush_and_finalize();

#ifdef __cplusplus
}
#endif

// 考虑兼容性，特增加log_printf_def和log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for defualt module
#if (defined _WIN32 || defined _WIN64)
    #define LOG_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define LOG_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define LOG_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for HPP module
#if (defined _WIN32 || defined _WIN64)
    #define HPP_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define HPP_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "HPP", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "HPP", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define HPP_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for MQ module
#if (defined _WIN32 || defined _WIN64)
    #define MQ_ERROR(fmt, ...)          hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define MQ_WARN(fmt, ...)           hlog_format(HLOG_LEVEL_WARN, "MQ", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_INFO(fmt, ...)           hlog_format(HLOG_LEVEL_INFO, "MQ", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_DEBUG(fmt, ...)          hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_TRACE(fmt, ...)          hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define MQ_ERROR(fmt, args...)      hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_WARN(fmt, args...)       hlog_format(HLOG_LEVEL_WARN, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_INFO(fmt, args...)       hlog_format(HLOG_LEVEL_INFO, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_DEBUG(fmt, args...)      hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_TRACE(fmt, args...)      hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#endif
