#pragma once
#include "./ConnectionParams.h"
#include <pqxx/pqxx>

pqxx::connection* ConnectToDatabase(const ConnectionParams& params);