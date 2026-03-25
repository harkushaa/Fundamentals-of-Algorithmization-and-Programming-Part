#include "./header-files/conn.h"

pqxx::connection* ConnectToDatabase(const ConnectionParams& params) {
 
    string connection_string = 
        "host=" + params.host +
        " port=" + std::to_string(params.port) +
        " dbname=" + params.dbname +
        " user=" + params.user +
        " password=" + params.password;

    auto* conn = new pqxx::connection(connection_string);

    if (conn->is_open()) { 
        return conn; 
    } else {
        delete conn;
        return nullptr;
    }     
} 