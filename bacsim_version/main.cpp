//g++ *.cpp -o Fenetre `pkg-config gtkmm-3.0 --cflags --libs` -std=c++14
#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>
#include "window.hpp"
#include <string>







int main(int argc, char* argv[]) {


    Gtk::Main app(argc, argv);
    Window window;

   // Gtk::Image image("result.png");


    //window.add(image);
    //image.show();

    //Window window; //Création de la fenêtre.

/*
    Gtk::Button bouton(Gtk::Stock::LEAVE_FULLSCREEN); //Création d'un bouton à partir d'un Stock Item.
    fenetre.add(bouton); //Ajout du bouton à la fenêtre.
    bouton.set_can_focus(false); //Empêcher le bouton d'avoir le focus.
    bouton.show(); //Afficher le bouton.
*/

    Gtk::Main::run(window);



    return 0;
}
