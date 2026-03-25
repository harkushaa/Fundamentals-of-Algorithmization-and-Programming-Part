#pragma once

#include <string>
#include <pqxx/pqxx>

using std::string;

typedef struct ConnectionParams {
    string host;
    unsigned int port;
    string dbname;
    string user;
    string password;
} ConnectionParams;