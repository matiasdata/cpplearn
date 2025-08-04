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
            // db.close();
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

    // 1st case
    try {
        std::cout << "=== Scenario 1: Client closes connection ===\n";
        DBConn safeConn(DBConnection::create());
        safeConn.close();  // No error shown because we assume success

    } catch (const std::exception& e) {
        std::cerr << "[main] Exception: " << e.what() << "\n";
    }

    // 2nd case
    try {
        std::cout << "\n=== Scenario 2: Client forgets to close, destructor handles it ===\n";
        DBConn unsafeConn(DBConnection::create());
        // Destructor will try to close and simulate failure

    } catch (const std::exception& e) {
        std::cerr << "[main] Exception: " << e.what() << "\n";
    }


    std::cout << "\n[main] Program finished safely.\n";
    return 0;
}

/*
1st case prints:
=== Scenario 1: Client closes connection ===
[DBConn] Client-initiated close. // 1) safeConn.close(); is called and initiates the close
[DBConnection] Attempting to close connection... // 2) this in turn calls db.close() from the DBConnection 
// 3) This throws an exception, and thus the stack unwinding begins.
[DBConn] Destructor attempting to close DBConnection... // 4) ~DBConn() is automatically called.
[DBConnection] Attempting to close connection... // this again calls db.close(), which again throws an exception.
[DBConn] ERROR in destructor: DB close failed: simulated error // this exception is caught inside the DBConn destructor. (see [DBConn])
[main] Exception: DB close failed: simulated error // but the first exception is caught in main. (see [main])

If instead we replace the DBConn destructor with
~DBConn()
{
    if(!closed)
    {
        std::cout << "[DBConn] Destructor attempting to close DBConnection...\n";
        db.close(); // may throw, but we don't catch it
    }
}

Then the same main results in an error, because throwing an exception during
stack unwinding causes std::terminate() to be called. Prints the following:

=== Scenario 1: Client closes connection ===
[DBConn] Client-initiated close.
[DBConnection] Attempting to close connection...
[DBConn] Destructor attempting to close DBConnection...
[DBConnection] Attempting to close connection...
libc++abi: terminating due to uncaught exception of type std::runtime_error: DB close failed: simulated error
zsh: abort      ./main2


2nd case prints:

=== Scenario 2: Client forgets to close, destructor handles it ===
[DBConn] Destructor attempting to close DBConnection... // 1) destructor is called automatically because the DBConn goes out of scope
[DBConnection] Attempting to close connection... // 2) this calls db.close()
[DBConn] ERROR in destructor: DB close failed: simulated error // 3) this throws an exception which is caught on the destructor.

[main] Program finished safely.


*/