cmake_minimum_required(VERSION 3.14)

project(RaskMqtt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(libRaskMqtt_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttworker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/raskmqtt_plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttsubscription.h

    ${CMAKE_CURRENT_LIST_DIR}/src/mqttworker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/raskmqtt_plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttsubscription.cpp

    ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
)

set(QT_INSTALL_QMLDIR "$ENV{QTDIR}/qml")

set(plugin_PATH plugins/Rask/Mqtt)

set(CMAKE_AUTOMOC ON)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 Mqtt REQUIRED)

add_library(${PROJECT_NAME}
    SHARED
        ${libRaskMqtt_SRCS}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        AUTOMOC TRUE
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../${plugin_PATH}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Mqtt
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${QT_INSTALL_QMLDIR}/Rask/Mqtt)
install(FILES resources/qmldir DESTINATION ${QT_INSTALL_QMLDIR}/Rask/Mqtt)
