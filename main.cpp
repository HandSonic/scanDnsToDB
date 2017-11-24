#include "global.h"
#include "core.h"
#include "mysql_controller.h"
#include "dns.h"
#include <getopt.h>
#include <sstream>
#include <sys/time.h>
#define VERSION 0.11
#define CREATE_TIME 20171123
void help(char * argv[]){
    std::cout << "Usage:" << argv[0] << " -d<target domain> -t<thread counts> -r<dict path>" << std::endl;
    std::cout << "Example:" << argv[0] << " -dshadowteam.online -t5 -rsubnames.txt" << std::endl;
    std::cout << "Create :" << CREATE_TIME << std::endl;
}
int main(int argc,char * argv[]) {
    // v version
    // d domain
    // t thread numbers
    // o output
    // r dic dir
    // SomeError ERROR;
    struct Options Opt;
    struct globalSet GLOBAL;
    struct timeval times;
    std::stringstream timeStr;
    timeStr << times.tv_sec;
    gettimeofday(&times,NULL);
    std::string opt("v::d:t::o::r:h::s:u::"); int option;
    GLOBAL.debug=false;
    Opt.config_file = "./my.ini";
    Opt.DnsServer = "202.101.172.35";
    Opt.threadNum = 5;
    Opt.output = "./"+timeStr.str();
    Opt.start = times.tv_sec;
    Core CoreEngine(&Opt,&GLOBAL);
    while((option=getopt(argc,argv,opt.c_str())) != -1){
        switch (option){
            case 'v':
                std::cout << argv[0] << "  [Version " << VERSION  << "] by payloads "<< std::endl;
                std::cout <<"Email : " << " payloads@aliyun.com "<< std::endl;
                exit(0);
            case 'd':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.domain = optarg;
                break;
            case 'u':
                GLOBAL.debug = true;
                break;
            case 't':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
            //std::cout << optarg << " | "<< Opt.threadNum << std::endl;
                Opt.threadNum = atoi(optarg);
                break;
            case 'o':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.output = optarg;
                break;
            case 's':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.DnsServer = optarg;
                break;
            case 'r':
                if(optarg==NULL){
                    CoreEngine.Error=NOT_GIVE_DOMAIN_DICT;
                    std::cout << CoreEngine.error_handle() << std::endl;
                    exit(EXIT_FAILURE);
                }
                Opt.dict_path = optarg;
                break;
            case 'h':
                help(argv);
                exit(EXIT_SUCCESS);
            case 'c':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.config_file = optarg;
                break;
            default:
                help(argv);
                exit(EXIT_SUCCESS);
        }
    }
    if(optind < 2){
        help(argv);
        exit(EXIT_FAILURE);
    }
    MySQL_Controller  controller;
    controller.debug = true;
    CoreEngine.loadMysqlConfig();
    if(!controller.connect(GLOBAL.mysql_host,GLOBAL.mysql_user,GLOBAL.mysql_pass,GLOBAL.mysql_database,3306)){
        CoreEngine.Error=MYSQL_CANT_CONNECT;
        CoreEngine.error_handle();
    }
    CoreEngine.readDict();
    DNS run(&controller);
    run.Enum(&Opt,&GLOBAL,CoreEngine.dicLists);
    return 0;
}
