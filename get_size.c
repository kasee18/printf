#include "main.h"

/**
 * get_size - a function that Calculates the size to cast the argument
 * @format: Formatted string in which arguments are printed
 * @i: argument list to be printed
 *
 * Return: Precision
 */
int get_size(const char *format, int *i)
{
	int c = *i + 1;
	int s = 0;

	if (format[c] == 'l')
		s = S_LONG;
	else if (format[c] == 'h')
		s = S_SHORT;

	if (s == 0)
		*i = c - 1;
	else
		*i = c;

	return (s);
}

