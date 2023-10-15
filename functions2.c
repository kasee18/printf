#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - a function that prints the value of a pointer variable
 * @types: argument list
 * @buffer: array of buffer to handle print
 * @flags: calculates flags that are active
 * @width: specifier that gets the width
 * @precision: specification for precision
 * @size: specifier to talk about size
 * @Return: character count printed
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = 0, p = ' ';
	int ind = BUFF_SIZE - 2, length = 2, p_start = 1; /* length=2, for '0x' */
	unsigned long num_address;
	char map_it_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[ind--] = map_it_to[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (flags & F_PLUS)
		c = '+', length++;
	else if (flags & F_SPACE)
		c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, p, c, p_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Printing ascii codes in hexa of non printable chars
 * @types: argument list
 * @buffer: array buffer to handle print
 * @flags:  Calculating active flags
 * @width: obtaining the width
 * @precision: specifying precision
 * @size: specifier for size
 * Return: count of printed chars
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = 0, v = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[k] != '\0')
	{
		if (is_printable(str[k]))
			buffer[k + v] = str[k];
		else
			v += append_hexa_code(str[k], buffer, k + v);

		k++;
	}

	buffer[k + v] = '\0';

	return (write(1, buffer, k + v));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - a function that Prints a reversed string
 * @types: argument list
 * @buffer: array buffer to handle print
 * @flags:  geting active flags
 * @width: width calculation
 * @precision: Precision specification
 * @size: specification of size
 * Return: Numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, total_count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (k = 0; str[k]; k++)
		;

	for (k = k - 1; k >= 0; k--)
	{
		char z = str[k];

		write(1, &z, 1);
		total_count++;
	}
	return (total_count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * * print_rot13string - Printing a string in rot13
 * @types: argument list
 * @buffer: Buffer of array for handling print
 * @flags: Calculation of active flags
 * @width: geting the width
 * @precision: Precision specification
 * @size: Size specification
 * Return: Numbers of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char p;
	char *str;
	unsigned int k, v;
	int total_count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (k = 0; str[k]; k++)
	{
		for (v = 0; in[v]; v++)
		{
			if (in[v] == str[k])
			{
				p = out[v];
				write(1, &x, 1);
				total_count++;
				break;
			}
		}
		if (!in[v])
		{
			p = str[k];
			write(1, &x, 1);
			total_count++;
		}
	}
	return (total_count);
}
