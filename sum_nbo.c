#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "sum_nbo.h"

uint32_t read_be32_file(const char *file_path)
{
    FILE *file = fopen(file_path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "cannot open %s\n", file_path);
        exit(1);
    }

    uint32_t network_order_value;

    if (fread(&network_order_value, sizeof(network_order_value), 1, file) != 1)
    {
        fprintf(stderr, "cannot read %s\n", file_path);
        fclose(file);
        exit(1);
    }

    fclose(file);

    network_order_value = ntohl(network_order_value);

    printf("%u(0x%08x)", network_order_value, network_order_value);

    return network_order_value;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    uint32_t total_sum = 0;

    for (int index = 1; index < argc; index++)
    {
        total_sum += read_be32_file(argv[index]);

        if (index < argc - 1)
            printf(" + ");
    }

    printf(" = %u(0x%08x)\n", total_sum, total_sum);

    return 0;
}
