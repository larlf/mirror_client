#ifndef MM_CORE_H
#define MM_CORE_H

#include "mm_utils.h"

namespace mm
{
	class Stage
	{
	public:
		static IRect Size;  ///< ��ǰ���ڵĴ�С��λ��
	};

	/**
	* �����Ⱦϵͳ
	*/
	class RenderSystem
	{
	public:
		IRect rect;  ///< ��ʾ�ķ�Χ

		/**
		* ���캯��
		* @param rect ��ʾ��λ�úʹ�С
		* @param isFull �Ƿ�ȫ����ʾ
		*/
		RenderSystem(IRect rect, bool isFull);
	};
}

#endif