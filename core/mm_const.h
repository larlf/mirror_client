#ifndef MM_CONST_H
#define MM_CONST_H

#define PTR std::shared_ptr

#ifdef __cplusplus
extern "C" {
#endif

	typedef unsigned char		BYTE;		///< 字节数据类型
	typedef unsigned int		uint;		///< 无符号整数
	typedef unsigned long long	uint64;		///< 64位的无符号数
	typedef long long			int64;		///< 64位数字

	static double PI = 3.14159265358979323846;	///< PI
	static char HEX[] = "0123456789ABCDEF";
	static char hex[] = "0123456789abcdef";
	static char SF[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~";
	static char FirstKey[] = "xNNdjNrj8fuSBT4V7Ig2pUdpYvPmrbgQnHMbnu2cgVHBocFJ456uHQoRN01zP1EF";

#ifdef __cplusplus
}
#endif

//C语言下需要处理的内容
#ifndef __cplusplus
#if defined(WIN32)
#define inline __inline
#endif
#endif

#endif