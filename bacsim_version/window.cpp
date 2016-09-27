#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "window.hpp"


using namespace std;


Window::Window() { 




    /****** Window features ******/
    set_title("Bacterial growth");
    resize(600, 400); //Redimensionner la fenêtre : nouvelle largeur = 640px, nouvelle hauteur = 480px.
    set_position(Gtk::WIN_POS_CENTER);
    //fullscreen();

    /****** Menu Bar features ******/
    menuItemFile.set_label("File");
    menuBar.append(menuItemFile);
    menuItemFile.set_submenu(menuFile);


    menu_save.set_label("Save");
    menuFile.append(menu_save);

    menu_quit.set_label("Quit");
    menuFile.append(menu_quit);





    /****** Button feature *****/
    button_run.set_label("Run");
    button_run.signal_clicked().connect([this]() { run_experiment(); }); // when RUN button is clicked, the experiment runs
    button_run.set_margin_top(20);


    /* Here is settings for adjustment button ( <initial value> , <minimal> , <maximal> , <step> )*/
    Glib::RefPtr<Gtk::Adjustment> ajustment = Gtk::Adjustment::create(60, 0, 100, 5); 
    button_counter.set_adjustment(ajustment);
    button_counter.set_numeric(); // Allows ONLY numerical values

    /****** Image features ******/
    Glib::ustring fImg("Welcome.png") ;
    /* a Pixbuf object is created and then stored in Image object */
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_ptr = Gdk::Pixbuf::create_from_file(fImg, 320, 320) ;
    image.set(pixbuf_ptr);






    /****** Vertical box features ******/
    //Vbox.set_layout(Gtk::BUTTONBOX_CENTER);
    Vbox.pack_start(button_run);    // Add RUN button to the vertical box (= container)
    Vbox.pack_start(button_counter);    // Add COUNTER button to the vertical box (= container)


    /****** Horizontal box features ******/
    Hbox.pack_start(Vbox);   // Hbox = Horizontal Box (= container)
    Hbox.pack_start(image);
    

    /****** Menu box features ******/
    MenuBox.pack_start(menuBar, Gtk::PACK_SHRINK);
    MenuBox.pack_start(Hbox);





    /***** For display *****/
    add(MenuBox); // add the menu box (=main box) to the window
    show_all(); // Display all widgets



    //Autres modifications de la fenêtre.
    /*
    bouton.set_label("Hello world !");
    bouton.show(); //Ne pas oublier l'affichage du bouton.
    bouton.set_can_focus(false); //Nous pouvons aussi modifier le bouton.
    add(bouton); //Ajouter le bouton à la fenêtre.


    bouton.signal_clicked().connect([this]() { set_title("Bonjour le monde !"); });
    bouton.signal_clicked().connect([this]() { bouton.set_label("Bonjour le monde !"); });
*/  

}



void Window::run_experiment()
{
    /* FAIRE UNE FONCTION ICI ? */
    double value = button_counter.get_value_as_int();
    string value_str = convert_int_to_str(value);

    string cmd = "./run " /*+ value_str*/ ;

    system(cmd.c_str());
    system("python makePicture.py");

    //system("cat gnu.conf | gnuplot");



    /****** Image features ******/
    Glib::ustring fImg("results.png") ;
    /* a Pixbuf object is created and then stored in Image object */
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_ptr = Gdk::Pixbuf::create_from_file(fImg, 320, 320) ;
    image.set(pixbuf_ptr);

    cout << "Done" << endl;

}




std::string convert_int_to_str(int value)
{
    stringstream s;
    s << value;
    return s.str();
}
