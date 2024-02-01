#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    int img_num = 0;
    FILE *img_file = NULL;
    char filename[8];

    while (fread(buffer, 1, 512, input_file) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img_num != 0)
            {
                fclose(img_file);
            }
            sprintf(filename, "%03i.jpg", img_num);
            img_file = fopen(filename, "w");
            img_num++;
        }

        if (img_file != NULL)
        {
            fwrite(buffer, 512, 1, img_file);
        }
    }

    fclose(input_file);
    fclose(img_file);
}
