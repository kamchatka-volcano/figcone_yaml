cmake_minimum_required(VERSION 3.18)

project(figcone_yaml VERSION 0.12.1 DESCRIPTION "rapidyaml parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

set(INSTALL_FIGCONE_TREE ON)
SealLake_Import(
        figcone_tree 0.12.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG      v0.12.0
)

SealLake_ObjectLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        SOURCES
            src/parser.cpp
        INTERFACE_LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 0.12.0
)

SealLake_OptionalBuildSteps(tests)

