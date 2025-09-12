#include <stdio.h>
#include "menu.h"
#include "snack.h"

int main(void)
{
    int c;
    while ((c = menu_display()) != 3)
    {
        switch (c)
        {
        case 1: hamburger(); break;
        case 2: spaghetti(); break;
        default: break;
        }
    }
    return 0;
}
