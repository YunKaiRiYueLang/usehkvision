/** @file   hlog.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  ��־��ӿڣ�ֻ�������ӿڣ�hlog_set_log_callback�� hlog_print���ɵ���־��ӿ���hlog1.h�ж���
 *          
 *  @ʹ�þ�����
 *      1������ģ�飺HLOG_HANLDE_MODULE(NVR)�����ļ��·��Ѿ�Ĭ�϶�����default HPP MQ ����ģ�飩
 *                   
 *      2�������д��־
 *         #define NVR_ERROR(error_code, error_description, bussiness_id, module_id, fmt, ...) \
 *         hlog_print(HLOG_LEVEL_ERROR, HLOGGER(NVR), error_code, error_description, bussiness_id, module_id, __HLOG_FILE__, __HLOG_FUNC__, __HLOG_LINE__, fmt, ##__VA_ARGS__);
 *
 *      3�����ú�д��־
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:48:14
 *
 *  @change log
 *
 */
#ifndef __HLOG_H__
#define __HLOG_H__

#include "hlogconfig.h"
#include "hlog4cxx.h"
#include "hlog1.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @fn typedef void (HLOG_API * HlogCallBack()
 *  @brief ��־�ص�����
 *  @@return 
 */
typedef void (HLOG_API *HlogCallBack)(HLOG_LEVEL level,  
                                      int error_code, 
                                      int bussiness_id,
                                      int module_id,
                                      const char* message,
                                      void* user_data);

/** @fn HLOG_DECLARE int HLOG_API hlog_set_callback2(HlogCallBack callback)
 *  @brief ������־�ص����������ٴ�ӡ��־����־��Ϣͨ���ص���������
 *  @param callback[in] �ص�����ָ��
 *  @param user_data[in] �û�����
 *  @@return HLOG_OK
 */
HLOG_DECLARE int HLOG_API hlog_set_log_callback(HlogCallBack callback, void* user_data);

/** @fn HLOG_DECLARE int HLOG_API hlog_print(HLOG_LEVEL level, HLOG_HANDLE module, int error_code, const char* error_description, int bussiness_id, int module_id, const char* filename, const char* funcname, int lineno, const char* format, ...)
 *  @brief ��¼��־
 *  @param level[in] ��־����
 *  @param module_handle[in] ��־ģ����
 *  @param error_code[in] ������
 *  @param error_description[in] ��������
 *  @param bussiness_id[in] ���� bussiness id
 *  @param module_id[in] ���� mdule id
 *  @param filename[in] �����ļ���
 *  @param funcname[in] ���뺯����
 *  @param lineno[in] �к�
 *  @param format[in] ��ʽ���ַ���
 *  @@return �ɹ����� HLOG_OK ʧ�ܷ�����Ӧ������
 */
HLOG_DECLARE int HLOG_API hlog_print(HLOG_LEVEL level,
                                     HLOG_HANDLE module_handle, 
                                     int error_code,
                                     const char* error_description,
                                     int module_id,
                                     int bussiness_id,
                                     const char* filename, 
                                     const char* funcname, 
                                     int lineno,
                                     const char* format, ...) LOG_CHECK_FMT(10, 11);

/** @fn typedef void(HLOG_API * HlogEventCallBack(HLOG_API *HlogEventCallBack)
 *  @brief �¼��ص�����
 *  @param level[in] ��־����
 *  @param error_code[in] ������
 *  @param bussiness_id[in] bussiness id
 *  @param module_id[in] module id
 *  @param event_module[in] �¼�ģ��
 *  @param message[in] ��׼��־��ʽ��չ����
 *  @param conflict_tag[in] ��ͻ��ǩ
 *  @param filter[in] ���ݿ����
 *  @param time_out[in] ��ʱʱ��
 *  @param event_type[in] �¼����ͣ�0����ʼ�� 1��������2�������¼�
 *  @param occur_time[in] ����ʱ��
 *  @param user_data[in] �û�����
 *  @@return 
 */
typedef void(HLOG_API *HlogEventCallBack)(HLOG_LEVEL level,       
                                          int error_code,
                                          int bussiness_id,
                                          int module_id,
                                          const char* event_module,
                                          const char* message,           
                                          const char* conflict_tag,    
                                          const char* filter,
                                          const int time_out,
                                          const int   event_type,       
                                          const char*  occur_time,  
                                          void* user_data);      

/** @fn HLOG_DECLARE int HLOG_API hlog_set_event_callback(HlogEventCallBack listen_call_back, void* user_data)
 *  @brief �����¼��ص��������¼���ÿһ����������ʼ�����������������˻ص�
 *  @param listen_call_back[in] �ص�����
 *  @param user_data[in] �û�����
 *  @@return HLOG_OK
 */
HLOG_DECLARE int HLOG_API hlog_set_event_callback(HlogEventCallBack listen_call_back, void* user_data);   

/** @fn HLOG_DECLARE int HLOG_API hlog_event(HLOG_LEVEL level, const char* module, int error_code, const char* error_description, int bussiness_id, int module_id, const char* filename, const char* funcname, int lineno, const char* event_module, const char* conflict_tag, const char* filter, const int time_out, const char* format, ...)
 *  @brief ��¼��־���¼�����
 *  @param level[in] ��־����
 *  @param module_handle[in] ģ����������д��־
 *  @param error_code[in] ������
 *  @param error_description[in] �������� 
 *  @param bussiness_id[in] ���� bussiness_id
 *  @param module_id[in] ���� module_id
 *  @param filename[in] �ļ���
 *  @param funcname[in] ������
 *  @param lineno[in] �к�
 *  @param event_module[in] �¼�ģ��
 *  @param conflict_tag[in] ��ͻ��ǩ
 *  @param filter[in] ���ݿ�����ֶ�
 *  @param time_out[in] ��ʱʱ��
 *  @param format[in] ��ʽ���ַ���
 *  @@return success:HCOUNTER_OK fail:������
 */
HLOG_DECLARE int HLOG_API hlog_event(HLOG_LEVEL level,
                                     HLOG_HANDLE module_handle,
                                     int error_code,
                                     const char* error_description,
                                     int bussiness_id,
                                     int module_id,
                                     const char* filename, 
                                     const char* funcname, 
                                     int lineno,
                                     const char* event_module, 
                                     const char* conflict_tag, 
                                     const char* filter, 
                                     const int   time_out,
                                     const char* format, ...) LOG_CHECK_FMT(14, 15);

#ifdef __cplusplus
} // __cplusplus
#endif

#define HLOGCAT(start, end) start##end
#define HLOGSTR(str) #str

#define HLOGGER(module) HLOGCAT(hlog_handle_, module)

#define HLOG_HANLDE_MODULE(module) static HLOG_HANDLE HLOGCAT(hlog_handle_, module) = hlog_OpenLoggerA(HLOGSTR(module));

#endif
