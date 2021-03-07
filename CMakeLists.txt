set(libRaskMqtt_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttworker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/raskmqtt_plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttsubscription.h

    ${CMAKE_CURRENT_LIST_DIR}/src/mqttworker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/raskmqtt_plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mqttsubscription.cpp

    ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
)

set(plugin_PATH plugins/Rask/Mqtt)

set(CMAKE_AUTOMOC ON)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 Mqtt REQUIRED)

add_library(RaskMqtt
    SHARED
        ${libRaskMqtt_SRCS}
)

set_target_properties(RaskMqtt
    PROPERTIES
        AUTOMOC TRUE
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../${plugin_PATH}
)

# Copy qmldir file
add_custom_command(
    TARGET RaskMqtt
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/${plugin_PATH}/qmldir
)

add_custom_command(
    TARGET RaskMqtt
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/../../${plugin_PATH}/qmldir
    )

target_link_libraries(RaskMqtt
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Mqtt
)
