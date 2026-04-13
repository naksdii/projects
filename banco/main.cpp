#include <iostream>
#include <sqlite3.h>
#include <string>
#include <limits>
#include <optional>
#include <cstdlib> // para system()

void clearScreen()
{
#ifdef _WIN32
    system("CLS"); // Windows
#else
    system("clear"); // Linux / macOS
#endif
}
long hashIt(std::string text, int base);
void createUser(sqlite3 *db);
void mainMenu(sqlite3 *db, int &loggedId);
int loginAccount(sqlite3 *db);
int getRowCount(sqlite3 *db);
double balance(sqlite3 *db, int loggedId);
void userMenu(sqlite3 *db, int &loggedId);
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    sqlite3 *db;
    char *errMsg = nullptr;
    int rc = sqlite3_open("meu_banco.db", &db);
    int loggedId = 0;
    if (rc)
    {
        std::cerr << "wasnt possible to open database: " << sqlite3_errmsg(db) << std::endl;
    }

    const char *sql = R"(
        CREATE TABLE IF NOT EXISTS accounts (
            id INTEGER PRIMARY KEY,
            nome TEXT NOT NULL,
            hash TEXT,
            amount REAL
        );
    )";

    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    while (true)
    {
        clearScreen();
        if (loggedId > 0)
        {
            cout << "welcome, user  " << loggedId << endl;
            userMenu(db, loggedId);
        }
        else
        {
            mainMenu(db, loggedId);
        }
    }
}
void mainMenu(sqlite3 *db, int &loggedId)
{
    using std::cin;
    using std::cout;
    using std::endl;
    int choice = 0;
    cout << "CHOOSE ONE OPTION" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Log-in account" << endl;
    cout << "3. Power off app" << endl;
    cout << "choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        createUser(db);
        break;
    case 2:
        loggedId = loginAccount(db);
        cout << (loggedId > 0 ? "Logged in ID: " + std::to_string(loggedId) : "Login failed") << endl;
        break;
    case 3:
        sqlite3_close(db);
        exit(0);
    default:
        cout << "Invalid choice, try again." << endl;
    }
}
void createUser(sqlite3 *db)
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    char *errMsg = nullptr;
    int rc;

    string passwordtemp;
    string name;
    double amount = 50;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Creating new account..." << endl;
    cout << "name of account: ";
    std::cin >> name;
    cout << "password: ";
    cin >> passwordtemp;

    string insertSQL = "INSERT INTO accounts (nome, hash, amount) VALUES ('" + name + "', '" + std::to_string(hashIt(passwordtemp, 31)) + "', " + std::to_string(amount) + ");";

    rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
int loginAccount(sqlite3 *db)
{
    std::string name, password;
    std::cout << "user: ";
    std::cin >> name;
    std::cout << "password: ";
    std::cin >> password;
    int account = 0;
    long hashed = hashIt(password, 31);

    std::string query = "SELECT id, amount FROM accounts WHERE nome = '" + name + "' AND hash = '" + std::to_string(hashed) + "';";
    sqlite3_stmt *stmt;
    if (!(sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) || !(sqlite3_step(stmt) == SQLITE_ROW))
    {
        account = 0;
        return account;
    }
    account = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return account;
}
int getRowCount(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM accounts";
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return count;
}
long hashIt(std::string text, int base)
{
    long temp = 0;

    for (char c : text)
    {
        temp = temp * base + c;
    }
    return temp;
};
void userMenu(sqlite3 *db, int &loggedId)
{
    using std::cin;
    using std::cout;
    using std::endl;
    int choice = 0;
    cout << "CHOOSE ONE OPTION" << endl;
    cout << "1. Check balance" << endl;
    cout << "2. Deposit(unable)" << endl;
    cout << "3. Withdraw(unable)" << endl;
    cout << "4. Log out" << endl;
    cout << "choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Seu saldo é: R$ " << balance(db, loggedId) << endl;
        break;
    case 2:
    case 3:
        cout << "unable to use." << endl;
        break;
    case 4:
        loggedId = 0; // Log out
        break;
    default:
        cout << "Invalid choice, try again." << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getchar();
}
double balance(sqlite3 *db, int loggedId)
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT amount FROM accounts WHERE id = " + std::to_string(loggedId) + ";";
    double balance = 0.0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            balance = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return balance;
}