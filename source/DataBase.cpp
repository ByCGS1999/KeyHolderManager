#include <Includes.h>
#include <SafeString.h>
#include <KeyContainer.h>
#include <sqlite3.h>
#include <DataBase.h>

sqlite3* db;

bool TableExists(const char* tableName)
{
	int rc = 0;
	std::string sqlSentence = "SELECT * FROM " + std::string(tableName) + ";";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sqlSentence.c_str(), -1, &stmt, 0);

	if(rc != SQLITE_OK)
	{
		std::cerr << "Failed to check if table exists: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	rc = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (rc == SQLITE_ROW) 
	{
		return true;
	}

	return false;
}

void Query(const char* SQL)
{
    int rc = 0;
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        sqlite3_column_int(stmt, 0);

        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
    return;
}

template <typename T>
T Query(const char* SQL)
{
    int rc = 0;
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return T(); // Return a default-constructed value for non-void types
    }

    // Step through the result of the query
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        // Default behavior: return a value for non-specialized types
        T result = sqlite3_column_int(stmt, 0); // Default to integer retrieval

        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return T(); // Return a default-constructed value if no result found
}

// Specialization for void* to handle BLOBs
template <>
const void* Query<const void*>(const char* SQL)
{
    int rc = 0;
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        // Retrieve the BLOB data
        const void* blob = sqlite3_column_blob(stmt, 0);

        sqlite3_finalize(stmt);
        return blob;
    }

    sqlite3_finalize(stmt);
    return nullptr;
}

// Specialization for std::string to handle TEXT
template <>
std::string Query<std::string>(const char* SQL)
{
    int rc = 0;
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, SQL, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        // Retrieve the TEXT data as std::string
        const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        sqlite3_finalize(stmt);
        return std::string(text ? text : "");
    }

    sqlite3_finalize(stmt);
    return "";
}


bool InitDB()
{
	int rc = sqlite3_open("data.db", &db);

	if (rc)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

    bool mod = false;

    if (!TableExists("Container"))
    {
        const char* SQL_SENTENCE = R"(
                CREATE TABLE IF NOT EXISTS Container (
                    ID INTEGER PRIMARY KEY,
                    Identifier TEXT NOT NULL,
                    Username TEXT NOT NULL,
                    Password TEXT NOT NULL, 
                    Key TEXT NOT NULL,  
                    IV TEXT NOT NULL
                );
        )";

        Query(SQL_SENTENCE);

        mod = true;
    }

    if (!TableExists("rdata"))
    {
        const char* SQL_SENTENCE = R"(
            CREATE TABLE IF NOT EXISTS rdata(
                IV TEXT PRIMARY KEY NOT NULL
            );
        )";

        Query(SQL_SENTENCE);

        mod = true;
    }

    return (mod != true) ? true : false;
}

void CloseDB()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool SaveContainer(const int index, const Container& container)
{
    const char* SQL_SENTENCE = "INSERT INTO Container (ID, Identifier, Username, Password, Key, IV) VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, SQL_SENTENCE, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Bind the parameters safely
    sqlite3_bind_int(stmt, 1, index);
    sqlite3_bind_text(stmt, 2, container.identifier.c_str(), -1, SQLITE_STATIC);   // Bind ID
    sqlite3_bind_text(stmt, 3, container.username.c_str(), -1, SQLITE_STATIC);     // Bind Username
    sqlite3_bind_text(stmt, 4, container.password.c_str(), -1, SQLITE_STATIC);     // Bind Password
    sqlite3_bind_text(stmt, 5, container.key.c_str(), -1, SQLITE_STATIC);          // Bind Key
    sqlite3_bind_text(stmt, 6, container.iv.c_str(), -1, SQLITE_STATIC);           // Bind IV

    // Execute the statement
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

Container LoadContainer(const std::string& ContainerId)
{
    return Container("","","");
}

void DeleteContainer(int ContainerId)
{
    const char* SQL_QUERY = "DELETE FROM Container WHERE ID = ?;";

    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Bind parameters to prevent SQL injection
    sqlite3_bind_int(stmt, 1, ContainerId);

    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
    }

    sqlite3_finalize(stmt);
}

int GetContainerId(const Container& container)
{
    const char* SQL_QUERY = "SELECT c.ID FROM Container as c WHERE c.Identifier = ? AND c.Username = ?;";

    sqlite3_stmt* stmt;
    int containerID = -1;  // Default value if not found

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    // Bind parameters to prevent SQL injection
    sqlite3_bind_text(stmt, 1, container.identifier.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, container.username.c_str(), -1, SQLITE_STATIC);

    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        containerID = sqlite3_column_int(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    return containerID;
}

std::string GetGlobalIV()
{
    const char* SQL_QUERY = "SELECT IV FROM rdata LIMIT 1;";
    sqlite3_stmt* stmt;
    std::string IV = "";

    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return IV;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        IV = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);

    return IV;
}


void InsertGlobalIV(const std::string& IV)
{
    if (!GetGlobalIV().empty())
        return;

    const char* SQL_QUERY = "INSERT INTO rdata (IV) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, IV.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
    }

    sqlite3_finalize(stmt);
}

void DeleteAllContainers()
{
    Query("DELETE FROM Container;");
}

void UpdateGlobalIV(const std::string& IV)
{
    Query("DELETE FROM rdata;");

    const char* SQL_QUERY = "INSERT INTO rdata (IV) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, IV.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
    }

    sqlite3_finalize(stmt);
}

std::vector<Container> LoadContainers()
{
    const char* SQL_QUERY = "SELECT ID, Identifier, Username, Password, Key, IV FROM Container;";
    sqlite3_stmt* stmt;
    std::vector<Container> containers = std::vector<Container>();

    if (sqlite3_prepare_v2(db, SQL_QUERY, -1, &stmt, 0) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return containers; // Return empty vector on failure
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const std::string identifier = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const std::string key = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        const std::string iv = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // Create a Container object and add it to the list
        containers.emplace(containers.begin() + id, Container(identifier, username, password, key, iv));
    }

    sqlite3_finalize(stmt);
    return containers;
}