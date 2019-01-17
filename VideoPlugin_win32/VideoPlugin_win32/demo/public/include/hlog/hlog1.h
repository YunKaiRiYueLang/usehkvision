/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  ��־��ɽӿ�
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
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false)
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn int hlog_fini()
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn int hlog_set_callback(HLOG_CB callback)
     *  @brief ������־�Ļص�����
     *  @param[in] callback ���ڴ�����־��Ϣ�Ļص�����
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn int hlog_level(HLOG_LEVEL level)
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
     *  @brief д��־��ʽ������
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] format ��־��ʽ���ַ���, ��ӿɱ����
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_format�����hlog_set_callback����Ļص�����
     *  @warning ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
     *  @sa hlog_format_ex
     */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn int HLOG_API hlog_format(int level, const char* module, const char* format, ...)
     *
     *  @brief д��־��ʽ������, ���ܺ�hlog_format��ͬ��ֻ�ǽӿڲ����������ͨ��
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] format ��־��ʽ���ַ���, ��ӿɱ����
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_format�����hlog_set_callback����Ļص�����
     *  @warning ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
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
     *  @brief      �¹淶����־�ӿ�
     *  @param[in]  level, ��־����
     *  @param[in]  module, ��־ģ��
     *  @param[in]  function_name, ����
     *  @param[in]  line_no, �к�
     *  @param[in]  instance_id, ����/����ʵ��ID
     *  @param[in]  status, ״̬��
     *  @param[in]  format, ��־��ʽ���ַ���, ��ӿɱ����
     *  @return     HLOG_OK, �ɹ�; ����, ʧ��
     *  @warning    ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
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
     *  @brief      ��������ɹ淶�µ�������־�ӿ�
     *  @param[in]  level, ��־����
     *  @param[in]  module, ��־ģ��
	 *  @param[in]  file_name, �ļ��� (����Ϣ��дNULL �� "")
     *  @param[in]  function_name, ������ (����Ϣ��дNULL �� "")
     *  @param[in]  line_no, �к�
     *  @param[in]  error_code, ������ (����Ϣ��дNULL �� "")
	 *  @param[in]  trace_id,   ������Ϣ�е�trace_id (����Ϣ��дNULL �� "")
	 *  @param[in]  span_id,    ������Ϣ�е�span_id (����Ϣ��дNULL �� "")
     *  @param[in]  format, ��־��ʽ���ַ���, ��ӿɱ����
     *  @return     HLOG_OK, �ɹ�; ����, ʧ��
     *  @warning    ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
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
     *  @brief      ��������ɹ淶�µ�������־�ӿڣ��Զ���д������Ϣ��
     *  @param[in]  level, ��־����
     *  @param[in]  module, ��־ģ��
	 *  @param[in]  file_name, �ļ��� (����Ϣ��дNULL �� "")
     *  @param[in]  function_name, ������ (����Ϣ��дNULL �� "")
     *  @param[in]  line_no, �к�
     *  @param[in]  error_code, ������ (����Ϣ��дNULL �� "")
     *  @param[in]  format, ��־��ʽ���ַ���, ��ӿɱ����
     *  @return     HLOG_OK, �ɹ�; ����, ʧ��
     *  @warning    ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
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
     *  @brief д��־�ַ���
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] message ��־�ַ���
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_message�������hlog_set_callback����Ļص�����
     *  @warning ��ʹ�øýӿ�ʱ, ��Ӧ��message��Я��%n�ȸ�ʽ��������ַ�,
     *           ��������б����ķ���, �������ȷ�����������, ��ô��ʹ��
     *           hlog_message_ex�ӿ�
     *  @sa hlog_message_ex
     */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn int hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message)
     *  @brief д��־�ַ���
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] message ��־�ַ���
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @sa hlog_message
     */
    HLOG_DECLARE int HLOG_API hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn void HLOG_API hlog_set_configfile_name(const char* config_file_name)
     *  @brief ����̹���һ�������ļ�ʱ�������־�ļ���������, Ϊ�˹����һ����, 
     *         �ؼ��ϴ˽ӿ�, ������������ӿ�, �������һ������, �������һ����
     *         ���ļ�
     *  @param[in] config_file_name �����ļ���
     */
    HLOG_DECLARE void HLOG_API hlog_set_configfile_name(const char* config_file_name);

    /** @fn void HLOG_API hlog_set_immediate_flush(int immediate_flush);
     *
     *  @brief      �����Ƿ�����ˢд��־���ļ����ӿ�Ԥ������δʵ�֣�
     *  @param[in]  immediate_flush, �Ƿ�����ˢд��־���ļ�, 0-false, else-true
     *  @warning    �������־�����ļ�����������־���������������˳�ʱ�αȽϹ�ע
     *              ��־�ļ�ʱ�ԣ���ô���Կ���ʹ�øýӿڿ��ƽ��̻ص�����д��־��
     *              ״̬
     *  @sa         hlog_flush_and_finalize
     */
    HLOG_DECLARE void HLOG_API hlog_set_immediate_flush(int immediate_flush);

    /** @fn void HLOG_API hlog_flush_and_finalize();
     *
     *  @brief      ˢд������������־������ʼ����־��
     *  @warning    �������־�����ļ�����������־����������ô�����ڳ����˳�ǰ
     *              ���øýӿڽ�����������־ˢд����־�ļ���
     *  @sa         hlog_set_immediate_flush
     */
    HLOG_DECLARE void HLOG_API hlog_flush_and_finalize();

#ifdef __cplusplus
}
#endif

// ���Ǽ����ԣ�������log_printf_def��log_printf_dst
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
