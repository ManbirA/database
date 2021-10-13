#include <iostream>
#include "database.h"

int main() {
    std::string name("Database");
    database *db = database::load_db(name);
    database *db_del = database::load_db("NewDB");
    std::string value0("Value 0");
    std::string value1("Value 1");
//    db.set_key_value("0", value0);
//    db.set_key_value("1", value1);

//    std::cout << "Expected Value: " << value0 << " Gotten Value: " << db->get_key_value("0") << std::endl;
//    std::cout << "Expected Value: " << value1 << " Gotten Value: " << db->get_key_value("1") << std::endl;
    db->delete_db();
    db_del->delete_db();
    return 0;

}
