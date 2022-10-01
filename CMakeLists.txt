cmake_minimum_required(VERSION 3.18)

project(figcone_yaml VERSION 0.11.0 DESCRIPTION "rapidyaml parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

set(INSTALL_FIGCONE_TREE ON)
SealLake_FindOrDownload(
        figcone_tree 0.11.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        cmake_maintenance
)

SealLake_HeaderOnlyLibrary(
        NAMESPACE figcone
        INCLUDES detail/external
        BUILD_STAGE_INCLUDES detail/external
        LIBRARIES figcone::figcone_tree
)

SealLake_OptionalBuildSteps(
        IF_ENABLED_AND_STANDALONE tests
)

