//
// Created by payloads on 11/20/17.
//
#ifndef UNTITLED_MYSQL_CONTROLLER_H
#define UNTITLED_MYSQL_CONTROLLER_H
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <vector>
class MySQL_Controller{
public:
    enum show_type{
        fields,
        data
    }Type;
    bool debug;
    bool connected;
    //MySQL_Controller(std::string host,std::string user,std::string pass,std::string database,short int port);
    bool connect(std::string host,std::string user,std::string pass,std::string database,short int port);
    MYSQL_RES * Select(std::string sql);
    int Update(std::string sql);
    void ShowData(MYSQL_RES * mysqlRes);
    std::string Escape(std::string str);
    ~MySQL_Controller();
    int Insert(std::string tableName,std::vector<std::string>columns,std::vector<std::string>data);
    int real_Insert(std::string tableName,std::vector<std::string>columns,std::vector<std::string>data);
private:
    MYSQL_RES * Query(std::string sql);
    int exec(std::string sql);
    MYSQL * sqler;
    MYSQL_FIELD * mysql_field;
    MYSQL_ROW mysqlRow;
};
#endif //UNTITLED_MYSQL_CONTROLLER_H
