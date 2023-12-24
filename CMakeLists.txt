cmake_minimum_required(VERSION 3.18)

project(figcone_yaml VERSION 1.0.0 DESCRIPTION "rapidyaml parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

set(INSTALL_FIGCONE_TREE ON)
SealLake_Import(
        figcone_tree 2.0.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG      v2.0.0
)
SealLake_Bundle(
        NAME figcone_rapidyaml
        URL https://github.com/biojppm/rapidyaml/releases/download/v0.5.0/rapidyaml-0.5.0.hpp
        TEXT_REPLACEMENTS
            _RYML_ FIGCONE_RYML
            "namespace ryml" "namespace figcone::yaml::ryml"
)
file(RENAME
    ${SEAL_LAKE_SOURCE_figcone_rapidyaml}/rapidyaml-0.5.0.hpp
    ${SEAL_LAKE_SOURCE_figcone_rapidyaml}/rapidyaml.hpp
)

SealLake_ObjectLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        SOURCES
            src/parser.cpp
        INCLUDES
            ${SEAL_LAKE_SOURCE_figcone_rapidyaml}
        INTERFACE_LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 2.0.0
)

SealLake_OptionalBuildSteps(tests)

