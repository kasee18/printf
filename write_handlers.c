#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - a function that Prints a string
 * @c: character
 * @buffer: array of buffer
 * @flags:  Calculating active flags
 * @width: calculating width
 * @precision: precision specifier
 * @size: Size specification
 *
 * Return: Number of characters to be printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* character is stored at left and paddind at buffer's right */
	int k = 0;
	char p = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		p = '0';

	buffer[k++] = c;
	buffer[k] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buffer[BUFF_SIZE - k - 2] = p;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - a function that Prints a string
 * @is_negative argument list
 * @ind: characters
 * @buffer: Buffer of array
 * @flags:  Calculating the active flags
 * @width: width calculation
 * @precision: precision specification
 * @size: Size specification
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char p = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, p, extra_ch));
}

/**
 * write_num - a function that Writes a number using a bufffer
 * @ind: Index from which the number starts at buffer
 * @buffer: the given buffer
 * @flags: given flags
 * @width: width calculation
 * @prec: Precision specification
 * @length: length calculation
 * @padd: Pading character
 * @extra_c: Extra character
 *
 * Return: Number of characters printed
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int k, p_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no character is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (k = 1; k < width - length + 1; k++)
			buffer[k] = padd;
		buffer[k] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], k - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--p_start] = extra_c;
			return (write(1, &buffer[p_start], k - p_start) +
				write(1, &buffer[ind], length - (1 - p_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - a function that writes an unsigned integer
 * @is_negative: an integer indicating if the number is negative
 * @ind: start of the number in the buffer
 * @buffer: Array of characters
 * @flags: Flags specification
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specification
 *
 * Return: count of written characters
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, k = 0;
	char p = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no character is printed */

	if (precision > 0 && precision < length)
		p = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';

	if (width > length)
	{
		for (k = 0; k < width - length; k++)
			buffer[k] = p;

		buffer[k] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], k));
		}
		else
		{
			return (write(1, &buffer[0], k) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writing memory address
 * @buffer: Arrays of characters
 * @ind: start of the number in the buffer
 * @length: number length
 * @width: Wwidth specification
 * @flags: Flags specification
 * @padd: representation of the padding by a char
 * @extra_c: representation of extra characters
 * @padd_start: index from which padding starts
 *
 * Return: written character count
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[kasee] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], kasee - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], kasee - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
