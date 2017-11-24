//
// Created by payloads on 11/23/17.
//
#include "dns.h"
#include "mysql_controller.h"
bool DNS::Enum(struct Options * Opt,struct globalSet * GLOBAL,std::vector <std::string> dictList) {
    std::vector<std::string>columns = {"md51","domain","ip","md52"};
    for(auto it=dictList.begin();it != dictList.end();it++){
        // std::cout << *dictList.begin() << std::endl;
        name = ldns_dname_new_frm_str(it->c_str());
        if(!name){
            std::cout << *it <<"  域名格式不正确，请检查字典..." << std::endl;
            exit(EXIT_FAILURE);
        }
        res = ldns_resolver_new();
        int i =0; std::string ip;char str[16];
        nameserver = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_A, Opt->DnsServer.c_str());//这里可以指定DNS服务器
        (void)ldns_resolver_push_nameserver(res, nameserver);
        ldns_resolver_set_retry(res, 1);
        p = ldns_resolver_query(res, name, LDNS_RR_TYPE_A, LDNS_RR_CLASS_IN, LDNS_RD);//做DNS查询
        info = ldns_pkt_rr_list_by_type(p, LDNS_RR_TYPE_A, LDNS_SECTION_ANSWER);//获取A记录
        ldns_pkt_rr_list_by_type(p, LDNS_RR_TYPE_A, LDNS_SECTION_ANSWER);//获取A记录
        for(i = 0; i < ldns_rr_list_rr_count(info); i++) {
            //ldns_rr_print(stdout, ldns_rr_list_rr(info, i));//A记录可能有多个，所以这里循环获取
            rr = ldns_rr_list_rr(info, i);
            rr_rdf = ldns_rr_rdf(rr, 0);
            if (inet_ntop(AF_INET, ldns_rdf_data(rr_rdf), str, sizeof(str))) {
                printf("[*]%s -> %s \n", str,it->c_str());
                std::string iphost = str;
                std::string domain = "'"+*it+"'";
                std::string md51 = "md5('" + iphost + *it + "')";
                std::string md52 = "md5('"+*it + "')";
                iphost = "'"+iphost+"'";
                std::vector<std::string>data = {md51,domain,iphost,md52};
                controller->real_Insert(GLOBAL->mysql_table,columns,data);
            }
        }
        ldns_rr_list_deep_free(info);
        ldns_pkt_free(p);
        ldns_resolver_deep_free(res);
    }
}

DNS::DNS(MySQL_Controller *controller) {
    this->controller = controller;
}