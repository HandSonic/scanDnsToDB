//
// Created by payloads on 11/22/17.
//
#include "core.h"
std::string Core::error_handle() {
        switch (Error){
            case CONFIG_CANT_READ:
            std::cout<< "Config file can't read." << std::endl;
            exit(EXIT_FAILURE);
            case MYSQL_CANT_CONNECT:
                std::cout<< "MySQL can't connect." << std::endl;
                exit(EXIT_FAILURE);
            case MYSQL_SQL_ERROR:
                return "Exec SQL error.";
                exit(EXIT_FAILURE);
            case OPTION_LOST:
                std::cout<< "Some config options lost."<< std::endl;
                exit(EXIT_FAILURE);
            case CONFIG_MYSQL_HOST_LOST:
                std::cout<< "Can't read mysql host from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case CONFIG_MYSQL_USER_LOST:
                std::cout<< "Can't read mysql user from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case CONFIG_MYSQL_PASS_LOST:
                std::cout<< "Can't read mysql password from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case CONFIG_MYSQL_TABLE_LOST:
                std::cout<< "Can't read mysql table name from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case MYSQL_TABLE_NOT_CREATED:
                std::cout<< "MySQL not found table name from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case NOT_GIVE_DOMAIN:
                std::cout<< "Not found domain."<< std::endl;
                exit(EXIT_FAILURE);
            case NOT_GIVE_DOMAIN_DICT:
                std::cout<< "Not found domain dict lists ."<< std::endl;
                exit(EXIT_FAILURE);
            case CONFIG_MYSQL_DATABSE_LOST:
                std::cout<< "Can't read mysql database name from config file."<< std::endl;
                exit(EXIT_FAILURE);
            case CANT_READ_DICT:
                std::cout<< "DICT file can't read."<< std::endl;
                exit(EXIT_FAILURE);
            default:
                std::cout<< "Unkown Error. Please contact my  [Email:payloads@aliyun.com]"<< std::endl;
                exit(EXIT_FAILURE);
        }
}



void Core::loadMysqlConfig() {
    std::fstream IO(Opt->config_file);
    if(!IO.is_open()){
        Error = CONFIG_CANT_READ;
        error_handle();
    }
    IO.close();
    if(!readConfigFile(Opt->config_file,"mysql_host",GLOBAL->mysql_host)){
        Error = CONFIG_MYSQL_HOST_LOST;
        error_handle();
    }
    if(!readConfigFile(Opt->config_file,"mysql_user",GLOBAL->mysql_user)){
        Error = CONFIG_MYSQL_HOST_LOST;
        error_handle();
    }
    if(!readConfigFile(Opt->config_file,"mysql_pass",GLOBAL->mysql_pass)){
        Error = CONFIG_MYSQL_PASS_LOST;
        error_handle();
    }
    if(!readConfigFile(Opt->config_file,"mysql_database",GLOBAL->mysql_database)){
        Error = CONFIG_MYSQL_DATABSE_LOST;
        error_handle();
    }
    if(!readConfigFile(Opt->config_file,"mysql_table",GLOBAL->mysql_table)){
        Error = CONFIG_MYSQL_TABLE_LOST;
        error_handle();
    }
}


bool Core::readConfigFile(std::string cfgfilepath, const std::string & key, std::string & value)
{
    std::fstream cfgFile;
    cfgFile.open(cfgfilepath);
    if( ! cfgFile.is_open())
    {
        //std::cout<<"can not open cfg file!"<<std::endl;
        return false;
    }
    std::string tmp;
    while(!cfgFile.eof())
    {
        getline(cfgFile,tmp);
        //cfgFile.getline(tmp,1000);
        std::string line(tmp);
        size_t pos = line.find('=');
        if(pos==std::string::npos) return false;
        std::string tmpKey = line.substr(0,pos);
        if(key==tmpKey)
        {
            if(line.substr(pos+1) == "null"){
                return true;
            }
            value = line.substr(pos+1);//取=号之后
            // std::cout << value << std::endl;
            cfgFile.close();
            return true;
        }
    }
    cfgFile.close();
    return false;
}

Core::Core(struct Options *Opt,struct globalSet * GLOBAL) {
    std::cout << "Loading ..." << std::endl;
    this->Opt = Opt;
    this->GLOBAL = GLOBAL;
    //loadMysqlConfig();
    //readDict();
    std::cout << "Loading Options Success !" << std::endl;
}

bool Core::readDict() {
    std::fstream IO(Opt->dict_path);
    if(!IO.is_open()){
        Error=CANT_READ_DICT;
        error_handle();
    }
    while(!IO.eof()){
        std::string line;
        getline(IO,line);
        line += "." + Opt->domain;
        dicLists.push_back(line);
        std::cout << "[*] " << line << std::endl;
    }
    IO.close();
    std::cout << "Load dict Success !" << std::endl;
}