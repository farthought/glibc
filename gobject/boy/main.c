#include <glib.h>
#include "boy.h"
#include "man.h"

int main(int argc, char *argv[])
{
    Boy *tom, *peter;
    Man *green, *brown;
    g_type_init();
    g_print("***********************\n");
    tom = boy_new_with_name("Tom");
    tom->cry();
    boy_info(tom);
    g_print("***********************\n");
    peter = boy_new_with_name_and_age("Peter", 10);
    peter->cry();
    boy_info(peter);
    g_print("***********************\n");
    g_print("#######################\n");
    green = man_new();
    boy_set_name(BOY(green), "Green");
    boy_set_age(BOY(green), 28);
    man_set_job(green, "Doctor");
    man_info(green);
    green->bye();
    g_print("########################\n");
    brown = man_new_with_name_age_and_job("Brown", 30, "Teacher");
    man_info(brown);
    brown->bye();
    g_print("#########################\n");
    return TRUE;


}
