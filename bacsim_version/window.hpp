#ifndef DEF_WINDOW
#define DEF_WINDOW


class Window : public Gtk::Window {
    public :
        Window();
        //typedef sigc::signal<void> type_signal_nom;
		//type_signal_nom signal_nom();
        void run_experiment();


    
    private :

        Gtk::VBox MenuBox;
        Gtk::MenuBar menuBar;
        Gtk::MenuItem menuItemFile;
        Gtk::Menu menuFile;
        Gtk::ImageMenuItem menu_save;
        Gtk::ImageMenuItem menu_quit;




        Gtk::HBox Hbox;
        Gtk::VButtonBox Vbox;
       	Gtk::Image image;

        Gtk::Button button_run;
        Gtk::SpinButton button_counter;






        //Gtk::Button bouton; //Déclaration du bouton.
        //type_signal_nom m_signal_nom;

};

std::string convert_int_to_str(int value);



#endif