#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base, unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int wid, int prec);

/**
 * convert_sbase - Converts a signed long to an inputted base
 * @output: buffer_t struct containing a character array.
 * @num: signed long to be converted.
 * @base: pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base, unsigned char flags, int wid, int prec)
{
    int size;
    char digit, pad = '0';
    unsigned int retrn = 1;

    for (size = 0; *(base + size);)
        size++;

    if (num >= size || num <= -size)
        retrn += convert_sbase(output, num / size, base, flags, wid - 1, prec - 1);
    else
    {
        for (; prec > 1; prec--, wid--)
            retrn += _memcpy(output, &pad, 1);

        if (NEG == 0)
        {
            pad = (ZERO == 1) ? '0' : ' ';
            for (; wid > 1; wid--)
                retrn += _memcpy(output, &pad, 1);
        }
    }

    digit = base[(num < 0 ? -1 : 1) * (num % size)];
    _memcpy(output, &digit, 1);

    return (retrn);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base
 * @output: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int wid, int prec)
{
    unsigned int size, retrn = 1;
    char digit, pad = '0', *lead = "0x";

    for (size = 0; *(base + size);)
        size++;

    if (num >= size)
        retrn += convert_ubase(output, num / size, base, flags, wid - 1, prec - 1);

    else
    {
        if (((flags >> 5) & 1) == 1)
        {
            wid -= 2;
            prec -= 2;
        }
        for (; prec > 1; prec--, wid--)
            retrn += _memcpy(output, &pad, 1);

        if (NEG == 0)
        {
            pad = (ZERO == 1) ? '0' : ' ';
            for (; wid > 1; wid--)
                retrn += _memcpy(output, &pad, 1);
        }
        if (((flags >> 5) & 1) == 1)
            retrn += _memcpy(output, lead, 2);
    }

    digit = base[(num % size)];
    _memcpy(output, &digit, 1);

    return (retrn);
}