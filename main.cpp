#include <iostream>
#include "database.h"

int main() {
    std::string name("NewDB");
    database *cpyDB = database::load_db(name);
    // database newDB(name);
    // std::cout << newDB.get_name() << " " << newDB.get_dir()  << std::endl;
    std::string key("0");
    std::string value("LAst test Value");
    cpyDB->set_key_value(key, value);
    std::cout << "Value Expected: " << value << "\nValue Gotten: "<< cpyDB->get_key_value(key) << std::endl;
    std::cout << "CopyDB: " << cpyDB->get_name() << std::endl;
    std::cout << "CopyDB: " << cpyDB->get_dir() << std::endl;
    // std::cout << "Value Expected: " << newDB.get_key_value(key) << "\nValue Gotten: "<< cpyDB->get_key_value(key) << std::endl;
    // newDB.delete_db();
    return 0;
}
