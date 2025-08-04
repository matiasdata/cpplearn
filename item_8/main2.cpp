#include <iostream>
#include <string>
#include <stdexcept>

class DBConnection
{
public:
    DBConnection(){};
    static DBConnection create()
    {
        return DBConnection();
    }
    void close()
    {
        if(!alreadyClosed)
        {
            std::cout << "[DBConnection] Attempting to close connection...\n";
            
            // simulate a possible error
            throw std::runtime_error("DB close failed: simulated error");
            
            alreadyClosed = true;
            std::cout << "[DBConnection] Connection closed successfully.\n";
        }
    }
private:
    bool alreadyClosed = false;
};

// Resource manager for DBConnection
class DBConn{
public:
    DBConn(DBConnection conn) : db(std::move(conn)), closed(false) {}

    void close()
    {
        std::cout << "[DBConn] Client-initiated close.\n";
        db.close(); // may throw.
        closed = true;
    }

    ~DBConn()
    {
        if(!closed)
        {
            std::cout << "[DBConn] Destructor attempting to close DBConnection...\n";
            try
            {
                db.close();
                std::cout << "[DBConn] Destructor closed connection successfully.\n";
            }
            catch(const std::exception& e)
            {
                std::cerr  << "[DBConn] ERROR in destructor: " << e.what() << '\n';
                // Option 1: This swallow exception (safe)
                // std::abort(); // Option 2: force program termination (optional)
            }
            
        }
    }

private:
    DBConnection db;
    bool closed;
};


// Demonstration
int main() {
    try {
        // {
        //     std::cout << "=== Scenario 1: Client closes connection ===\n";
        //     DBConn safeConn(DBConnection::create());
        //     safeConn.close();  // No error shown because we assume success
        // }

        {
            std::cout << "\n=== Scenario 2: Client forgets to close, destructor handles it ===\n";
            DBConn unsafeConn(DBConnection::create());
            // Destructor will try to close and simulate failure
        }

    } catch (const std::exception& e) {
        std::cerr << "[main] Exception: " << e.what() << "\n";
    }

    std::cout << "\n[main] Program finished safely.\n";
    return 0;
}