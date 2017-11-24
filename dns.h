//
// Created by payloads on 11/23/17.
//

#ifndef UNTITLED2_DNS_H
#define UNTITLED2_DNS_H
#include "global.h"
#include "dns.h"
#include <arpa/inet.h>
#include <ldns/ldns.h>
#include "mysql_controller.h"
// extern struct Options Opt;
class DNS{
public:
    DNS(MySQL_Controller * controller);
    bool Enum(struct Options * Opt,struct globalSet * GLOBAL,std::vector<std::string> dictList);
private:
    ldns_resolver   *res;
    ldns_rdf        *name;
    ldns_rdf        *nameserver;
    ldns_rdf        *rr_rdf;
    ldns_pkt        *p;
    ldns_rr_list    *info;
    ldns_rr         *rr;
    ldns_status     s;
    MySQL_Controller * controller;
};
#endif //UNTITLED2_DNS_H
