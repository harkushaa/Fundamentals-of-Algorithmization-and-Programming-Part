#include "./header-files/app.h"

void AppRun() {
    Py_Initialize();
    ConnectionParams params = {
        HOST, 
        PORT,
        DBNAME,
        USER,
        PASSWORD
    };
    pqxx::connection* connector = ConnectToDatabase(params); 
    if (!connector) {
        return;
    }
    elasticCreateIndex();
    menu(*connector);
    Py_Finalize();
};