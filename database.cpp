//
// Created by manbira on 10/10/21.
//
#include <iostream>
#include <filesystem>
#include <fstream>
#include "database.h"

database::database(std::string name): base_dir(BASEDIR){
    this->set_name(name);
    std::string full_dir = this->create_dir(this->base_dir);
    this->set_dir(full_dir);
}

database::database(std::string name, std::string full_path) {
    this->set_name(name);
    this->set_dir(full_path);
    // Load all the db files
    for (const auto& file: std::filesystem::directory_iterator(this->get_dir())){
        if (file.exists() && file.is_regular_file() && file.path().extension() == FILE_EXT) {
            std::string key = file.path().filename();
            key = key.substr(0, key.length() - FILE_ENDING_SIZE);
            std::string value = get_key_value(key);
            key_value_store.insert({key, value});
        }
    }
}

database::~database() {
    this->key_value_store.clear();
    delete this;
}

database *database::load_db(std::string name) {
    std::string base_dir(BASEDIR);
    std::string full_path(base_dir + "/" + name);
    if (std::filesystem::exists(full_path)){
        return (new database(name, full_path));
    }
    return nullptr;
}

int database::delete_db() {
    if (std::filesystem::exists(this->get_dir())) {
        std::filesystem::remove_all(this->get_dir());
    }
    this->key_value_store.clear();
    delete this;
    return 0;
}

std::string database::get_name() {
    return this->name;
}

int database::set_name(std::string name) {
    this->name = name;
    return 0;
}

std::string database::get_dir() {
    return this->dir;
}

int database::set_dir(std::string dir){
    this->dir = dir;
    return 0;
}

std::string database::create_dir(std::string base_dir){
    // Create basedir if doesn't exist
    if (!std::filesystem::exists(base_dir)) {
        std::filesystem::create_directory(base_dir);
    }
    std::string db_folder(base_dir + "/" + this->get_name());
    if (!std::filesystem::exists(db_folder)) {
        std::filesystem::create_directory(db_folder);
    }
    return db_folder;
}

int database::set_key_value(std::string key, std::string value){
    std::ofstream os;
    os.open(this->get_dir() + "/" + key + FILE_ENDING, std::ios::out | std::ios::trunc);
    os << value;
    os.close();
    key_value_store.insert({key, value});
    return 0;
}

std::string database::get_key_value(std::string key){
    auto get_val = this->key_value_store.find(key);
    if (get_val != this->key_value_store.end()) {
        return get_val->second;
    } else {
        std::ifstream is(this->get_dir() + "/" + key + FILE_ENDING);
        std::string value;
        // Seek to end of file, reserve that amount of sapce for string
        is.seekg(0, std::ios::end);
        value.reserve(is.tellg());
        // Seek to beginning of file
        is.seekg(0, std::ios::beg);

        value.assign((std::istreambuf_iterator<char>(is)), (std::istreambuf_iterator<char>()));
        is.close();
        return value;
    }
}

