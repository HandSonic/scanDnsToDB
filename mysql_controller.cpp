#include "mysql_controller.h"
/*
MySQL_Controller::MySQL_Controller(std::string host,std::string user,std::string pass,std::string database,short int port) {
    sqler = mysql_init(NULL);
    debug = true;
    connected = false;
    if(!mysql_real_connect(sqler,host.c_str(),user.c_str(),pass.c_str(),database.c_str(),port,NULL,0)){
    //if(!mysql_real_connect(sqler,"127.0.0.1","root","root","test",3306,NULL,0)){
        std::cout << mysql_error(sqler)<< std::endl;
        connected= false;
        this->~MySQL_Controller();
    }
    Type = fields;
}
 */
MySQL_Controller::~MySQL_Controller(){
    mysql_close(sqler);
}
MYSQL_RES * MySQL_Controller::Query(std::string sql) {
    if(mysql_query(sqler,sql.c_str()) != 0 && debug){
        std::cout << "QUERY : " << sql  << std::endl;
        std::cout << mysql_error(sqler)<< std::endl;
        return NULL;
    }
    return mysql_use_result(sqler);
}

int MySQL_Controller::Update(std::string sql) {
    return exec(sql);
}

MYSQL_RES * MySQL_Controller::Select(std::string sql) {
    return Query(sql);
}
void MySQL_Controller::ShowData(MYSQL_RES * mysqlRes) {
    switch (Type){
        case fields:
            for(int i=0;mysql_field=mysql_fetch_field(mysqlRes);i++)//获取列名
            {
                std::cout << mysql_field->name << " \t ";
            }
            std::cout << "\n";
        default:
            while ((mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
            {
                for(int i=0;i<mysql_num_fields(mysqlRes);i++){
                    std::cout << mysqlRow[i] << " \t";
                }
                std::cout << "\n";
            }
    }
}

std::string MySQL_Controller::Escape(std::string str) { // escape attack string
    char resultSQL[(str.length()*2)+1];
    mysql_real_escape_string(sqler,resultSQL,str.c_str(),str.length());
    std::string realsql = resultSQL;
    return realsql;
}

int MySQL_Controller::exec(std::string sql) {
    int code = 0;
    if((code =mysql_query(sqler,sql.c_str())) != 0){
        std::cout << "[Error] :" << mysql_error(sqler) << std::endl;
        std::cout << "[SQL] :" << sql << std::endl;
        return -1;
    }
    return code;
}

int MySQL_Controller::Insert(std::string tableName, std::vector<std::string> columns, std::vector<std::string> data) {
    int code = 0;
    if(columns.size() != data.size() && debug){
        std::cout << "column count number not eq data number" << std::endl;
        return -1;
    }
    std::string sql = "INSERT INTO "+tableName;
    for(int j = 0; j < columns.size(); ++j) {
        if(j==0){
            sql += " (";
        }
        if(j == (columns.size()-1)){
            sql += Escape(columns[j])+")";
            break;
        }
        sql+=Escape(columns[j])+",";
    }
    sql+="VALUES";

    for(int j = 0; j < data.size(); ++j) {
        if(j==0){
            sql += " (";
        }
        if(j == (data.size()-1)){
            sql += "'"+Escape(data[j])+"')";
            break;
        }
        sql+= "'"+Escape(data[j])+"',";
    }
    if(debug){
        std::cout <<"[+]SQL : " <<sql << std::endl;
    }
    if((code =mysql_query(sqler,sql.c_str())) != 0){
        std::cout << "[Error] :" << mysql_error(sqler) << std::endl;
        std::cout << "[SQL] :" << sql << std::endl;
        return -1;
    }
    std::cout << "Insert ID:" << mysql_insert_id(sqler) << std::endl;
    return code;
}

int MySQL_Controller::real_Insert(std::string tableName, std::vector<std::string> columns,
                                  std::vector<std::string> data) {
    int code = 0;
    if(columns.size() != data.size() && debug){
        std::cout << "column count number not eq data number" << std::endl;
        return -1;
    }
    std::string sql = "INSERT INTO "+tableName;
    for(int j = 0; j < columns.size(); ++j) {
        if(j==0){
            sql += " (";
        }
        if(j == (columns.size()-1)){
            sql += columns[j]+")";
            break;
        }
        sql+=columns[j]+",";
    }
    sql+="VALUES";

    for(int j = 0; j < data.size(); ++j) {
        if(j==0){
            sql += " (";
        }
        if(j == (data.size()-1)){
            sql += data[j]+")";
            break;
        }
        sql+= data[j]+",";
    }
    if((code =mysql_query(sqler,sql.c_str())) != 0){
        std::cout << "[Error] :" << mysql_error(sqler) << std::endl;
        std::cout << "[SQL] :" << sql << std::endl;
        return -1;
    }
    if(debug){
        std::cout <<"[+]SQL : " <<sql << std::endl;
        std::cout << "Insert ID:" << mysql_insert_id(sqler) << std::endl;
    }
    return code;
}

bool MySQL_Controller::connect(std::string host, std::string user, std::string pass, std::string database,
                               short int port) {
    sqler = mysql_init(NULL);
    debug = true;
    connected = false;
    if(!mysql_real_connect(sqler,host.c_str(),user.c_str(),pass.c_str(),database.c_str(),port,NULL,0)){
        //if(!mysql_real_connect(sqler,"127.0.0.1","root","root","test",3306,NULL,0)){
        std::cout << mysql_error(sqler)<< std::endl;
        connected= false;
        //this->~MySQL_Controller();
        mysql_close(sqler);
        return false;
    }
    Type = fields;
    return true;
}