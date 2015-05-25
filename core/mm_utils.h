#ifndef MIRROR_UI_UTILS
#define MIRROR_UI_UTILS

#include "mirror.utils.h"


//____________________________________________________________________________

namespace mirror
{
	namespace ui
	{
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
}



#endif