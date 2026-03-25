cmake_minimum_required(VERSION 3.10)

project(labwork8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SRCS
    main.cpp
    app/app.cpp
    db/db.cpp
    db/conn.cpp
    menu/menu.cpp
    utils/utils.cpp
    constants/constants.cpp
    elastic-search/elastic.cpp
    scripts/random.cpp
)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})

add_executable(main ${SRCS})

set(PQXX_INCLUDE_DIR /usr/local/include)
set(PQXX_LIBRARY /usr/local/lib/libpqxx.a)
include_directories(${PQXX_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${PQXX_LIBRARY} pq pthread)

set(CPR_INCLUDE_DIR /usr/local/include)
set(CPR_LIBRARY /usr/local/lib/libcpr.a)
include_directories(${CPR_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${CPR_LIBRARY})

set(NLOHMANN_JSON_INCLUDE_DIR /home/iharharkusha/json/single_include)
set(NLOHMANN_JSON_LIBRARY /home/iharharkusha/json/build/libnlohmann_json.a)
include_directories(${NLOHMANN_JSON_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${NLOHMANN_JSON_LIBRARY})

find_package(OpenSSL REQUIRED)
target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(CURL REQUIRED)
target_link_libraries(main PRIVATE CURL::libcurl)

target_link_libraries(main PRIVATE ${Python3_LIBRARIES})

set_target_properties(main PROPERTIES CLEAN_DIRECTORIES "YES")
