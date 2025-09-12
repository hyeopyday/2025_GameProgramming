#include "submenu.h"
#include "snack.h"

void sub_main01(void)
{
    int c;
    while ((c = sub_menu_display01()) != 3)
    {
        switch (c)
        {
        case 1:
            chicken_burger();
            break;
        case 2:
            cheese_burger();
            break;
        default:
            break;
        }
    }
}

void sub_main02(void)
{
    int c;
    while ((c = sub_menu_display02()) != 3)
    {
        switch (c)
        {
        case 1:
            tomato_spaghetti();
            break;
        case 2:
            cream_spaghetti();
            break;
        default:
            break;
        }
    }
}
