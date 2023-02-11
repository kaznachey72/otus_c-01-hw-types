#include "utils.h"
#include "parsing_zip.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
        printf("USAGE: %s file.jpg\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
        printf("ERROR: file open error\n");
		return 1;
	}

    if (has_jpeg_sign(f)) {
        bool b = has_archive(f);
        printf("has archive: %s\n", (b ? "yes" : "no"));

        if (b) {
            show_files(f);
        }
    }

    fclose(f);
	return 0;
}

