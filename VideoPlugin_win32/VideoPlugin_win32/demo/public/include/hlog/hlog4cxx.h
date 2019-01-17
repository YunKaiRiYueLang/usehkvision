/** @file hlog4cxx.h
 *  @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief log4cxx��־ϵͳ�ķ�װ��
 *
 *  @author     ��ͨ��
 *  @date       2010/06/28
 */
#ifndef __HLOG4CXX_H__
#define __HLOG4CXX_H__

#include "hlogconfig.h"

// ��־������
typedef void* HLOG4CXX_HANDLE;

#ifdef __cplusplus
extern "C"
{
#endif

    /** @fn void hlog_ConfigureA(const char* filename)
    *   @brief ���������ļ�������log4cxx
    *   @param filename �����ļ�·��
    */
    HLOG_DECLARE void HLOG_API hlog_ConfigureA(const char* filename);
    HLOG_DECLARE void HLOG_API hlog_ConfigureW(const wchar_t* filename);

    /** @fn HLOG4CXX_HANDLE hlog_OpenLoggerA(const char* name)
    *   @brief ��ȡ��־���
    *   @param name ��־��������
    *   @return ��־������������ name ���������ļ����õ���־�������������򷵻�Ĭ�ϵ���־����
    */
    HLOG_DECLARE HLOG4CXX_HANDLE HLOG_API hlog_OpenLoggerA(const char* name);
    HLOG_DECLARE HLOG4CXX_HANDLE HLOG_API hlog_OpenLoggerW(const wchar_t* name);

    /** @fn void hlog_CloseLogger(HLOG4CXX_HANDLE logger)
    *   @brief �ͷ���־���
    *   @param logger ��־������
    */
    HLOG_DECLARE void HLOG_API hlog_CloseLogger(HLOG4CXX_HANDLE logger);

    /** @fn bool hlog_IsEnabledFor(HLOG4CXX_HANDLE logger, HLOG_LEVEL level)
    *   @brief �ж�ĳ�������־�Ƿ�ᱻ���
    *   @param logger ��־������
    *   @param level ��־����
    *   @return true - level �������־�ᱻ�����false - level �������־���ᱻ���
    */
    HLOG_DECLARE bool HLOG_API hlog_IsEnabledFor(HLOG4CXX_HANDLE logger, HLOG_LEVEL level);

    /** @fn HLOG_LEVEL hlog_GetEffectiveLevel(HLOG4CXX_HANDLE logger)
    *   @brief ��ȡ��־����������
    *   @param logger ��־������
    *   @return ��־���������𣬼����ڸü������־�����ᱻ���
    */
    HLOG_DECLARE HLOG_LEVEL HLOG_API hlog_GetEffectiveLevel(HLOG4CXX_HANDLE logger);
 
    /** @fn int hlog_GetNameA(HLOG4CXX_HANDLE logger, char* const name, int size)
    *   @brief ��ȡ��־��������
    *   @param logger ��־������
    *   @param name ��־������������
    *   @param size ��־�������������ߴ�
    *   @return �趨��length = ��־�������Ƶĳ��ȣ�����������������
    *       �� name == NULL ������ length
    *       �� size <= length ������ size - 1
    *       �� size > length ������ length
    */
    HLOG_DECLARE int HLOG_API hlog_GetNameA(HLOG4CXX_HANDLE logger, char* const name, int size);
    HLOG_DECLARE int HLOG_API hlog_GetNameW(HLOG4CXX_HANDLE logger, wchar_t* const name, int size);

    /** @fn void hlog_LogA(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const char* message)
    *   @brief �����־��Ϣ
    *   @param logger ��־������
    *   @param level ��־����
    *   @param message ��־��Ϣ
    */
    HLOG_DECLARE void HLOG_API hlog_LogA(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const char* message);
    HLOG_DECLARE void HLOG_API hlog_LogW(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const wchar_t* message);

    /** @fn void hlog_LogExtA(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const char* message, const char* filename, const char* functionName, int lineNumber)
    *   @brief �����־��Ϣ������ش�����Ϣ
    *   @param logger ��־������
    *   @param level ��־����
    *   @param message ��־��Ϣ
    *   @param filename �����־�Ĵ����ļ�·��
    *   @param functionName �����־�Ĵ��뷽������
    *   @param lineNumber �����־�Ĵ����к�
    */
    HLOG_DECLARE void HLOG_API hlog_LogExtA(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const char* message, const char* filename, const char* functionName, int lineNumber);
    HLOG_DECLARE void HLOG_API hlog_LogExtW(HLOG4CXX_HANDLE logger, HLOG_LEVEL level, const wchar_t* message, const char* filename, const char* functionName, int lineNumber);

#ifdef __cplusplus
}
#endif

#endif // __HLOG4CXX_H__
