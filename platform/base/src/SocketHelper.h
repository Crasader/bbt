﻿#pragma once



#if defined(__linux) || defined(__APPLE__)
inline int GetSocketError() { return errno; }
inline void CloseSocketHandle(SOCKET nSocket) { close(nSocket); }
#endif

#ifdef _MSC_VER
inline int GetSocketError() { return WSAGetLastError(); }
inline void CloseSocketHandle(SOCKET nSocket) { closesocket(nSocket); }
#endif

BOOL    SetSocketNoneBlock(SOCKET nSocket);
SOCKET  ConnectSocket(const char cszIP[], int nPort, int nTimeout, size_t uRecvBufferSize);


BOOL IsSocketAlive(SOCKET nSocket);

#define MAX_HEADER_LEN	5

// 每次调用send时,最多发送的数据量,如果太大,可能会导致EAGAIN错误
#define MAX_SIZE_PER_SEND	((size_t)1024 * 4)
// 实际测试发现,调用recv时传入太大的请求字节数会显著降低性能,目前原因未知
#define MAX_SIZE_PER_RECV	((size_t)1024 * 8)

