#if !defined(STRING_H)

static inline void
str_cat_unsafe(char *src0, char *src1, char *dest)
{
    while (*src0)  *(dest++) = *(src0++);
    while (*src1)  *(dest++) = *(src1++);
    *dest = '\0';
}

static inline void
str_copy_unsafe(char *src, char *dest)
{
    while (*src)  *(dest++) = *(src++);
}

static char *
str_find_first(char *str, char *token)
{
    char *result = 0;
    char *cmp = token;

    while (*str && *cmp)
    {
        if ((*str) == (*cmp))
        {
            if (!result)
                result = str;
            cmp += 1;
        }
        else
        {
            result = 0;
            cmp = token;
        }
        str += 1;
    }

    if ((!(*str)) && (*cmp))
        result = 0;
    return result;
}

static char *
str_find_last(char *str, char *token)
{
    char *result = 0;
    char *search = str;
    while(*str)
    {
        // @todo: optimize
        search = str_find_first(str, token);
        if (search)
        {
            result = search;
            str = search;
        }
        str += 1;
    }
    return result;
}

#define STRING_H
#endif
