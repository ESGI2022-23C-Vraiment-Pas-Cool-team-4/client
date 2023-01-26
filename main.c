#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char** argv){
	gtk_init(&argc, &argv);

	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "Hello World");
	gtk_widget_show(window);

	gtk_main();
	
	return EXIT_SUCCESS;
}