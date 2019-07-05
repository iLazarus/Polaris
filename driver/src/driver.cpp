#include "driver.h"

driver::driver()
{
	hDriver = CreateFileA("\\\\.\\KingSoft", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		printf("[!] Driver Install Failed\n");
	}
	else
	{
		printf("[!] Driver Install Successed\n");
	}
}


driver::~driver()
{
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDriver);
		printf("[!] Driver UnInstall Successed\n");
	}
}

unsigned long long driver::GetGameModule()
{
	if (hDriver == INVALID_HANDLE_VALUE) return 0;
	unsigned long long readBuffer;
	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)&readBuffer,
		(unsigned long long)0x0,
		sizeof(unsigned long long),
		(unsigned long)GetCurrentProcessId(),
		0
	};
	int stat = DeviceIoControl(
		hDriver,
		IO_GET_MODULE_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0);
	return stat ? readBuffer : 0;
}

unsigned long driver::GetGamePid()
{
	if (hDriver == INVALID_HANDLE_VALUE) return 0;
	unsigned long readBuffer;
	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)&readBuffer,
		(unsigned long long)0x0,
		sizeof(unsigned long long),
		(unsigned long)GetCurrentProcessId(),
		0
	};
	int stat = DeviceIoControl(
		hDriver,
		IO_GET_PID_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0);
	return stat ? readBuffer : 0;
}

unsigned long long driver::GetImageSize()
{
	if (hDriver == INVALID_HANDLE_VALUE) return 0;
	unsigned long long readBuffer;
	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)&readBuffer,
		(unsigned long long)0x0,
		sizeof(unsigned long long),
		(unsigned long)GetCurrentProcessId(),
		0
	};
	int stat = DeviceIoControl(
		hDriver,
		IO_GET_IMAGESIZE_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0);
	return stat ? readBuffer : 0;
}
