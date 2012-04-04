
#ifndef TGSETTINGSGUI_H_
#define TGSETTINGSGUI_H_

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/hvscale.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/togglebutton.h>
#include "TGInterface.h"

class TGSettingsGUI : public Gtk::Window
{

public:
    TGSettingsGUI(SimParams &params);
    virtual ~TGSettingsGUI();

protected:
    //Signal handlers:
    void on_reset_clicked();
    void on_value_changed();

    //Member widgets:
    Gtk::Button myResetButton;
    Gtk::VBox myMainPanel1;
    Gtk::VBox myMainPanel2;
    Gtk::HScale myCScale;
    Gtk::Label myCLabel;
    Gtk::HScale myHeightScale;
    Gtk::Label myHeightLabel;
    Gtk::HScale myShapeScale;
    Gtk::Label myShapeLabel;
    Gtk::HScale myViscScale;
    Gtk::Label myViscLabel;
    Gtk::HScale myScaleScale;
    Gtk::Label myScaleLabel;
    Gtk::HScale myColorScale;
    Gtk::Label myColorLabel;
    Gtk::CheckButton myShading;
    Gtk::HBox myTogglePanel;
    Gtk::HBox mySuperPanel;
    Gtk::ToggleButton myZoom;
    SimParams &myParams;
public:
    static void RunGUI(int argc, char** argv, SimParams &params);
};

#endif 
