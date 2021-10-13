//
// Created by manbira on 10/10/21.
//

#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#import <string>
#include <unordered_map>

#define BASEDIR ".database"
#define FILE_ENDING "_string.kv"
#define FILE_ENDING_SIZE 10
#define FILE_EXT ".kv"

class database {
private:
    std::string name;
    std::string dir;
    std::string base_dir;
    std::unordered_map<std::string, std::string> key_value_store;
    std::string create_dir(std::string base_dir);
public:
    explicit database(std::string name);
    database(std::string name, std::string full_path);
    ~database();
    int delete_db();
    static database *load_db(std::string name);
    std::string get_name();
    int set_name(std::string name);
    std::string get_dir();
    int set_dir(std::string dir);
    int set_key_value(std::string key, std::string value);
    std::string get_key_value(std::string key);
};


#endif //DATABASE_DATABASE_H
