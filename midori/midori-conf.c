#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	GKeyFile  * keyfile;
	GtkWidget * entry;
	GtkWidget * button;
	const gchar * group;
	const gchar * key;
	gchar * str;
}keyfileconf;

static GKeyFile * loadfile(gchar *file)
{
	GKeyFile * keyfile;
	GError * err = NULL;
	GKeyFileFlags flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;


	keyfile = g_key_file_new();
	if(! g_key_file_load_from_file(keyfile, file, flags, &err))
	{
		error("Parasing %s failed:%s", file, err->message);
		g_error_free(err);
		g_key_file_free(keyfile);

		return NULL;
	}
	return keyfile;
}


void midori_button_clicked(GtkWidget * button, gpointer data)
{
	GtkWidget *dialog;
	gchar *bufferold;
	const gchar *buffernew;
	gchar *buffer;
	gchar *tip = "";
	gboolean flag = FALSE;
	gsize length = 0;

	keyfileconf * pbuf = (keyfileconf *) data;
	bufferold = g_strdup(pbuf->str);
	buffernew = gtk_entry_get_text(GTK_ENTRY(pbuf->entry));
	if(g_strcmp0(bufferold, buffernew) == 0)
	{
		buffer = g_strdup("请重新输入：");
		tip = g_strdup("没有改变");
	}
	else
	{
		buffer = g_strdup("您输入了：");
		tip = g_strdup(buffernew);
	}
	dialog=gtk_message_dialog_new(NULL,
			GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK_CANCEL, "%s", buffer);
	gtk_message_dialog_format_secondary_text(
			GTK_MESSAGE_DIALOG(dialog),"%s",tip);

	gtk_window_set_title(GTK_WINDOW(dialog),"提示");

	if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_OK)
	{
		g_key_file_set_value(pbuf->keyfile, pbuf->group, pbuf->key, buffernew);
		gchar * content = g_key_file_to_data(pbuf->keyfile, &length, NULL);
		FILE * fp = fopen("/etc/isoft.conf", "w");
		if (fp == NULL)
			exit -1;
		fwrite(content, 1, length, fp);
		fclose(fp);
		g_printf("%s\n", content);
	}
	else
		exit -1;
	gtk_widget_destroy(dialog);

}
int item_paint(GtkWidget *box, GKeyFile *keyfile, const gchar *group, const gchar *key){

	GtkWidget * hbox;
	GtkWidget * label;
	GtkWidget * button;
	GError * err = NULL;
	gchar * str, * string;
	gchar ** strlist;
	GtkWidget * entry;
	gsize length;

	keyfileconf * keyfileconf_intent = (keyfileconf *)g_malloc(sizeof(keyfileconf));

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);
	string = (gchar *)g_malloc(sizeof(key)+1);
	g_sprintf(string, "%s: ", key);
	label = gtk_label_new(string);
	gtk_misc_set_alignment(GTK_MISC(label), 0, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
	gtk_widget_show(label);
	str = g_key_file_get_value(keyfile, group, key, &err);
	if(err)
	{
		g_printf("%s", err->message);
		return -1;
	}

	button = gtk_button_new_with_label("修改");	
	entry = gtk_entry_new();
	keyfileconf_intent->keyfile = keyfile;
	keyfileconf_intent->entry = entry;
	keyfileconf_intent->button = button;
	keyfileconf_intent->group = group;
	keyfileconf_intent->key = key;
	keyfileconf_intent->str = g_strdup(str);

	g_signal_connect(GTK_BUTTON(button), "clicked",G_CALLBACK(midori_button_clicked), keyfileconf_intent);

	gtk_entry_set_text(GTK_ENTRY(entry), str);
	gtk_entry_set_visibility(GTK_ENTRY(entry), TRUE);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 40);
	gtk_box_pack_end(GTK_BOX(hbox), entry, FALSE, FALSE, 10);
	gtk_widget_show(entry);
	gtk_widget_show(button);
}

int main(int argc, char ** argv)
{
	GtkWidget * window;
	GtkWidget * box;
	GtkEntryBuffer * entrybuffer;
	GKeyFile * keyfile;
	gchar * str;
	guint val;

	keyfile = loadfile("./isoft.conf");

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "configure");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(box);

	item_paint(box, keyfile, "username", "name");
	item_paint(box, keyfile, "password", "passwd");
	item_paint(box, keyfile, "http", "http");
	item_paint(box, keyfile, "browser", "browser");
	item_paint(box, keyfile, "addr", "addr");
	item_paint(box, keyfile, "ip", "ip");
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
