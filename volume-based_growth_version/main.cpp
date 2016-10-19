#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>
#include "window.hpp"
#include <string>


int main(int argc, char* argv[]) {


    Gtk::Main app(argc, argv);
    Window window;

    Gtk::Main::run(window);

    return 0;
}
