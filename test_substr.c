
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               int size);
static void discard_all_characters_from_stdin(void);
static int is_str_an_integer(const char *str);
static int get_integer_input_from_user(char *str, int size, int *integer_ptr);

int main(void)
{

    char str[STR_LIB_MAX_STR_SIZE_ALLOWED] = {0};
    char num_str[STR_LIB_INTEGER_STR_SIZE] = {0};
    int start_index = -1;
    int end_index = -1;
    char *arg_str = NULL;
    char *sub_str = NULL;
    char *retval_char = NULL;
    int retval_num = STR_LIB_FAILURE;

    while (1) {

        // get the string from the user
        while (1) {

            printf("\nPlease input a string from which to get the substring"
                    " (max %d characters else the input string will be"
                    " truncated to %d characters) (To enter NULL string, type"
                    " NULL (in capital letters)): ",
                    STR_LIB_MAX_STR_SIZE_ALLOWED - 1,
                    STR_LIB_MAX_STR_SIZE_ALLOWED - 1);

            retval_char = get_input_from_stdin_and_discard_extra_characters(str,
                                                STR_LIB_MAX_STR_SIZE_ALLOWED);

            if (retval_char == NULL) {
                printf("\n\nNo input received. Please try again..\n");
                continue;
            }

            if (strncmp(str, "NULL", (strlen("NULL") + 1)) == 0) {
                arg_str = NULL;
            } else {
                arg_str = str;
            }

            break;

        } // end of while (1) loop for getting the string

        printf("\n");

        // get the start_index from the user
        while (1) {

            printf("Please input the start index from which to start copying"
                   " the substring: ");

            retval_num = get_integer_input_from_user(num_str,
                                    STR_LIB_INTEGER_STR_SIZE, &start_index);

            if (retval_num != STR_LIB_SUCCESS) {
                continue;
            }

            break;

        } // end of while (1) loop for getting the start_index

        printf("\n");

        // get the end_index from the user
        while (1) {

            printf("Please input the end index at which to stop copying"
                   " the substring: ");

            retval_num = get_integer_input_from_user(num_str,
                                    STR_LIB_INTEGER_STR_SIZE, &end_index);

            if (retval_num != STR_LIB_SUCCESS) {
                continue;
            }

            break;

        } // end of while (1) loop for getting the end_index

        printf("\n");
        printf("\n-------\n");
        printf("Output:");
        printf("\n-------\n");
        
        // using strlen() here is safe because it is guranteed that 'str' is
        // null terminated.
        printf("\nInput parameters: str=\"%s\", start_index=%d, end_index=%d"
               " (length_of_str = ", arg_str ? arg_str: "(null string)",
               start_index, end_index);
        if (arg_str) {
            printf("%d)\n", (int)(strlen(arg_str)));
        } else {
            printf("INVALID)\n");
        }
        printf("\n");
        sub_str = substr(arg_str, start_index, end_index);
        if (sub_str) {
            // using strlen() here is safe because it is guranteed that sub_str
            // is null terminated.
            printf("** substr = \"%s\" (length_of_substr = %d)\n", sub_str,
                   (int)(strlen(sub_str)));
            free(sub_str);
            sub_str = NULL;
        } else {
            printf("** substr() returned NULL. It looks like one or more user"
                   " inputs were invalid. **\n");
        }

        printf("\nPlease press ENTER to continue..");
        // now clear the stdin input buffer
        discard_all_characters_from_stdin();

    } // end of outermost while(1) loop

} // end of main

/*
 * get_input_from_stdin_and_discard_extra_characters():
 *
 *      Function get_input_from_stdin_and_discard_extra_characters() reads at
 *      most (size - 1) characters from stdin and stores them in 'str'.
 *      One character is used to null terminate 'str'. The rest of the
 *      remaining characters in stdin are read and discarded, they are not
 *      stored in 'str'. So, when this function returns then there is no
 *      input/characters left in stdin.
 *
 *      If 'str' is NULL then it is an error and nothing is read from stdin and
 *      NULL is returned.
 *
 *      If 'size' is greater than 'STR_LIB_MAX_STR_SIZE_ALLOWED' or less than
 *      'STR_LIB_MIN_STR_SIZE_ALLOWED' then it is an error and nothing is read
 *      from stdin and NULL is returned.
 */
static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               int size)
{

    int c = 0;
    int i = 0;

    if (str == NULL) {
        return NULL;
    }

    if ((size < STR_LIB_MIN_STR_SIZE_ALLOWED) ||
        (size > STR_LIB_MAX_STR_SIZE_ALLOWED)) {
        return NULL;
    }

    for (i = 0; i < (size - 1); i = i + 1) {

        c = getchar();

        if ((c == '\n') || (c == EOF)) {
            str[i] = 0;
            return str;
        }

        str[i] = (char)(c);

    } // end of for loop

    str[i] = 0;

    // discard the rest of the input
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return str;

} // end of function get_input_from_stdin_and_discard_extra_characters()

static void discard_all_characters_from_stdin(void)
{

    int c = 0;

    // discard all characters from stdin
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return;

} // end of function discard_all_characters_from_stdin()

/*
 * is_str_an_integer():
 *
 *      Function is_str_an_integer() expects only numeric characters in 'str'
 *      and optionally a leading '+' or '-' character.
 *
 *      This function returns STR_LIB_NUM_TRUE when all of the following
 *      conditions are met:
 *
 *              ** 'str' is not null.
 *              ** The first character of 'str' is not the null terminating
 *                 character (means 'str' is not an empty string).
 *              ** Length of 'str' is less than 'STR_LIB_INTEGER_STR_SIZE'.
 *              ** 'str' contains only numeric characters and optionally a
 *                 leading '+' or '-' character.
 *
 *      In all other cases, this function returns STR_LIB_NUM_FALSE.
 */
static int is_str_an_integer(const char *str)
{

    char c = -1;

    if (str == NULL) {
        return STR_LIB_NUM_FALSE;
    }

    if (str[0] == '\0') { // empty string
        return STR_LIB_NUM_FALSE;
    }

    // If length of 'str' is not less than 'STR_LIB_INTEGER_STR_SIZE' then it is
    // an error and in this case, return STR_LIB_NUM_FALSE.
    if (strnlen(str, STR_LIB_INTEGER_STR_SIZE) == STR_LIB_INTEGER_STR_SIZE) {
        return STR_LIB_NUM_FALSE;
    }

    if ((*str == '+') || (*str == '-')) {
        str++;
    }

    while ((c = *str)) {
        if ((c < '0') || (c > '9')) {
            return STR_LIB_NUM_FALSE;
        }
        str++;
    }

    return STR_LIB_NUM_TRUE;

} // end of function is_str_an_integer()

static int get_integer_input_from_user(char *str, int size, int *integer_ptr)
{

    char *retval = NULL;

    if ((str == NULL) || (integer_ptr == NULL)) {
        return STR_LIB_FAILURE;
    }

    if ((size < STR_LIB_MIN_STR_SIZE_ALLOWED) ||
        (size > STR_LIB_INTEGER_STR_SIZE)) {
        return STR_LIB_FAILURE;
    }

    retval = get_input_from_stdin_and_discard_extra_characters(str, size);

    if (retval == NULL) {
        return STR_LIB_FAILURE;
    }

    if (is_str_an_integer(str) != STR_LIB_NUM_TRUE) {
        return STR_LIB_FAILURE;
    }

    // convert string to int
    (*integer_ptr) = atoi(str);

    return STR_LIB_SUCCESS;

} // end of function get_integer_input_from_user()

