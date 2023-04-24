#include "main.h"

unsigned int width_printer(buffer_t *output, unsigned int printed, unsigned char flags, int wid);
unsigned int string_width_printer(buffer_t *output, unsigned char flags, int wid, int prec, int size);
unsigned int neg_width_printer(buffer_t *output, unsigned int printed, unsigned char flags, int wid);

/**
 * width_printer - Stores leading spaces to buffer for the width modifier.
 * @output: A buffer_t struct that contains a character array.
 * @printed: The current number of characters already printed.
 * @flags: Flag modifiers.
 * @wid:width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int width_printer(buffer_t *output, unsigned int printed, unsigned char flags, int wid)
{
    unsigned int retrn = 0;
    char width = ' ';

    if (NEG == 0)
    {
        for (wid -= printed; wid > 0;)
            retrn += _memcpy(output, &width, 1);
    }

    return (retrn);
}

/**
 * string_width_printer - Stores leading spaces to a buffer.
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * @prec: precision modifier.
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int string_width_printer(buffer_t *output, unsigned char flags, int wid, int prec, int size)
{
    unsigned int retrn = 0;
    char width = ' ';

    if (NEG == 0)
    {
        wid -= (prec == -1) ? size : prec;
        for (; wid > 0; wid--)
            retrn += _memcpy(output, &width, 1);
    }

    return (retrn);
}

/**
 * neg_width_printer - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct with a character array.
 * @printed: The current number of bytes already stored
 * @flags: Flag modifier.
 * @wid: width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int neg_width_printer(buffer_t *output, unsigned int printed, unsigned char flags, int wid)
{
    unsigned int retrn = 0;
    char width = ' ';

    if (NEG == 1)
    {
        for (wid -= printed; wid > 0; wid--)
            ret += _memcpy(output, &width, 1);
    }

    return (retrn);
}