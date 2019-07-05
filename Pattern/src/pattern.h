/****************************************************************
*
* Author: JoyShow ye4tar@gmail.com
*
****************************************************************/
#pragma once

#ifndef PATTERN_H
#define PATTERN_H

/* format pattern from char to bytecode
	*src [IN] signature string
	*out [OUT] signarure bytecode
	return [RET] length of bytecode
*/
int FormatPattern(const char *src, unsigned char *out);

/* search pattern  [OverLoad]
	*data [IN] source data for search
	searchLength [IN] search length
	*signature [IN] search signature
	*result [OUT] search found offset collection
	return [RET] search count
*/
long long FindPattern(unsigned char *data, int searchLength, const char *signature, unsigned long long *result);

/* search pattern [OverLoad]
	*data [IN] source data for search
	searchLength [IN] search length
	*signature [IN] search signature
	return [RET] just first one search found offset
*/
unsigned long long FindPattern(unsigned char *data, int searchLength, const char *signature);
unsigned long long FindPattern(unsigned char *data, int searchLength, const char *signature, int findcount);

#endif // !PATTERN_H


