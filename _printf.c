#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - function for the printf
 * @format: given format for the string
 * Return: printed characters
 */
int _printf(const char *format, ...)
{
	int k, p = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);

	for (k = 0, format && format[k] != '\0'; k++)
	{
		if (format[k] != '%')
		{
			buffer[buff_ind++] = format[k];
			if (buff_ind == BUFF_SIZE)
				print_buff(buffer, &buff_ind);
			/* write(1, &format[k], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get flags(format, &k);
			width = get_width(format, &k, list);
			size = get_size(format, &k);
			++k;
			p = handled_print(format, &k, list, buffer, flags, width, precision, size);
			if (p == -1)
				return (-1);
			printed_chars += p;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - a function that prints the contents of buffer if it exists
 * @buffer: char arrays
 * @buff_ind: the index that represents length and to which we add next char
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
