
/*
 * License:
 *
 * This file has been released under "unlicense" license
 * (https://unlicense.org).
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non-commercial, and by any means.
 *
 * For more information about this license, please visit - https://unlicense.org
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#ifndef _SUBSTR_H_
#define _SUBSTR_H_

// Change this value to process more characters.
#define STR_LIB_MAX_STR_SIZE_ALLOWED 8192 // includes null terminating character

#define STR_LIB_MIN_STR_SIZE_ALLOWED 1 // includes null terminating character.
                                       // string returned will be empty if its
                                       // size is STR_LIB_MIN_STR_SIZE_ALLOWED

#define STR_LIB_SUCCESS  1
#define STR_LIB_FAILURE -1

#define STR_LIB_NUM_TRUE  2
#define STR_LIB_NUM_FALSE -2

// The size of the integer string is 10 (including null terminating character)
// so this means that the max number of digits in this string can be 9. If we
// keep the max number of digits as 10 then in some cases, all these digits can
// be 9 and in these cases when we convert the string to integer then there will
// be integer overflow because 9999999999 (9 is 10 times) is greater than
// INT_MAX. So, to prevent the integer overflow we have limited the max number
// of integer digits in the string to 9. Since the string will be null
// terminated, so accounting for the null terminating character, the size of the
// integer string becomes 10.
#define STR_LIB_INTEGER_STR_SIZE 10 // includes null terminating character

/*
 * char *substr(const char *str, int start_index, int end_index):
 *
 * Function substr() allocates memory for the substring and returns a pointer to
 * this substring which is a copy of characters of 'str' from 'start_index' to
 * 'end_index' (including the character at 'end_index'). This substring is
 * terminated by the null character.
 *
 * If the 'end_index' is negative or greater than the last index of 'str' then
 * 'end_index' is normalized which means that 'end_index' is set to the last
 * index of 'str' (length_of_str - 1).
 *
 * This function returns NULL in the following error cases:
 *
 *      ** 'str' is NULL.
 *      ** The first character of 'str' is the null terminating character (means
 *         that 'str' is an empty string).
 *      ** length of 'str' is greater than 'STR_LIB_MAX_STR_SIZE_ALLOWED - 1'.
 *      ** 'start_index' is less than zero (0).
 *      ** 'start_index' is greater than the last index of 'str' (length_of_str
 *         -1).
 *      ** After normalization of 'end_index' (as explained above), 'end_index'
 *         is less than 'start_index'.
 *
 * It is necessary to check the return value of this functon for NULL before
 * proceeding ahead.
 *
 * The memory for the substring is allocated using calloc(), so it is the user's
 * responsibility to free this memory.
 */
char *substr(const char *str, int start_index, int end_index);

#endif

