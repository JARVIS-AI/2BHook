#pragma once
#include <Windows.h>
#include <stdio.h>

#define TODO_CLICKABLE

#ifndef _MAKE_STRING
#define _MAKE_STRING(x)  #x
#endif // !_MAKE_STRING

#ifndef MAKE_STRING
#define MAKE_STRING(x) _MAKE_STRING(x)
#endif // !MAKE_STRING

#ifndef TODO
#ifndef TODO_CLICKABLE
#define TODO(x) __pragma(message(":TODO: " MAKE_STRING(x) " -> " __FILE__ "@" MAKE_STRING(__LINE__))) 
#else
#define TODO(x) __pragma(message(__FILE__ "(" MAKE_STRING(__LINE__) "):" " TODO: " MAKE_STRING(x))) 
#endif // !TODD_CLICKABLE
#endif // !TODO

#ifdef _DEBUG
#define LOG(fmt, ...) Log::Log(__FUNCTION__, fmt, __VA_ARGS__)
#else 
#define LOG(fmt, ...)
#endif

#ifdef _DEBUG
#define EXPLOG(fmt, ...) LOG
#else
#define EXPLOG(fmt, ...) MessageBoxA(NULL, fmt, fmt, MB_OK | MB_ICONERROR | MB_SETFOREGROUND)
#endif

class Log
{
public:
	explicit Log(const char* szFunction, const char* fmt, ...)
	{
		printf("[%s]: ", szFunction);
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
	}

	static void AttachConsole(const wchar_t* szConsolename)
	{
		AllocConsole();
		SetConsoleTitleW(szConsolename);
		freopen_s(&pStdout, "CON", "w", stdout);
	}

	static inline void DetachConsole(void)
	{
		fclose(pStdout);
		FreeConsole();
	}

private:
	static FILE* pStdout;
};