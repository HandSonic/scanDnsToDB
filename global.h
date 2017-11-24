//
// Created by payloads on 11/23/17.
//

#ifndef UNTITLED2_GLOBAL_H
#define UNTITLED2_GLOBAL_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
struct Options{
    std::string dict_path;
    std::string nameServer;
    int threadNum;
    std::string domain;
    std::string output;
    long int start;
    std::string config_file;
    std::string DnsServer;
};
struct globalSet{
    std::string mysql_host;
    std::string mysql_user;
    std::string mysql_pass;
    std::string mysql_database;
    std::string mysql_table;
    std::string ext_file;
    bool debug;
};
#endif //UNTITLED2_GLOBAL_H
