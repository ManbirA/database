//
// Created by manbira on 10/10/21.
//

#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#import <string>
#define BASEDIR ".database"
#define FILE_EXT "_string.kv"

class database {
    private:
        std::string name;
        std::string dir;
        std::string base_dir;
    public:
        explicit database(std::string name);
        database(std::string name, std::string full_path);
        int delete_db();
        static database *load_db(std::string name);
        std::string get_name();
        int set_name(std::string name);
        std::string get_dir();
        int set_dir(std::string dir);
        std::string create_dir(std::string base_dir);
        int set_key_value(std::string key, std::string value);
        std::string get_key_value(std::string key);
};


#endif //DATABASE_DATABASE_H
