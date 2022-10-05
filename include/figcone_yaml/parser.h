#ifndef FIGCONE_YAML_PARSER_H
#define FIGCONE_YAML_PARSER_H

#include "detail/external/ryml_all.hpp"
#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>
#include <figcone_tree/errors.h>
#include <regex>

#include <vector>
#include <string>
#include <iostream>

namespace figcone::yaml::detail
{

    inline void on_error(const char* msg, size_t len, ryml::Location loc, void*)
    {
        throw figcone::ConfigError{std::string{msg, len}, {loc.line, loc.col}};
    }

    inline ryml::Callbacks errorCallback()
    {
        return {nullptr, nullptr, nullptr, on_error};
    }

    inline void parseYaml(const ryml::NodeRef& yaml, figcone::TreeNode& node)
    {
        auto str = [](const auto& yamlstr){ return std::string{yamlstr.data(), yamlstr.size()};};
        if (yaml.is_stream()) {
            parseYaml(yaml[0], node);
            return;
        }
        for (const auto& child : yaml.children()){
            if (child.is_map()){
                auto& newNode = node.asItem().addNode(str(child.key()));
                parseYaml(child, newNode);
            }
            else if (child.is_container()){
                if (child.has_children() && child.first_child().is_map()) {
                    auto& newNode = node.asItem().addNodeList(str(child.key()));
                    for (const auto& item : child.children())
                        parseYaml(item, newNode.asList().addNode());
                }
                else{
                    auto valuesList = std::vector<std::string>{};
                    for (auto item : child.children())
                        valuesList.emplace_back(str(item.val()));

                    node.asItem().addParamList(str(child.key()), valuesList);
                }
            }
            else if (child.is_keyval())
                node.asItem().addParam(str(child.key()), str(child.val()));
        }
    }
}

namespace figcone::yaml{
class Parser : public IParser{
public:
    TreeNode parse(std::istream& stream) override
    {
        stream >> std::noskipws;

        auto input = std::string{std::istream_iterator<char>{stream}, std::istream_iterator<char>{}};
        auto yaml = ryml::Tree{};
        ryml::set_callbacks(detail::errorCallback());
        yaml = ryml::parse_in_arena(ryml::to_csubstr(input));

        auto tree = figcone::makeTreeRoot();
        detail::parseYaml(yaml.rootref(), tree);

        return tree;
    }
};

}

#endif //FIGCONE_YAML_PARSER_H