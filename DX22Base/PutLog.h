#ifndef _____PUT_LOG_H_____
#define _____PUT_LOG_H_____

#include <Windows.h>
#include <string>

/// @brief エラーメッセージをMessageBoxで出す
/// @param 出力文字列
void Error(LPCSTR);

/// @brief 出力ウィンドウに値を表示する
/// @param 出力文字列
void PutDebug(std::string);

#endif // !_____PUT_LOG_H_____