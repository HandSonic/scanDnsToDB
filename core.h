//
// Created by payloads on 11/22/17.
//

#ifndef UNTITLED2_CORE_H
#define UNTITLED2_CORE_H

#include "global.h"
#include "some_error.h"
class Core{
public:
    Core(struct  Options * Opt,struct globalSet * GLOBAL);
    SomeError Error;
    std::string error_handle();
    void loadMysqlConfig();
    bool readConfigFile(std::string cfgfilepath, const std::string & key, std::string & value);
    bool readDict();
    std::vector<std::string>dicLists;
private:
    struct Options * Opt;
    struct globalSet * GLOBAL;
};
#endif //UNTITLED2_CORE_H
