#include <stdio.h>
#include <gtk/gtk.h>

#define g_value_new(type) g_value_init(g_new(GValue, 1), type)

int main(void)
{
    GValue *a = g_value_new(G_TYPE_UCHAR);
    GValue *b = g_value_new(G_TYPE_INT);
    int c = 0;
    
    g_value_set_uchar(a, 'a');
    g_value_copy(a, b);

    c = g_value_get_int(b);
    g_print("w00t:%d\n", c);

    g_free(a);
    g_free(b);
    return 0;
}
