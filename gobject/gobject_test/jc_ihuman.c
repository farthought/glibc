#include "jc_ihuman.h"

static void
jc_ihuman_base_init (gpointer g_class)

{
  static gboolean is_initialized = FALSE;


  if (!is_initialized)
    {
      /* add properties and signals to the interface here */


      is_initialized = TRUE;
    }
}


GType
jc_ihuman_get_type (void)
{
  static GType iface_type = 0;

  if (iface_type == 0)
    {

      static const GTypeInfo info = {

        sizeof (JcIhumanInterface),
        jc_ihuman_base_init,   /* base_init */

        NULL,   /* base_finalize */
      };


      iface_type = g_type_register_static (G_TYPE_INTERFACE, "JcIhuman",

                                           &info, 0);
    }


  return iface_type;
}

void

jc_people_talk (JcIhuman *self)
{

  g_return_if_fail (JC_IS_IHUMAN (self));


  JC_IHUMAN_GET_INTERFACE (self)->speak ();

}
