#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_s - Converts an argument to a string
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_s(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len)
{
    char *string, *null = "(null)";
    int size;
    unsigned int retrn = 0;

    (void)flags;
    (void)len;

    string = va_arg(args, char *);
    if (string == NULL)
        return (_memcpy(output, null, 6));

    for (size = 0; *(string + size);)
        size++;

    retrn += print_string_width(output, flags, wid, prec, size);

    prec = (prec == -1) ? size : prec;
    while (*string != '\0' && prec > 0)
    {
        retrn += _memcpy(output, string, 1);
        prec--;
        string++;
    }

    retrn += print_neg_width(output, retrn, flags, wid);

    return (retrn);
}

/**
 * convert_S - Converts an argument to a string and stores it to a buffer.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_S(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len)
{
    char *string, *null = "(null)", *hex = "\\x", zero = '0';
    int size, i;
    unsigned int retrn = 0;

    (void)len;
    string = va_arg(args, char *);
    if (string == NULL)
        return (_memcpy(output, null, 6));

    for (size = 0; str[size];)
        size++;

    retrn += print_string_width(output, flags, wid, prec, size);

    prec = (prec == -1) ? size : prec;
    for (i = 0; *(string + i) != '\0' && i < prec; i++)
    {
        if (*(string + i) < 32 || *(string + i) >= 127)
        {
            retrn += _memcpy(output, hex, 2);
            if (*(string + i) < 16)
                retrn += _memcpy(output, &zero, 1);
            retrn += convert_ubase(output, *(string + i), "0123456789ABCDEF", flags, 0, 0);
            continue;
        }
        retrn += _memcpy(output, (string + i), 1);
    }

    retrn += print_neg_width(output, retrn, flags, wid);

    return (retrn);
}

/**
 * convert_r-Reverses a string and stores it to a buffer.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_r(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len)
{
    char *string, *null = "(null)";
    int size, end, i;
    unsigned int retrn = 0;

    (void)flags;
    (void)len;

    string = va_arg(args, char *);
    if (string == NULL)
        return (_memcpy(output, null, 6));

    for (size = 0; *(string + size);)
        size++;

    retrn += string_width_printer(output, flags, wid, prec, size);

    end = size - 1;
    prec = (prec == -1) ? size : prec;
    for (i = 0; end >= 0 && i < prec; i++)
    {
        retrn += _memcpy(output, (string + end), 1);
        end--;
    }

    retrn += neg_width_printer(output, retrn, flags, wid);

    return (retrn);
}

/**
 * convert_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A lenth modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_R(va_list args, buffer_t *output, unsigned char flags, int wid, int prec, unsigned char len)
{
    char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
    char *string, *null = "(null)";
    int i, j, size;
    unsigned int retrn = 0;

    (void)flags;
    (void)len;

    string = va_arg(args, char *);
    if (string == NULL)
        return (_memcpy(output, null, 6));

    for (size = 0; *(string + size);)
        size++;

    retrn += string_width_handler(output, flags, wid, prec, size);

    prec = (prec == -1) ? size : prec;
    for (i = 0; *(string + i) != '\0' && i < prec; i++)
    {
        for (j = 0; j < 52; j++)
        {
            if (*(string + i) == *(alpha + j))
            {
                retrn += _memcpy(output, (rot13 + j), 1);
                break;
            }
        }
        if (j == 52)
            retrn += _memcpy(output, (string + i), 1);
    }

    retrn += neg_width_printer(output, retrn, flags, wid);

    return (retrn);
}