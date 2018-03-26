#ifndef GTKMM_AddWindow_H
#define GTKMM_AddWindow_H

#include <gtkmm.h>
#include "DatabaseConnector.h"

class AddWindow : public Gtk::Window
{
public:
  AddWindow();
  virtual ~AddWindow();

protected:
  //Signal handlers:
  void on_button_cancel();
  void on_button_add();

  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::Box m_HBox;

  Gtk::ScrolledWindow m_ScrolledWindow;

  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_Cancel;
  Gtk::Button m_Button_Add;
  Gtk::Entry m_Entry_Title;
  Gtk::TextView m_TextView_Content;
  Gtk::ComboBoxText m_Combo_Urgency;
  Gtk::ComboBoxText m_Combo_State;
};

#endif //GTKMM_AddWindow_H
