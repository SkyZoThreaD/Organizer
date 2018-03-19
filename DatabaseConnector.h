/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "ModelColumns.h"

#include <sstream>
#include <gtkmm.h>

std::string StateNumberToString(int nb);
std::string UrgencyNumberToString(int nb);

class DatabaseConnector
{
private:
    std::string m_ServerIpPort;
    std::string m_User;
    std::string m_Password;
    std::string m_Database;

public:
    DatabaseConnector(std::string ServerIpPort, std::string User, std::string Password, std::string Database);

    void AddTask(std::string TaskTitle, std::string TaskContent, int TaskUrgency, int TaskState);
    void FillTreeModel(Glib::RefPtr<Gtk::ListStore> List, ModelColumns *m_Columns);

};
