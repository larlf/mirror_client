#ifndef MM_CONST_H
#define MM_CONST_H

#define PTR std::shared_ptr

#ifdef __cplusplus
extern "C" {
#endif

	typedef unsigned char		BYTE;		///< �ֽ���������
	typedef unsigned int		uint;		///< �޷�������
	typedef unsigned long long	uint64;		///< 64λ���޷�����
	typedef long long			int64;		///< 64λ����

	static double PI = 3.14159265358979323846;	///< PI
	static char HEX[] = "0123456789ABCDEF";
	static char hex[] = "0123456789abcdef";
	static char SF[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~";
	static char FirstKey[] = "xNNdjNrj8fuSBT4V7Ig2pUdpYvPmrbgQnHMbnu2cgVHBocFJ456uHQoRN01zP1EF";

#ifdef __cplusplus
}
#endif

//C��������Ҫ���������
#ifndef __cplusplus
#if defined(WIN32)
#define inline __inline
#endif
#endif

#endif