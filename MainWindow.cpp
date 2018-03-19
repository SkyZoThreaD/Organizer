#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "MainWindow.h"

using std::sprintf;
using std::strtol;

MainWindow::MainWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Quit"),
  m_Button_AddTask("Add Task"),
  m_validate_retry(false)
{
  set_title("Organizer");
  set_border_width(5);
  set_default_size(600, 400);


  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_AddTask, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_quit) );
  m_Button_AddTask.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_add_task) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  

  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Title", m_Columns.m_col_title);
  m_TreeView.append_column("State", m_Columns.m_col_state);
  m_TreeView.append_column("Urgency", m_Columns.m_col_urgency);

    RefreshList();

  show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::RefreshList()
{
    DatabaseConnector con("tcp://127.0.0.1:3306", "organizer", "password", "Organizer");
    con.FillTreeModel(m_refTreeModel, &m_Columns);
}

void MainWindow::on_button_quit()
{
  hide();
}

void MainWindow::on_button_add_task()
{
    AddWindow *addwin = new AddWindow();
    addwin->show();
}
