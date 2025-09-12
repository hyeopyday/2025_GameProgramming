#include <stdio.h>
#include "menu.h"
#include "submain.h"

int main(void)
{
    int c;
    while ((c = menu_display()) != 3)
    {
        switch (c)
        {
            case 1: sub_main01(); break;
            case 2: sub_main02(); break;
            default: break;
        }
    }
    return 0;
}
