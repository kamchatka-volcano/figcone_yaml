project(rapidyaml VERSION 0.4.1)

add_library(rapidyaml INTERFACE)
add_library(rapidyaml::rapidyaml ALIAS rapidyaml)

target_include_directories(
    rapidyaml
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

option(INSTALL_RAPIDYAML "Install rapidyaml library unconditionally" OFF)
if (INSTALL_RAPIDYAML)
    include(GNUInstallDirs)
    install(FILES ${PROJECT_SOURCE_DIR}/include/ryml_all.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    set(RAPIDYAML_PACK_PATH ${CMAKE_INSTALL_LIBDIR}/cmake/rapidyaml)
    install(TARGETS rapidyaml
            EXPORT rapidyaml-targets
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rapidyaml)
    install(EXPORT rapidyaml-targets
            FILE rapidyamlTargets.cmake
            NAMESPACE rapidyaml::
            DESTINATION ${RAPIDYAML_PACK_PATH})
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/rapidyamlConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
    )

    configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/rapidyamlConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/rapidyamlConfig.cmake
            INSTALL_DESTINATION ${RAPIDYAML_PACK_PATH}
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/rapidyamlConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/rapidyamlConfigVersion.cmake
            DESTINATION ${RAPIDYAML_PACK_PATH}
    )
endif()