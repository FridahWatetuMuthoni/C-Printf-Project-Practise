#include "main.h"

void cleanup_function(va_list args, buffer_t *output);
int runing_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup_function - Peforms cleanup operations for _printf.
 * @args: arguments provided to _printf.
 * @output: A buffer_t struct.
 */
void cleanup_function(va_list args, buffer_t *output)
{
    va_end(args);
    write(1, output->start, output->len);
    free_buffer(output);
}

/**
 * run_printf - Reads through the format string for _printf.
 * @format: string to print
 * @output: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments.
 *
 * Return: The number of characters stored to output.
 */
int runing_printf(const char *format, va_list args, buffer_t *output)
{
    int i, wild, precision, retrn = 0;
    char temp;
    unsigned char flags, length;
    unsigned int (*f)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

    for (i = 0; *(format + i); i++)
    {
        length = 0;
        if (*(format + i) == '%')
        {
            temp = 0;
            flags = flag_handler(format + i + 1, &temp);
            wild = width_handler(args, format + i + temp + 1, &temp);
            precision = precision_handler(args, format + i + temp + 1, &temp);
            length = length_handler(format + i + temp + 1, &temp);

            f = specifiers_handler(format + i + temp + 1);
            if (f != NULL)
            {
                i += temp + 1;
                retrn += f(args, output, flags, wild, precision, length);
                continue;
            }
            else if (*(format + i + temp + 1) == '\0')
            {
                retrn = -1;
                break;
            }
        }
        retrn += _memcpy(output, (format + i), 1);
        i += (length != 0) ? 1 : 0;
    }
    cleanup_function(args, output);
    return (retrn);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
    buffer_t *output;
    va_list args;
    int retrn;

    if (format == NULL)
        return (-1);
    output = init_buffer();
    if (output == NULL)
        return (-1);

    va_start(args, format);

    retrn = runing_printf(format, args, output);

    return (retrn);
}