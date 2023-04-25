#include "main.h"

/**
 * _printf - Print function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, flags, width, precision, size;
	int printed = 0, printed_chars = 0, buff_i = 0;

	va_list ap;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(ap, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_i++] = format[i];
			if (buff_i == BUFF_SIZE)
				print_buffer(buffer, &buff_i);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, ap);
			precision = get_precision(format, &i, ap);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, ap, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_i);
	va_end(ap);
	return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_i: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_i)
{
	if (*buff_i > 0)
		write(1, &buffer[0], *buff_i);
	*buff_i = 0;
}
