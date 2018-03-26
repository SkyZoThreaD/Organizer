/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
 
#include <iostream>
#include <libgnomedbmm.h>
#include <gtkmm.h>

int main(int argc, char* argv[])
{
  Gtk::Main kit(argc, argv);
  Gnome::Db::init("Example", "1.0", argc, argv);

  Glib::RefPtr<Gnome::Gda::Client> client = Gnome::Gda::Client::create();
 
  Glib::RefPtr<Gnome::Gda::DataModel> model;

  // Create a connection to an example SQLite database. The function might
  // fail, so we have to catch potential exceptions.
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    Glib::RefPtr<Gnome::Gda::Connection> connection = client->open_connection_from_string("SQLite", "DB_DIR=" LIBGNOMEDB_DATADIR ";DB_NAME=demo_db", "" /* username */, "" /* password */);
    model = connection->execute_select_command("SELECT * FROM products");
  }
  catch(const Glib::Error& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
#else
  std::auto_ptr<Glib::Error> error;
  Glib::RefPtr<Gnome::Gda::Connection> connection = client->open_connection_from_string("SQLite", "DB_DIR=" LIBGNOMEDB_DATADIR ";DB_NAME=demo_db", "" /* username */, "" /* password */, Gnome::Gda::ConnectionOptions(0), error);
  if(connection)
    model = connection->execute_select_command("SELECT * FROM products", error);

  if(error.get() != NULL)
  {
    std::cerr << error->what() << std::endl;
    return 1;
  }
#endif


  Gnome::Db::Grid grid(model);
  Gtk::Window window;

  window.set_title("Libgnomedbmm example window");
  window.set_default_size(400, 400);
  window.add(grid);
  window.show_all();

  kit.run(window);
  return 0;
}
