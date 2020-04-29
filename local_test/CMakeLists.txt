cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project(DroneLocalTest)

set(INCLUDE_DIR ../main/src)

add_executable(DroneTest  ./tests/test_main.cpp
    ${INCLUDE_DIR}/app/pkg/input_pkg.cpp  ${INCLUDE_DIR}/app/pkg/adjust_pkg.cpp ${INCLUDE_DIR}/app/pkg/hello_pkg.cpp
    ${INCLUDE_DIR}/app/ses/session.cpp ${INCLUDE_DIR}/app/ses/builder.cpp
    ${INCLUDE_DIR}/app/ses/pip/pipeline.cpp ${INCLUDE_DIR}/app/ses/pip/processors.cpp ${INCLUDE_DIR}/app/ses/pip/builder.cpp
    ${INCLUDE_DIR}/app/ses/eve/event_chain.cpp ${INCLUDE_DIR}/app/ses/eve/builder.cpp
    )

target_include_directories(DroneTest PUBLIC ${INCLUDE_DIR}/)

