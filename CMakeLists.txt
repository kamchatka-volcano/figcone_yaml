cmake_minimum_required(VERSION 3.18)

project(figcone_yaml VERSION 1.0.0 DESCRIPTION "rapidyaml parser adapter for figcone library")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(FIGCONE_YAML_SUBPROJECT OFF)
else()
    set(FIGCONE_YAML_SUBPROJECT ON)
endif()

find_package(figcone_tree 1.0 QUIET)
if (NOT figcone_tree_FOUND)
    message("Configuration info: figcone_tree library wasn't found on your system, downloading it from the GitHub repository")
    include (external/figcone_tree)
endif()

find_package(rapidyaml 0.4.1 QUIET)
if (NOT rapidyaml_FOUND)
    #message("Configuration info: rapidyaml library wasn't found on your system, downloading it from the GitHub repository")
    #include(external/rapidyaml)

    #until the single header version of rapidyaml is fixed in official repository
    message("Configuration info: rapidyaml library wasn't found on your system, using a bundled version")
    set(INSTALL_RAPIDYAML ON)
    add_subdirectory(lib/rapidyaml)
endif()

add_library(figcone_yaml INTERFACE)
add_library(figcone::figcone_yaml ALIAS figcone_yaml)

target_include_directories(
        figcone_yaml
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(figcone_yaml INTERFACE figcone::figcone_tree rapidyaml::rapidyaml)

option(ENABLE_TESTS "Enable tests" OFF)
if (ENABLE_TESTS AND NOT FIGCONE_YAML_SUBPROJECT)
    enable_testing()
    add_subdirectory(tests)
endif()

option(INSTALL_FIGCONE_YAML "Install figcone_yaml library unconditionally" OFF)
if (NOT FIGCONE_YAML_SUBPROJECT OR INSTALL_FIGCONE_YAML)
    include(GNUInstallDirs)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/figcone_yaml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    set(FIGCONE_YAML_PACK_PATH ${CMAKE_INSTALL_LIBDIR}/cmake/figcone_yaml)
    install(TARGETS figcone_yaml
            EXPORT figcone_yaml-targets
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/figcone_yaml)
    install(EXPORT figcone_yaml-targets
            FILE figcone_yamlTargets.cmake
            NAMESPACE figcone::
            DESTINATION ${FIGCONE_YAML_PACK_PATH})
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_yamlConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
    )

    configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/figcone_yamlConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_yamlConfig.cmake
            INSTALL_DESTINATION ${FIGCONE_YAML_PACK_PATH}
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_yamlConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_yamlConfigVersion.cmake
            DESTINATION ${FIGCONE_YAML_PACK_PATH}
    )
endif()
