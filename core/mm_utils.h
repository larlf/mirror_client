#ifndef MIRROR_UI_UTILS
#define MIRROR_UI_UTILS

#include "mm_const.h"
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>

#ifdef WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif



//下面是一些用于输出调试信息的宏
#ifdef WIN32

#ifdef DEBUG
#define LOG_DEBUG(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<"  | "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<mm::GameUtils::changeEncoding(__FUNCTION____LINE__.str(), "UTF-8", "GBK")<<std::flush; }
#else
#define LOG_DEBUG(p1)
#endif
#define LOG_INFO(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<" .| "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<mm::GameUtils::changeEncoding(__FUNCTION____LINE__.str(), "UTF-8", "GBK")<<std::flush; }
#define LOG_ERROR(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<"><| "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<mm::GameUtils::changeEncoding(__FUNCTION____LINE__.str(), "UTF-8", "GBK")<<std::flush; }

#else

#ifdef DEBUG
#define LOG_DEBUG(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<"  | "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<__FUNCTION____LINE__.str()<<std::flush; }
#else
#define LOG_DEBUG(p1)
#endif
#define LOG_INFO(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<" .| "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<__FUNCTION____LINE__.str()<<std::flush; }
#define LOG_ERROR(p1)	{ std::ostringstream __FUNCTION____LINE__; __FUNCTION____LINE__<<"><| "<<mm::GameUtils::msTimeString()<<" | "<<p1<<" ... "<<__FILE__<<":"<< __FUNCTION__<<"():"<<__LINE__<<std::endl; std::cout<<__FUNCTION____LINE__.str()<<std::flush; }

#endif

//____________________________________________________________________________

namespace mm
{

	/**
	* 一些不好分类的公用方法
	*/
	class GameUtils
	{
	private:
		static size_t SqlCharSize;							///< 上个数组的长度

	public:
		static int readInt(const char *data);
		static std::string writeInt(int data);

		/**
		* 以二进制的方式显示一个字符串的信息
		*/
		static void debugBytes(const BYTE *data, uint size);
		static void debugBytes(const std::string &data, uint size);
		static void debugBytes(const std::string &data);
		static std::string toHex(uint n);
		static std::string toSF(uint n, uint size);
		static std::string toSF(uint n) { return GameUtils::toSF(n, 0); }
		static std::string changeEncoding(const std::string &source, const std::string &fromCode, const std::string &toCode);

		//递增生成ID
		static uint makeID(uint &idIndex, uint mask = 0xFFFFFFFF)
		{
			idIndex++;
			if (idIndex >= mask || !idIndex) idIndex = 1;
			return idIndex;
		}

		static long timeStamp() { return (long)time(0); }
		static uint64 msTimeStamp()
		{
#ifdef WIN32
			struct timeb tp;
			ftime(&tp);
			return tp.time * 1000 + tp.millitm;
#else
			struct timeval t;
			gettimeofday(&t, 0);
			uint64 s = time(0);
			return s * 1000 + (t.tv_usec / 1000);
#endif
		}

		static std::string timeString(long t = 0);
		static std::string msTimeString(uint64 t = 0);

		//地图计算相关
		inline static double distance(int x1, int y1, int x2, int y2)
		{
			return sqrt(pow(abs(double(x1 - x2)), 2) + pow(abs(double(y1 - y2)), 2));
		}

		inline static double P2PAngle(int x1, int y1, int x2, int y2)
		{
			return atan2(double(y2 - y1), double(x2 - x1));
		};

		inline static int distanceX(double distance, double angle)
		{
			return (int)(cos(angle)*distance);
		}

		inline static int distanceY(double distance, double angle)
		{
			return (int)(sin(angle)*distance);
		}

		inline static int angle28Dir(double angle)
		{
			int n = (int(angle * 180 / PI + 450) % 360) / 45;
			if (n>7) n = 0;
			return n;
		};

		inline static int P2P28Dir(int x1, int y1, int x2, int y2)
		{
			return angle28Dir(P2PAngle(x1, y1, x2, y2));
		}
	};

	//文件处理相关的公用方法
	class FileUtils
	{
	public:
		static std::string readTextFile(const std::string& filename);
	};


	class Point
	{
	public:
		long x;
		long y;
		Point() : x(0), y(0) {}
		Point(long x, long y) : x(x), y(y) {}
	};

	class Rect
	{
	public:
		long x;
		long y;
		long w;
		long h;
		Rect() : x(0), y(0), w(0), h(0) {}
		Rect(long x, long y, long w, long h) : x(x), y(y), w(w), h(h) {}
	};

	class UIUtils
	{
	private:
		static unsigned int idIndex;
	public:
		//生成一个新的ID
		static std::string newId();
	};
}



#endif