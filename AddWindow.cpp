#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "AddWindow.h"

using std::sprintf;
using std::strtol;

AddWindow::AddWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Cancel("Cancel"),
  m_Button_Add("Add"),
  m_Entry_Title(),
  m_TextView_Content()
{
  set_title("Add a new task");
  set_border_width(5);
  set_default_size(600, 300);


  add(m_VBox);

  m_TextView_Content.set_size_request (-1, 120);
  m_TextView_Content.set_tooltip_text ("Content of the task.");

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_Entry_Title, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_TextView_Content, Gtk::PACK_SHRINK);
  m_VBox.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);
  m_VBox.pack_end(m_HBox, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_ScrolledWindow);

  m_ButtonBox.pack_start(m_Button_Add, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_Cancel, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

  // fill up the combo Urgency
  m_Combo_Urgency.append(UrgencyNumberToString(0));
  m_Combo_Urgency.append(UrgencyNumberToString(1));
  m_Combo_Urgency.append(UrgencyNumberToString(2));
  m_Combo_Urgency.append(UrgencyNumberToString(3));
  m_Combo_Urgency.append(UrgencyNumberToString(4));
  m_Combo_Urgency.set_active(2);

  // fill up the combo State
  m_Combo_State.append(StateNumberToString(0));
  m_Combo_State.append(StateNumberToString(1));
  m_Combo_State.append(StateNumberToString(2));
  m_Combo_State.set_active(0);

  m_HBox.pack_start(m_Combo_Urgency);
  m_HBox.pack_start(m_Combo_State);

  m_Button_Cancel.signal_clicked().connect( sigc::mem_fun(*this, &AddWindow::on_button_cancel) );
  m_Button_Add.signal_clicked().connect( sigc::mem_fun(*this, &AddWindow::on_button_add) );

  show_all_children();
}

AddWindow::~AddWindow()
{
}

void AddWindow::on_button_cancel()
{
  hide();
}

void AddWindow::on_button_add()
{
  DatabaseConnector con("tcp://127.0.0.1:3306", "organizer", "password", "Organizer");

  std::string Title     =   m_Entry_Title.get_text();
  std::string Content   =   m_TextView_Content.get_buffer()->get_text();
  int Urgency           =   m_Combo_Urgency.get_active_row_number(); 
  int State             =   m_Combo_State.get_active_row_number(); 

  con.AddTask(Title, Content, Urgency, State);
}
