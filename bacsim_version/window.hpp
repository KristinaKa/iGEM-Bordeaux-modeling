#ifndef DEF_WINDOW
#define DEF_WINDOW


class Window : public Gtk::Window {
    public :
        Window();
        void run_experiment();


    
    private :

        Gtk::VBox                   MenuBox;
        Gtk::MenuBar                menuBar;
        Gtk::MenuItem               menuItemFile;
        Gtk::Menu                   menuFile;
        Gtk::ImageMenuItem          menu_save;
        Gtk::ImageMenuItem          menu_quit;


        Gtk::Label                  L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11 ;


        Gtk::HBox                   Hbox, LeftHBox;
        Gtk::VButtonBox             LeftVbox, LabelBox, SpinButtonBox;
       	Gtk::Image                  image;

        Gtk::Button                 button_run;

        /** Spin button is an adjusting button*/
        std::vector<Gtk::SpinButton*>    vect;
};

std::string convert_int_to_str(int value);
std::string convert_double_to_str(double value);




#endif