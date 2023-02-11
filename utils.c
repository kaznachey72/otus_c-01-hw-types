#include "utils.h"

bool compare(const unsigned char *s1, const unsigned char *s2, size_t n)
{
    if (!n) return false;
    while (--n && *s1 == *s2) {
        s1++;
        s2++;
    }   
    return *s1 == *s2;
}

long pos_end_jpeg(FILE *f)
{
    const unsigned char end_jpg[2] = {0xff, 0xd9};

    unsigned char buf[2];
    fread(&buf[0], sizeof(char), 1, f);

    while (fread(&buf[1], sizeof(char), 1, f)) {
        if (compare(buf, end_jpg, sizeof(buf))) {
            break;
        }
        buf[0] = buf[1];
    }

    return ftell(f);
}

long pos_end_file(FILE *f)
{
    long cur_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long end_pos = ftell(f);
    fseek(f, cur_pos, SEEK_SET);
    return end_pos;
}


bool has_jpeg_sign(FILE *f) 
{
    long cur_pos = ftell(f);
    fseek(f, 0, SEEK_SET);

    const unsigned char beg_jpg[2] = {0xff, 0xd8};
    unsigned char buf[2];
    fread(buf, sizeof(char), sizeof(buf), f); 

    fseek(f, cur_pos, SEEK_SET);
    return compare(buf, beg_jpg, sizeof(buf));
}


bool has_archive(FILE *f)
{
    long fsize = pos_end_file(f);
    long jsize = pos_end_jpeg(f);
    return (fsize > jsize);
}


