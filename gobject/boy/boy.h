#ifndef _BOY_H
#define _BOY_H

#include <glib-object.h>

#define BOY_TYPE (boy_get_type())
#define BOY(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), BOY_TYPE, Boy))

typedef struct _Boy Boy;
typedef struct _BoyClass BoyClass;

struct _Boy
{
    GObject parent;
    gchar * name;
    gint age;
    void (*cry)(void);
};

struct _BoyClass
{
    GObjectClass parent_class;
    void (*boy_born)(void);
};

GType boy_get_type(void);
Boy  *boy_new(void);
char *boy_get_name(Boy *boy);
void boy_set_name(Boy *boy, char *name);
int  boy_get_age(Boy *boy);
void boy_set_age(Boy *boy, int age);
Boy  *boy_new_with_name(char *name);
Boy  *boy_new_with_age(int age);
Boy  *boy_new_with_name_and_age(char *name, int age);
void boy_info(Boy *boy);

#endif

