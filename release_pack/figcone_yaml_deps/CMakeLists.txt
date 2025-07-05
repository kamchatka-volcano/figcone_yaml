cmake_minimum_required(VERSION 3.18)

project(figcone_yaml_deps)
include(seal_lake.cmake)

SealLake_v040_Bundle(
        NAME figcone_tree
        URL https://github.com/kamchatka-volcano/figcone_tree/releases/download/v2.2.0/figcone_tree-v2.2.0.zip
        SKIP_LOAD
        DESTINATION deps/figcone_tree
)

SealLake_v040_Bundle(
        NAME figcone_rapidyaml
        URL https://github.com/biojppm/rapidyaml/releases/download/v0.5.0/rapidyaml-0.5.0.hpp
        DESTINATION deps/figcone_rapidyaml
        TEXT_REPLACEMENTS
        _RYML_ FIGCONE_RYML
        "namespace ryml" "namespace figcone::yaml::ryml"
)

file(RENAME
        deps/figcone_rapidyaml/rapidyaml-0.5.0.hpp
        deps/figcone_rapidyaml/rapidyaml.hpp
)
