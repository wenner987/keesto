//
// Created by Wenner on 2020/1/14.
//

#ifndef KEESTO_DEFINE_H
#define KEESTO_DEFINE_H

#define CONF_LOCATION "/tmp/keesto/conf/server.cnf"

enum HTTP_METHOD{
    HTTP_INVALID = 0,
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_OPTIONS
};

#endif //KEESTO_DEFINE_H
