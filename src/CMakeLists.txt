file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

list(REMOVE_ITEM SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_library(RuletkaLib STATIC ${SOURCES})

target_compile_features(RuletkaLib PUBLIC cxx_std_23)
if(WIN32)
    add_compile_definitions(_AMD64_)
endif()

target_include_directories(RuletkaLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/application
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/beer
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/cellphone
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/handcuffs
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/inverter
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/magnifier
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/item/saw
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/autosave
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/difficulty
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/exit
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/heal
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/item
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/load
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/save
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/serialization
        ${CMAKE_CURRENT_SOURCE_DIR}/application/actions/main/shoot
        ${CMAKE_CURRENT_SOURCE_DIR}/application/ai
        ${CMAKE_CURRENT_SOURCE_DIR}/application/ai/easy
        ${CMAKE_CURRENT_SOURCE_DIR}/application/ai/hard
        ${CMAKE_CURRENT_SOURCE_DIR}/application/ai/manager
        ${CMAKE_CURRENT_SOURCE_DIR}/application/ai/normal
        ${CMAKE_CURRENT_SOURCE_DIR}/application/core
        ${CMAKE_CURRENT_SOURCE_DIR}/application/core/initializers
        ${CMAKE_CURRENT_SOURCE_DIR}/application/core/initializers/loop
        ${CMAKE_CURRENT_SOURCE_DIR}/application/core/initializers/round
        ${CMAKE_CURRENT_SOURCE_DIR}/application/core/manager
        ${CMAKE_CURRENT_SOURCE_DIR}/application/processor
        ${CMAKE_CURRENT_SOURCE_DIR}/application/processor/decision
        ${CMAKE_CURRENT_SOURCE_DIR}/application/processor/item
        ${CMAKE_CURRENT_SOURCE_DIR}/application/state
        ${CMAKE_CURRENT_SOURCE_DIR}/application/state/ai
        ${CMAKE_CURRENT_SOURCE_DIR}/application/state/decision
        ${CMAKE_CURRENT_SOURCE_DIR}/application/state/loop
        ${CMAKE_CURRENT_SOURCE_DIR}/application/state/serialization
        ${CMAKE_CURRENT_SOURCE_DIR}/composition
        ${CMAKE_CURRENT_SOURCE_DIR}/composition/builder
        ${CMAKE_CURRENT_SOURCE_DIR}/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/state
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/state/item
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/system
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/system/magazine
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/system/player
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/system/player/hp
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/system/player/inventory
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/logging
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/async
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/json
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/manager
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/txt
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/validator
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/serialization/wrapper
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities/configs
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities/configs/core
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities/configs/serialization
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities/enums
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure/utilities/tools
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/console
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/console/core
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/console/initializer
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/console/provider
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/console/renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/manager
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/core
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/initializer
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/provider
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/utilities/constants
        ${CMAKE_CURRENT_SOURCE_DIR}/presentation/sfml/utilities/structs
)

target_link_libraries(RuletkaLib
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        nlohmann_json::nlohmann_json
        Boost::static_string
)

add_executable(RuletkaAPP "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(RuletkaAPP PRIVATE RuletkaLib)
if(TARGET SFML::Main)
    target_link_libraries(RuletkaAPP PRIVATE SFML::Main)
elseif(TARGET sfml-main)
    target_link_libraries(RuletkaAPP PRIVATE sfml-main)
endif()
target_compile_features(RuletkaAPP PRIVATE cxx_std_23)

add_custom_command(TARGET RuletkaAPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:RuletkaAPP>/assets"
    COMMENT "Copying assets to output directory"
)