set(libRaskMqtt_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/mqttworker.h
    ${CMAKE_CURRENT_LIST_DIR}/raskmqtt_plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/mqttsubscription.h

    ${CMAKE_CURRENT_LIST_DIR}/mqttworker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/raskmqtt_plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mqttsubscription.cpp

    ${CMAKE_CURRENT_LIST_DIR}/qmldir
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
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/${plugin_PATH}/qmldir
)

add_custom_command(
    TARGET RaskMqtt
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
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
