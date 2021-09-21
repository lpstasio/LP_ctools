#if !defined(STRING_H)

static inline u32
str_len(char *str)
{
    u32 result = 0;
    while (*(str++))
        result += 1;
    return result;
}

static inline void
str_cat_unsafe(char *src0, char *src1, char *dest)
{
    while (*src0)  *(dest++) = *(src0++);
    while (*src1)  *(dest++) = *(src1++);
    *dest = '\0';
}

// todo: test this properly
static inline void
str_copy_unsafe(char *src, char *dest)
{
    if (src != dest)
    {
        u32 src_len = str_len(src);
        u32 dest_len = str_len(dest);

        // if dest is ahead of src and they overlap, perform the copy backwards
        if ((dest > src) && (dest < (src + src_len)))
        {
            char *src_start  = src;
            char *dest_start = dest;
            src  += dest_len;
            dest += dest_len;
            
            while (src >= src_start)
                *(dest--) = *(src--);
        }
        else
        {
            while (*src)
                *(dest++) = *(src++);
        }

    }
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

static void
str_replace_first_unsafe(char *str, char *from, char *to)
{
    char *search = str_find_first(str, from);
    if (search)
    {
        u32 from_length = str_len(from);
        u32 to_length = str_len(to);

        s32 len_diff = (s32)to_length - (s32)from_length;
        if (len_diff)
        {
            str_copy_unsafe(search + from_length,
                            search + from_length + len_diff);
        }
        str_copy_unsafe(to, search);
    }
}

#define STRING_H
#endif
