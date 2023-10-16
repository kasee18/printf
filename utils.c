#include "main.h"

/**
 * is_printable - a function that evaluates if a char is printable
 * @c: Character evaluated
 *
 * Return: 1 if c is printable, 0 if else
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appending ascci in hexadecimal code to buffer
 * @buffer: characters array
 * @i: index from which appending starts
 * @ascii_code: ASSCI CODE
 * Return: 3 (success)
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char mapping_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = mapping_to[ascii_code / 16];
	buffer[i] = mapping_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - a function that verifies if a char is a digit
 * @c: evaluated character
 *
 * Return: 1 if c is a digit, 0 if else
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - a function that casts a number to the specified size
 * @num: integer to be casted
 * @size: an integer indicating the type to be casted
 *
 * Return: the casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - a function that asts a number to the specified size
 * @num: integer that is to be casted
 * @size: integer that indicates the type to be casted
 *
 * Return: the value of casted num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
