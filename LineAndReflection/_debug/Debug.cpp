#include "Debug.h"
#include <Windows.h>
#include <sstream>

void Debug::Out(const char* str)
{
#ifdef _DEBUG
	OutputDebugStringA(str);
#endif // DEBUG
}
void Debug::Out(const wchar_t* str)
{
#ifdef _DEBUG
	OutputDebugStringW(str);
#endif//DEBUG
}
void Debug::Out(const std::string str)
{
	Out(str.c_str());
}
void Debug::Out(const std::wstring str)
{
	Out(str.c_str());
}
void Debug::Out(const int val)
{
	std::ostringstream os;
	os << val;
	Out(os.str());
}
void Debug::Out(const float val)
{
	std::ostringstream os;
	os << val;
	Out(os.str());
}
void Debug::OutLine(const char* str)
{
	Out(str);
	Out("\n");
}
void Debug::OutLine(const wchar_t* str)
{
	Out(str);
	Out("\n");
}
void Debug::OutLine(const std::string str)
{
	Out(str);
	Out("\n");
}

void Debug::OutLine(const std::wstring str)
{
	Out(str);
	Out("\n");
}

void Debug::OutLine(const int val)
{
	Out(val);
	Out("\n");
}

void Debug::OutLine(const float val)
{
	Out(val);
	Out("\n");
}
