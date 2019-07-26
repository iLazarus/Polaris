#pragma once 
#ifndef DRIVER_H
#define DRIVER_H

#include <Windows.h>
#include <winioctl.h>
#include <stdio.h>

// driver function and ctl_code define
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //read
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //write
#define IO_GET_PID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //getPid
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //getModule
#define IO_GET_IMAGESIZE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //getModule

//driver r/w struct
typedef struct _IOBUFFER
{
	unsigned long long UserBufferAdress;
	unsigned long long GameAddressOffset;
	unsigned long long Size;
	unsigned long      UserPID;
	unsigned long      GamePID;
} IOBUFFER, *PIOBUFFER;

class driver
{
public:
	driver();
	~driver();

	unsigned long long GetGameModule();
	unsigned long GetGamePid();
	unsigned long long GetImageSize();

	template <typename T> inline T RPM(unsigned long long Addr);
	template <typename T> inline T RPM(unsigned long long Addr, unsigned long Size);
	template <typename T> inline bool RPM(unsigned long long Addr, T OuterBuffer, unsigned long Size);
	template <typename T> inline bool WPM(unsigned long long Addr, T value);
	template <typename T> inline bool WPM(unsigned long long Addr, T value, unsigned long Size);

protected:
	void* hDriver;

};

template<typename T>
inline T driver::RPM(unsigned long long Addr)
{
	T readBuffer = 0;

	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)&readBuffer,
		(unsigned long long)Addr,
		sizeof(T),
		(unsigned long)GetCurrentProcessId(),
		0
	};
	DeviceIoControl(
		hDriver,
		IO_READ_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0);
	return (T)readBuffer;
}

template<typename T>
inline T driver::RPM(unsigned long long Addr, unsigned long Size)
{
	T readBuffer = {};

	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)&readBuffer,
		(unsigned long long)Addr,
		Size,
		(unsigned long)GetCurrentProcessId(),
		0
	};
	DeviceIoControl(
		hDriver,
		IO_READ_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0);
	return (T)readBuffer;
}

template<typename T>
inline bool driver::RPM(unsigned long long Addr, T OuterBuffer, unsigned long Size)
{
	unsigned long Bytes;
	_IOBUFFER ReadRequest
	{
		(unsigned long long)OuterBuffer,
		(unsigned long long)Addr,
		Size,
		(unsigned long)GetCurrentProcessId(),
		0
	};
	return DeviceIoControl(
		hDriver,
		IO_READ_REQUEST,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		0); 
}

template<typename T>
inline bool driver::WPM(unsigned long long Addr, T value)
{
	T writeBuffer = value;
	unsigned long Bytes;
	_IOBUFFER  WriteRequest
	{
		(unsigned long long)&writeBuffer,
		(unsigned long long)Addr,
		sizeof(T),
		(unsigned long)GetCurrentProcessId(),
		0
	};
	return DeviceIoControl(
		hDriver,
		IO_WRITE_REQUEST,
		&WriteRequest,
		sizeof(WriteRequest),
		&WriteRequest,
		sizeof(WriteRequest),
		&Bytes,
		0); 
}

template<typename T>
inline bool driver::WPM(unsigned long long Addr, T value, unsigned long Size)
{
	unsigned long Bytes;
	_IOBUFFER  WriteRequest
	{
		(unsigned long long)value,
		(unsigned long long)Addr,
		Size,
		(unsigned long)GetCurrentProcessId(),
		0
	};

	return DeviceIoControl(
		hDriver,
		IO_WRITE_REQUEST,
		&WriteRequest,
		sizeof(WriteRequest),
		&WriteRequest,
		sizeof(WriteRequest),
		&Bytes,
		0); 
}

#endif