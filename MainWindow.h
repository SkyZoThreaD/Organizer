#ifndef GTKMM_MainWindow_H
#define GTKMM_MainWindow_H

#include <gtkmm.h>
#include "AddWindow.h"
#include "ModelColumns.h"

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();

protected:
  //Signal handlers:
  void on_button_quit();
  void on_button_add_task();
  void on_addtask_done();

  void RefreshList();

  ModelColumns m_Columns;

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_Quit;
  Gtk::Button m_Button_AddTask;

  //For the validated column:
  //You could also use a CellRendererSpin or a CellRendererProgress:
  Gtk::CellRendererText m_cellrenderer_validated;
  Gtk::TreeView::Column m_treeviewcolumn_validated;
  bool m_validate_retry;
  Glib::ustring m_invalid_text_for_retry;
};

#endif //GTKMM_MainWindow_H
