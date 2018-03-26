#ifndef ModelColumns_H
#define ModelColumns_H

#include <gtkmm.h>


//Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns();

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_title;
    Gtk::TreeModelColumn<Glib::ustring> m_col_state;
    Gtk::TreeModelColumn<Glib::ustring> m_col_urgency;
  };

#endif
