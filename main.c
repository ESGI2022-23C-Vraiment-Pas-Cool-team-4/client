#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void activate(GtkApplication* app, gpointer user_data){
	GtkWidget *mainWindow;

	gtk_init(&argc, &argv);

	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Hello World");
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 200, 200);
	gtk_widget_show(mainWindow);
}

int main(int argc, char** argv){
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.esgi.hotel", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}