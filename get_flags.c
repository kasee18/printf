#include "main.h"

/**
 * get_flags - a function that calculates active flags
 * @format: Formatted string in which arguments are printed
 * @i: the given parameter
 * Return: the flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int v, c;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (c = *i + 1; format[c] != '\0'; c++)
	{
		for (v = 0; FLAGS_CH[v] != '\0'; v++)
			if (format[c] == FLAGS_CH[v])
			{
				flags |= FLAGS_ARR[v];
				break;
			}

		if (FLAGS_CH[v] == 0)
			break;
	}

	*i = c - 1;

	return (flags);
}
