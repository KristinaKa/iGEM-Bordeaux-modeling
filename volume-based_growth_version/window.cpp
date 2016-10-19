#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "window.hpp"


using namespace std;


Window::Window() { 




    /****** Window features ******/
    set_title("Bacterial growth");
    resize(600, 500); //resize( width, height )
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



    /****** Button features *****/
    button_run.set_label("Run");
    button_run.signal_clicked().connect([this]() { run_experiment(); }); // when RUN button is clicked, the experiment runs
    button_run.set_margin_top(20);



    L1.set_text("Simulation time (h)");
    LabelBox.pack_start(L1);
    L2.set_text("Time step (h)");
    LabelBox.pack_start(L2);
    L3.set_text("Initial number of bacteria");
    LabelBox.pack_start(L3);
    L4.set_text("Percentage of donors");
    LabelBox.pack_start(L4);
    L5.set_text("Grid length");
    LabelBox.pack_start(L5);
    L6.set_text("Grid height");
    LabelBox.pack_start(L6);
    L7.set_text("Number of stack levels");
    LabelBox.pack_start(L7);
    L8.set_text("Nutrient concentration (fg/fl)");
    LabelBox.pack_start(L8);   
    L9.set_text("Conjugation rate");
    LabelBox.pack_start(L9);
    L10.set_text("Segregation loss");
    LabelBox.pack_start(L10);
    L11.set_text("Plasmid cost");
    LabelBox.pack_start(L11);
 

    int nb_of_spin_buttons= 11; //to be changed when a spin button is added
    for (int i = 0 ; i < nb_of_spin_buttons ; i++)
    {
        Gtk::SpinButton *spin_button = new Gtk::SpinButton();
        vect.push_back(spin_button);
    }

    /* Simulation Time */
    Glib::RefPtr<Gtk::Adjustment> adjustment = Gtk::Adjustment::create(1., 0, 72., 1); 
    vect[0]->set_adjustment(adjustment);
    vect[0]->set_numeric(); // Allows ONLY numerical values
    vect[1]->configure (adjustment, 0.05, 2);
    SpinButtonBox.pack_start(*vect[0]);


    /* Time step */
    adjustment = Gtk::Adjustment::create(0.1, 0.0001, 1. , 0.0050); 
    vect[1]->set_adjustment(adjustment);
    vect[1]->set_numeric(); // Allows ONLY numerical values
    vect[1]->configure (adjustment, 0.0050, 4);
    SpinButtonBox.pack_start(*vect[1]);
    

    /* Initial number of bacteria */
    adjustment = Gtk::Adjustment::create(3, 0, 1000, 20); 
    vect[2]->set_adjustment(adjustment);
    vect[2]->set_numeric(); // Allows ONLY numerical values
    SpinButtonBox.pack_start(*vect[2]);

    /* Percentage of donors */
    adjustment = Gtk::Adjustment::create(0.5, 0, 1, 0.05); 
    vect[3]->set_adjustment(adjustment);
    vect[3]->set_numeric(); // Allows ONLY numerical values
    vect[3]->configure (adjustment, 0.05, 2);
    SpinButtonBox.pack_start(*vect[3]);
    

    /* Lattice length */
    adjustment = Gtk::Adjustment::create(1000, 1, 10000, 1000); 
    vect[4]->set_adjustment(adjustment);
    vect[4]->set_numeric(); // Allows ONLY numerical values
    SpinButtonBox.pack_start(*vect[4]);    


    /* Lattice height */
    adjustment = Gtk::Adjustment::create(1000, 1, 10000, 1000); 
    vect[5]->set_adjustment(adjustment);
    vect[5]->set_numeric(); // Allows ONLY numerical values
    SpinButtonBox.pack_start(*vect[5]);
    

    /* Number of stack levels */
    adjustment = Gtk::Adjustment::create(0, 1, 9, 1); 
    vect[6]->set_adjustment(adjustment);
    vect[6]->set_numeric(); // Allows ONLY numerical values
    SpinButtonBox.pack_start(*vect[6]);

    
    /* Substrate concentration */
    adjustment = Gtk::Adjustment::create(100, 0, 10000, 10); 
    vect[7]->set_adjustment(adjustment);
    vect[7]->set_numeric(); // Allows ONLY numerical values
    SpinButtonBox.pack_start(*vect[7]);

    
    /* Conjugation rate */
    adjustment = Gtk::Adjustment::create(1., 0., 1., 0.1); 
    vect[8]->set_adjustment(adjustment);
    vect[8]->set_numeric(); // Allows ONLY numerical values
    vect[8]->configure (adjustment, 0.1, 1);
    SpinButtonBox.pack_start(*vect[8]);
    

    /* Segregation loss */
    adjustment = Gtk::Adjustment::create(0.5, 0., 1., 0.1); 
    vect[9]->set_adjustment(adjustment);
    vect[9]->set_numeric(); // Allows ONLY numerical values
    vect[9]->configure (adjustment, 0.1, 1);
    SpinButtonBox.pack_start(*vect[9]);
    
    
    /* Plasmid cost probability */
    adjustment = Gtk::Adjustment::create(0., 0., 1, 0.01); 
    vect[10]->set_adjustment(adjustment);
    vect[10]->set_numeric(); // Allows ONLY numerical values
    vect[10]->configure (adjustment, 0.01, 2);
    SpinButtonBox.pack_start(*vect[10]);
    

    /* Here are the settings for adjustment button ( <initial value> , <minimal> , <maximal> , <step> )*/
    //Glib::RefPtr<Gtk::Adjustment> ajustment = Gtk::Adjustment::create(60, 0, 100, 5); 
    //button_counter.set_adjustment(ajustment);
    //button_counter.set_numeric(); // Allows ONLY numerical values

    /****** Image features ******/
    Glib::ustring fImg("logo.png") ;
    /* a Pixbuf object is created and then stored in Image object */
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_ptr = Gdk::Pixbuf::create_from_file(fImg, 320, 320) ;
    image.set(pixbuf_ptr);


    /****** Horizontal box features ******/
    LabelBox.set_spacing(10);
    SpinButtonBox.set_spacing(10);

    LeftHBox.pack_start(LabelBox);
    LeftHBox.pack_start(SpinButtonBox);   // Hbox = Horizontal Box (= container)


    /****** Vertical box features ******/
    //Vbox.set_layout(Gtk::BUTTONBOX_CENTER);
    LeftVbox.pack_start(LeftHBox);
    LeftVbox.pack_start(button_run);    // Add RUN button to the vertical box (= container)


    /****** Horizontal box features ******/
    Hbox.pack_start(LeftVbox);   // Hbox = Horizontal Box (= container)
    Hbox.pack_start(image);
    

    /****** Menu box features ******/
    MenuBox.pack_start(menuBar, Gtk::PACK_SHRINK);
    MenuBox.pack_start(Hbox);





    /***** For display *****/
    add(MenuBox); // add the menu box (=main box) to the window
    show_all(); // Display all widgets

}



void Window::run_experiment()
{

    string cmd = "./run " /*+ value_str*/ ;

    for(int i = 0 ; i < vect.size() ; i++)
    {
        double nb = vect[i]->get_value() ;
        cmd +=  convert_double_to_str(nb) + " " ;
    }

    system(cmd.c_str());



    system("python makePicture.py");


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


std::string convert_double_to_str(double value)
{
    std::ostringstream sstream;
    sstream << value;
    std::string str = sstream.str();

    return str;
}
