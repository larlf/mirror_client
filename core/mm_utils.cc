#include "mm_utils.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

#ifdef WIN32
#include <iconv.h>
#endif


using namespace mm;

unsigned int mm::UIUtils::idIndex = 0;

std::string mm::UIUtils::newId()
{
	char buffer[10];
	std::string id("UI_");
	UIUtils::idIndex++;
	sprintf_s(buffer, 10, "%d", UIUtils::idIndex);
	id.append(buffer);
	return id;
}

void GameUtils::debugBytes(const BYTE *data, uint size)
{
	std::ostringstream ss;	//显示内容的缓存
	char buff[255];			//每行内容的缓存
	int pos;				//不前显示数据的位置
	int bound = 60;			//每一行显示完HEX信息后的边界，后面可以用于字符的显示

	for (uint i = 0; i < size; ++i)
	{
		//行首，位置信息的输出
		if (i % 16 == 0)
		{
#ifdef __linux__
			sprintf(buff, "%5d: ", i);
#else
			sprintf_s(buff, "%5d: ", i);
#endif

			pos = 7;
		}

		char v = data[i];	//当前显示的字符
		int p = i % 16;			//当前字符在这一行字符中的位置

		//字符显示
		if (v >= 0x20) buff[bound + p] = v;
		else buff[bound + p] = '?';

		//十六进制显示
		buff[pos++] = HEX[(v & 0xF0) >> 4];
		buff[pos++] = HEX[v & 0x0F];
		buff[pos++] = ' ';

		if (i % 4 == 3) buff[pos++] = ' ';

		//一行结束后的处理
		if (i % 16 == 15 || i >= (size - 1))
		{
			for (int j = 0; pos < 60; ++j)
			{
				buff[pos++] = ' ';
			}

			buff[bound + p + 1] = '\0';
			ss << buff;
			ss << '\n';
		}
	}

	//显示输出
	ss << '\0';
	std::cout << ss.str();
}

void GameUtils::debugBytes(const std::string &data, uint size)
{
	GameUtils::debugBytes((const BYTE*)data.c_str(), size);
}

void GameUtils::debugBytes(const std::string &data)
{
	GameUtils::debugBytes(data, data.length());
}

int GameUtils::readInt(const char *data)
{
	int v, i;

	v = 0;
	for (i = 0; i < 4; i++)
	{
		v = v << 8;
		v += data[i];
	}

	return v;
}

std::string GameUtils::writeInt(int data)
{
	std::string str;

	char buffer[4];

	for (int i = 0; i < 4; i++)
	{
		buffer[3 - i] = ((char*)&data)[i];
	}

	str.append(buffer, 4);

	return str;
}

std::string GameUtils::toHex(uint n)
{
	char temp[9] = { '\0' };

	size_t index = 0;
	while (n)
	{
		temp[7 - index++] = HEX[n % 16];
		n /= 16;
	}

	if (index > 0) return "0x" + std::string(temp + 8 - index);
	else return "0x0";
}

std::string GameUtils::timeString(long t)
{
	if (t < 1) t = GameUtils::timeStamp();

	char str[32];
	struct tm *ptr;
	time_t time = (size_t)t;

	ptr = localtime(&time);
	strftime(str, 32, "%y/%m/%d %H:%M:%S", ptr);

	return std::string(str);
}

std::string GameUtils::msTimeString(uint64 t/*=0*/)
{
	if (t < 1) t = GameUtils::msTimeStamp();
	long time = long(t / 1000);
	std::string r = GameUtils::timeString(time);

	//加入毫秒数
	char str[5];
#ifdef __linux__
	sprintf(str, "%-3d", int(t % 1000));
#else
	sprintf_s(str, 5, "%-3d", int(t % 1000));
#endif
	r.append(":");
	r.append(str);

	return r;
}


std::string GameUtils::changeEncoding(const std::string &source, const std::string &fromCode, const std::string &toCode)
{
#ifdef WIN32
	//源字符串的位置和长度
	const char* c1 = source.c_str();
	size_t s1 = source.size();

	//目标字符串的空间和长度
	size_t s2 = s1 * 2;
	size_t _s2 = s2;  //因为s2会变，缓存一下
	char* buffer = new char[s2];
	char* c2 = buffer;  //因为c2会变，不能直接用buffer
	bool success = true;

	if (s1 > 0)
	{
		iconv_t cd = iconv_open(toCode.c_str(), fromCode.c_str());

		while (s1 > 0)
		{
#ifdef WIN32
			int r = iconv(cd, &c1, &s1, &c2, &s2);
#else
			int r = iconv(cd, (char**)&c1, &s1, &c2, &s2);
#endif
			if (r < 0)
			{
				//std::cerr<<"Error in Iconv, code : "<<errno<<std::endl;
				success = false;
				break;
			}
		}

		iconv_close(cd);
	}

	if (success)	//转码出错
	{
		std::string r(buffer, _s2 - s2);
		delete[] buffer;
		return r;
	}
	else
	{
		delete[] buffer;
		return source;
	}
#else
	return source;
#endif
}


std::string GameUtils::toSF(uint n, uint size)
{
	char* s1 = new char[12];

	int i = 0;
	int v = 0;

	do
	{
		int v = n & 0x3F;
		s1[12 - i - 1] = SF[v];
		n = n >> 6;
		i++;
	} while (n > 0);

	if (size < i) size = i;
	char* s2 = new char[size + 1];
	memset(s2, '0', size);
	memcpy(s2 + size - i, s1 + 12 - i, i);

	(*(s2 + size)) = '\0';
	std::string s3(s2);

	delete[] s1;
	delete[] s2;
	return s3;
}