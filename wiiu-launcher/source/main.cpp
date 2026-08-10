#include <wut.h>
#include <proc_ui/procui.h>
#include "Application.h"

/**
 * @brief Universal Wii U application entrance thread hook.
 * @param argc Primary system argument count tracking variable.
 * @param argv Dynamic parameter line vector string arrays.
 * @return 0 upon safe process shutdown.
 */
int main(int argc, char **argv) {
    // Instantiate your main application state manager framework object
    Application app;

    // Fire up the initialization sequences, scan the SD card, and trigger the menu engine loop
    app.Run();

    // Return safely to Cafe OS system space when the loop ends
    return 0;
}
