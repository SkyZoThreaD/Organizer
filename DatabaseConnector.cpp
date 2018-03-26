#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector(std::string ServerIpPort, std::string User, std::string Password, std::string Database):
    m_ServerIpPort(ServerIpPort),
    m_User(User),
    m_Password(Password),
    m_Database(Database)
{

}

std::string StateNumberToString(int nb)
{
    switch(nb)
    {
        case 0: return "To do";
        case 1: return "Awaiting";
        case 2: return "Done";
        default:return "";
    }
}

std::string UrgencyNumberToString(int nb)
{
    switch(nb)
    {
        case 0: return "Not urgent at all";
        case 1: return "Not much urgent";
        case 2: return "Normal";
        case 3: return "A bit urgent";
        case 4: return "Very Urgent";
        default:return "";
    }
}

void DatabaseConnector::FillTreeModel(Glib::RefPtr<Gtk::ListStore> List, ModelColumns *m_Columns)
{
    try
    {
        sql::Driver *driver;
	    sql::Connection *con;
    	sql::Statement *stmt;
	    sql::ResultSet *res;

	    /* Create a connection */
	    driver = get_driver_instance();
	    con = driver->connect(m_ServerIpPort, m_User, m_Password);
	    /* Connect to the MySQL test database */
	    con->setSchema(m_Database);
	    stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Tasks"); //id state urgency title

	    while(res->next())
	    {
	        std::cout << res->getString(1) << std::endl;

	        //Fill the TreeView's model
	        Gtk::TreeModel::Row row = *(List->append());
	        row[m_Columns->m_col_id] = res->getInt(1);
	        row[m_Columns->m_col_title] = Glib::ustring(res->getString(4));
	        row[m_Columns->m_col_state] = StateNumberToString(res->getInt(2));
	        row[m_Columns->m_col_urgency] = UrgencyNumberToString(res->getInt(3));
	    }

	    delete res;
	    delete stmt;
	    delete con;

    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
	    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	    std::cout << "# ERR: " << e.what();
	    std::cout << " (MySQL error code: " << e.getErrorCode();
	    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void DatabaseConnector::AddTask(std::string TaskTitle, std::string TaskContent, int TaskUrgency, int TaskState)
{
    try
    {
        sql::Driver *driver;
	    sql::Connection *con;
	    sql::Statement *stmt;
	    sql::ResultSet *res;

	    /* Create a connection */
	    driver = get_driver_instance();
	    con = driver->connect(m_ServerIpPort, m_User, m_Password);
	    /* Connect to the MySQL test database */
	    con->setSchema(m_Database);

	    stmt = con->createStatement();

	    std::stringstream query;
	    query<<"INSERT INTO Tasks (State, Urgency, Content, Title) VALUES ('"<<TaskState<<"', '"<<TaskUrgency<<"', '"<<TaskContent<<"', '"<<TaskTitle<<"')";

	    res = stmt->executeQuery(query.str().c_str());
	    delete res;
	    delete stmt;
	    delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
    	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	    std::cout << "# ERR: " << e.what();
	    std::cout << " (MySQL error code: " << e.getErrorCode();
	    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}
