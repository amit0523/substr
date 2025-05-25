
File substr.c implements a function called substr() to get a subtring from a
string. The signature of this function is:

    char *substr(const char *str, int start_index, int end_index)

Function substr() allocates memory for the substring and returns a pointer to
this substring which is a copy of characters of 'str' from 'start_index' to
'end_index' (including the character at 'end_index'). This substring is
terminated by the null character.

If the 'end_index' is negative or greater than the last index of 'str' then
'end_index' is normalized which means that 'end_index' is set to the last index
of 'str' (length_of_str - 1).

This function returns NULL in the following error cases:

     ** 'str' is NULL.
     ** The first character of 'str' is the null terminating character (means
        that 'str' is an empty string).
     ** length of 'str' is greater than 'STR_LIB_MAX_STR_SIZE_ALLOWED - 1'.
     ** 'start_index' is less than zero (0).
     ** 'start_index' is greater than the last index of 'str' (length_of_str
        -1).
     ** After normalization of 'end_index' (as explained above), 'end_index'
        is less than 'start_index'.

It is necessary to check the return value of this functon for NULL before
proceeding ahead.

The memory for the substring is allocated using calloc(), so it is the user's
responsibility to free this memory.

---- End of README ----
