#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "header.h"

int main(int argc, char** argv){
	GtkApplication *app;
	int status;

	gtk_init(&argc, &argv);

	app = gtk_application_new("org.esgi.hotel", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}