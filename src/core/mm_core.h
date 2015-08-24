#ifndef MM_CORE_H
#define MM_CORE_H

#include "mm_utils.h"

namespace mm
{
	class Stage
	{
	public:
		static IRect Size;  ///< 当前窗口的大小和位置
	};

	/**
	* 这个渲染系统
	*/
	class RenderSystem
	{
	public:
		IRect rect;  ///< 显示的范围

		/**
		* 构造函数
		* @param rect 显示的位置和大小
		* @param isFull 是否全屏显示
		*/
		RenderSystem(IRect rect, bool isFull);
	};
}

#endif