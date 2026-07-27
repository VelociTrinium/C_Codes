/*
 * main_gui.c
 *
 * To compile (on Linux):
 * gcc main_gui.c -o my_simulator_gui `pkg-config --cflags --libs gtk+-3.0`
 *
 * You will also need to refactor your simulator code into a separate
 * .c/.h file (e.g., simulator_core.c) and link it.
 * For example:
 * gcc main_gui.c simulator_core.c -o gui `pkg-config --cflags --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// --- TODO: Move your Process struct and other definitions to a header ---
// #include "simulator_core.h"
// --- (Your core logic functions should be in simulator_core.c) ---


// This struct holds pointers to the widgets we need to access
typedef struct {
    GtkWidget *entry_n_procs;
    GtkWidget *entry_m_res;
    GtkWidget *text_view_output;
    // TODO: Add widgets for process data (maybe a GtkGrid)
    // TODO: Add widgets for resource totals
} AppWidgets;


/*
 * This is the "Controller" callback.
 * It's called when the "Run Simulation" button is clicked.
 */
static void on_run_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    GtkTextBuffer *buffer;
    
    // 1. GET DATA FROM VIEW (the UI)
    // ------------------------------------
    const gchar *n_text = gtk_entry_get_text(GTK_ENTRY(widgets->entry_n_procs));
    const gchar *m_text = gtk_entry_get_text(GTK_ENTRY(widgets->entry_m_res));

    // TODO: Get the rest of the data (process table, resource totals)
    // This is complex! You'd likely use a GtkGrid or GtkListStore for the table.

    // 2. RUN THE MODEL (your logic)
    // ------------------------------------
    
    // --- THIS IS WHERE YOU'D CALL YOUR REFACTORED CODE ---
    // You would first parse the text input (e.g., n = atoi(n_text))
    // Then, you'd populate your P[] array.
    // Then, you'd call your main simulation loop.
    
    // IMPORTANT: Your simulation logic CANNOT print to console.
    // It must be refactored to return the results (e.g., as a big string,
    // or a struct containing the avg. times).
    
    // For now, we'll just fake the output:
    const char *sim_results = "--- SIMULATION RESULTS (from your logic) ---\n"
                              "PID     AT      BT      Pri     ...\n"
                              "P1      0       5       1       ...\n"
                              "\nAverage Waiting Time = ...\n"
                              "\n--- CPU GANTT CHART ---\n"
                              "| P1 (0->5) | ...\n";
    // ----------------------------------------------------


    // 3. UPDATE THE VIEW (show results)
    // ------------------------------------
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->text_view_output));
    gtk_text_buffer_set_text(buffer, sim_results, -1);
}

/*
 * This function builds the main application window
 */
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *scrolled_window;
    AppWidgets *widgets = (AppWidgets *)user_data;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "OS Simulator");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    // --- Inputs ---
    label = gtk_label_new("Num Processes (n):");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    widgets->entry_n_procs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_n_procs, 1, 0, 1, 1);

    label = gtk_label_new("Num Resources (m):");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    widgets->entry_m_res = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_m_res, 1, 1, 1, 1);

    // TODO: Add widgets for process table input (e.g., a GtkGrid)

    // --- Button ---
    button = gtk_button_new_with_label("Run Simulation");
    // Connect the "clicked" signal to our on_run_clicked function
    g_signal_connect(button, "clicked", G_CALLBACK(on_run_clicked), widgets);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

    // --- Output ---
    label = gtk_label_new("Results:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 2, 1);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    widgets->text_view_output = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->text_view_output), FALSE);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(widgets->text_view_output), TRUE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), widgets->text_view_output);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 4, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    // Allocate our widget-holding struct
    AppWidgets *widgets = g_slice_new(AppWidgets);

    app = gtk_application_new("org.example.ossimulator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), widgets);
    
    // This starts the GTK event loop and blocks until the app quits
    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);
    g_slice_free(AppWidgets, widgets);

    return status;
}
