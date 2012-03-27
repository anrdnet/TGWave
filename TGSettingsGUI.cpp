#include <gtkmm/main.h>
#include <iostream>
#include "TGSettingsGUI.h"
#include "core/TGDebug.h"

TGSettingsGUI::TGSettingsGUI(SimParams &params)
  : myResetButton("Reset"),
    myCScale(1,40, 0.5),
    myCLabel("Bølgehastighet"),
    myHeightScale(0.1, 2, 0.1),
    myHeightLabel("Høyde på nye bølger"),
    myShapeScale(5, 10000, 5),
    myShapeLabel("Form på nye bølger"),
    myViscScale(0.001, 0.1, 0.001),
    myViscLabel("Viskositet"),
    myScaleScale(0.1, 10, 0.1),
    myScaleLabel("Størrelse på nye bølger"),
    myColorScale(0.1, 100, 0.1),
    myColorLabel("Farge"),
    myParams(params)
{
    // Sets the border width of the window.
    set_border_width(10);
    
    myCScale.set_value(params.c);
    myHeightScale.set_value(params.NewHeight);
    myShapeScale.set_value(params.Shape);
    myViscScale.set_value(params.mu);
    myScaleScale.set_value(params.Scale);
    myColorScale.set_value(params.Color);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    myResetButton.signal_clicked().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_reset_clicked));
    myCScale.signal_value_changed().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_value_changed));
    myHeightScale.signal_value_changed().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_value_changed));
    myShapeScale.signal_value_changed().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_value_changed));
    myViscScale.signal_value_changed().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_value_changed));
    myColorScale.signal_value_changed().connect(sigc::mem_fun(*this,
                &TGSettingsGUI::on_value_changed));
    
    myMainPanel.pack_end(myCScale);
    myMainPanel.pack_end(myCLabel);
    myMainPanel.pack_end(myHeightScale);
    myMainPanel.pack_end(myHeightLabel);
    myMainPanel.pack_end(myShapeScale);
    myMainPanel.pack_end(myShapeLabel);
    myMainPanel.pack_end(myViscScale);
    myMainPanel.pack_end(myViscLabel);
    myMainPanel.pack_end(myScaleScale);
    myMainPanel.pack_end(myScaleLabel);
    myMainPanel.pack_end(myColorScale);
    myMainPanel.pack_end(myColorLabel);
    myMainPanel.pack_end(myResetButton);
    
    // This packs the button into the Window (a container).
    add(myMainPanel);
    
    show_all();
}

TGSettingsGUI::~TGSettingsGUI()
{
}

void TGSettingsGUI::on_reset_clicked()
{
    if(pthread_mutex_lock(&SimParams::Lock) != 0)
        Bug(true, "Failed to lock mutex");
    myParams.Reset = true;
    pthread_mutex_unlock(&SimParams::Lock);
}

void TGSettingsGUI::on_value_changed()
{
    if(pthread_mutex_lock(&SimParams::Lock) != 0)
        Bug(true, "Failed to lock mutex");
    myParams.c = myCScale.get_value();
    myParams.mu = myViscScale.get_value();
    myParams.NewHeight = myHeightScale.get_value();
    myParams.Shape = myShapeScale.get_value();
    myParams.Scale = myScaleScale.get_value();
    myParams.Color = myColorScale.get_value();
    pthread_mutex_unlock(&SimParams::Lock);
}

void TGSettingsGUI::RunGUI(int argc, char** argv, SimParams &params)
{
    Gtk::Main kit(argc, argv);

    TGSettingsGUI settings(params);
    Gtk::Main::run(settings);
}
