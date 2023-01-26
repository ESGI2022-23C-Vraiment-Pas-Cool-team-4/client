#include <gtk/gtk.h>

void activate(GtkApplication* app, gpointer user_data){
	GtkWidget *mainWindow;
	
	mainWindow = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Hello World");
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 200, 200);
	gtk_widget_show(mainWindow);
}