#include "parsing_zip.h"
#include <stdlib.h>

typedef struct {
    unsigned char unused_fields[26];
    /*  
        int sign;
        short version;
        short flags;
        short compres;
        short time;
        short date;
        int crc;
        int compr_size;
        int total_size;
    */
    short fn_len;
    short ex_len;
} arch_t;

const unsigned char BEG_ZIP_SIGN[4] = {0x50, 0x4b, 0x03, 0x04};

void show_files(FILE *f)
{
    unsigned char buf;
 
    size_t cur_index = 0;   
    while (fread(&buf, sizeof(char), 1, f)) {
        cur_index = (buf == BEG_ZIP_SIGN[cur_index]) ? (cur_index + 1) : 0;        
        if (cur_index != sizeof(BEG_ZIP_SIGN)) {
            continue;
        }

        fseek(f, ftell(f)-4, SEEK_SET);

        arch_t arch;
        if (fread(&arch, sizeof(arch_t), 1, f)) {
            char *fn = (char*)malloc(arch.fn_len+1);
            
            fn[arch.fn_len] = 0;
            if (fread(fn, arch.fn_len, 1, f)) {
                printf("%s\n", fn);
            }

            free(fn);
        }
        cur_index = 0;
    }
}
