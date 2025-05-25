
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

#include "substr.h"

#include <stdlib.h>
#include <string.h>

char *substr(const char *str, int start_index, int end_index)
{

    char *substring = NULL;
    int len = 0;
    int substr_len = 0;

    if ((str == NULL) || (str[0] == '\0')) {
        return NULL;
    }

    len = (int)(strnlen(str, STR_LIB_MAX_STR_SIZE_ALLOWED));

    if (len == STR_LIB_MAX_STR_SIZE_ALLOWED) {
        return NULL;
    }

    if ((end_index < 0) || (end_index > (len - 1))) {
        end_index = len - 1;
    }

    if ((start_index < 0) || (start_index > (len - 1)) ||
        (end_index < start_index)) {
        return NULL;
    }

    substr_len = end_index - start_index + 1;

    // extra 1 byte for null terminating character
    substring = calloc((size_t)(substr_len + 1), 1);

    if (substring == NULL) {
        return NULL;
    }

    memmove(substring, str + start_index, (size_t)(substr_len));

    substring[substr_len] = '\0';

    return substring;

} // end of function substr()

