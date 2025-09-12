#include <conio.h>
#include "key.h"

int main(void)
{
    int chr;
    do
    {
        chr = getch();
        print_key_code(chr);
    } while (1);

    return 0;
}
