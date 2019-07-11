#include "pattern.h"
#include <stdlib.h>

int FormatPattern(const char *src, unsigned char *out)
{
	while (*src == ' ') src++;
	int cur = 0;
	bool h = false;
	bool l = false;
	while (*src)
	{
		const char c = *(src++);
		int ic = 0;
		if (c >= '0' && c <= '9')
		{
			if (!h)
			{
				ic = c - '0';
				out[cur] = ic * 16;
				h = true;
			}
			else if (!l)
			{
				ic = c - '0';
				out[cur] += ic;
				h = false;
				l = false;
			}

		}
		if (c >= 'a' && c <= 'f')
		{
			if (!h)
			{
				ic = c - 'a' + 10;
				out[cur] = ic * 16;
				h = true;
			}
			else if (!l)
			{
				ic = c - 'a' + 10;
				out[cur] += ic;
				h = false;
				l = false;
			}
		}
		if (c >= 'A' && c <= 'Z')
		{
			if (!h)
			{
				ic = c - 'A' + 10;
				out[cur] = ic * 16;
				h = true;
			}
			else if (!l)
			{
				ic = c - 'A' + 10;
				out[cur] += ic;
				h = false;
				l = false;
			}
		}
		if (c == ' ')
		{
			if (h && !l)
			{
				out[cur] = out[cur] / 16;
			}
			h = false;
			l = false;
		}
		if (c == '?')
		{
			if (!h)
			{
				out[cur] = 0;
				h = true;
			}
			else if (!l)
			{
				out[cur] += 0;
				h = false;
				l = false;
			}
		}
		if (*src && !h && !l && *src != ' ')
		{
			cur++;
		}
	}
	return cur;
}

long long FindPattern(unsigned char *data, int searchLength, const char *signature, unsigned long long *result)
{
	int ret = 0;
	unsigned char *sig = 0;
	sig = (unsigned char *)malloc(1024);
	if (!sig) throw "variable initialization memory failed in function [FindPattern]";
	int signatureLength = FormatPattern(signature, sig) + 1;
	if (!signatureLength) {
		free(sig);
		sig = nullptr;
		return ret;
	}
	unsigned char *headerCursor = data;
	unsigned char *buffer = data;
	unsigned char *max = buffer + searchLength - signatureLength;
	unsigned char first = sig[0];
	int last = signatureLength - 1;
	for (; buffer < max; ++buffer)
	{
		if (*buffer != first) continue;
		for (int i = 0; i < signatureLength; i++)
		{
			if (i == last)
			{
				if (sig[last] == '\x00' || sig[last] == buffer[i])
				{
					if (buffer - headerCursor < 0x0fffffff)
					{
						result[ret++] = buffer - headerCursor;
						if (ret > 0x1FFFF)
						{
							free(sig);
							sig = 0;
							return ret;
						}
					}


				}
			}
			if (sig[i] == '\x00') continue;
			if (buffer[i] != sig[i]) break;
		}
	}

	free(sig);
	sig = nullptr;
	return ret;
}

unsigned long long FindPattern(unsigned char *data, int searchLength, const char *signature)
{
	return FindPattern(data, searchLength, signature, 1);
}

unsigned long long FindPattern(unsigned char *data, int searchLength, const char *signature, int findcount)
{
	int iFoundCount = 1;
	unsigned long long ret = 0;
	unsigned char *sig = 0;
	sig = (unsigned char *)malloc(1024);
	if (!sig) throw "variable initialization memory failed in function [FindPattern]";
	int signatureLength = FormatPattern(signature, sig) + 1;
	if (!signatureLength) {
		free(sig);
		sig = 0;
		return ret;
	}
	unsigned char *headerCursor = data;
	unsigned char *buffer = data;
	unsigned char *max = buffer + searchLength - signatureLength;
	unsigned char first = sig[0];
	int last = signatureLength - 1;
	for (; buffer < max; ++buffer)
	{
		if (*buffer != first) continue;
		for (int i = 0; i < signatureLength; i++)
		{
			if (i == last)
			{
				if (sig[last] == '\x00' || sig[last] == buffer[i])
				{
					if (buffer - headerCursor < 0x0fffffff && iFoundCount++ == findcount)
					{
						ret = buffer - headerCursor;
						free(sig);
						sig = 0;
						return ret;
					}

				}
			}
			if (sig[i] == '\x00') continue;
			if (buffer[i] != sig[i]) break;
		}
	}

	free(sig);
	sig = 0;
	return ret;
}