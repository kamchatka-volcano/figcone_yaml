#include <figcone_yaml/parser.h>
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "rapidyaml.hpp"
#include <figcone_tree/errors.h>
#include <figcone_tree/iparser.h>
#include <figcone_tree/tree.h>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

namespace figcone::yaml::detail {
namespace {
void on_error(const char* msg, size_t len, ryml::Location loc, void*)
{
    throw figcone::ConfigError{std::string{msg, len}, {loc.line, loc.col}};
}

ryml::Callbacks errorCallback()
{
    return {nullptr, nullptr, nullptr, on_error};
}

void parseYaml(const ryml::ConstNodeRef& yaml, figcone::TreeNode& node)
{
    auto str = [](const auto& yamlstr)
    {
        return std::string{yamlstr.data(), yamlstr.size()};
    };
    for (const auto& child : yaml.children()) {
        if (child.is_map()) {
            auto& newNode = node.asItem().addNode(str(child.key()));
            parseYaml(child, newNode);
        }
        else if (child.is_container()) {
            if (child.has_children() && child.first_child().is_map()) {
                auto& newNode = node.asItem().addNodeList(str(child.key()));
                for (const auto& item : child.children())
                    parseYaml(item, newNode.asList().emplaceBack());
            }
            else {
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

void parseYamlList(const ryml::ConstNodeRef& yaml, figcone::TreeNode& nodeList)
{
    if (yaml.is_stream() || yaml.is_seq()) {
        for (const auto& child : yaml.children()) {
            auto& node = nodeList.asList().emplaceBack();
            parseYaml(child, node);
        }
    }
    else
        parseYaml(yaml, nodeList.asList().emplaceBack());
}

} //namespace
} //namespace figcone::yaml::detail

namespace figcone::yaml {
Tree Parser::parse(std::istream& stream)
{
    stream >> std::noskipws;

    const auto input = std::string{std::istream_iterator<char>{stream}, std::istream_iterator<char>{}};
    auto yaml = ryml::Tree{};
    ryml::set_callbacks(detail::errorCallback());
    yaml = ryml::parse_in_arena(ryml::to_csubstr(input));

    auto treeRoot = figcone::makeTreeRootList();
    detail::parseYamlList(yaml.rootref(), *treeRoot);

    return Tree{std::move(treeRoot)};
}

} //namespace figcone::yaml