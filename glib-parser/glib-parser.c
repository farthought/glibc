#include <glib.h>
#include <stdio.h>

static GKeyFile *load_config(const char *file)
{
	GError *err = NULL;
	GKeyFile *keyfile;
	GKeyFileFlags flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;
	keyfile = g_key_file_new();
	g_key_file_set_list_separator(keyfile,',');
	if(!g_key_file_load_from_file(keyfile,file,flags,&err)){
		error("Parsing %s failed:%s",file,err->message);
		g_error_free(err);
		g_key_file_free(keyfile);
		return NULL;
	}
	return keyfile;
}

int main(int argc, int **argv)
{
	gchar *str;
	const gchar * string;
	int val1, val2;
	GError *err = NULL;
	gsize length = 0;
	GKeyFile *keyfile;
	keyfile = load_config("main.conf");
	str = g_key_file_get_string(keyfile, "General", "OffMode", &err);
	if (err){
		g_printf("%s",err->message);
		g_clear_error(&err);
	}
	val1 = g_key_file_get_integer(keyfile, "General", "PageTimeout",&err);
	if(err){
		g_printf("%s", err->message);
		g_clear_error(&err);
	}
	val2 = g_key_file_get_integer(keyfile, "test","age",&err);
	if(err){
		g_printf("%s",err->message);
		g_clear_error(&err);
	}
	if(g_key_file_has_key(keyfile, "test", "age", &err))
	{
		int i=10;
		g_key_file_set_integer(keyfile, "test", "age", i);
	}
	gchar * content = g_key_file_to_data(keyfile, &length, NULL);
	FILE* fp = fopen("./main.conf","w");  
	if(fp == NULL) 
		return -1;  
	fwrite(content,1,length,fp);  
	fclose(fp);  
	g_printf("offmode=%s\n",str);
	g_printf("pagetimeout=%d\n",val1);
	g_printf("age=%d\n",val2);
	return 0;
}
