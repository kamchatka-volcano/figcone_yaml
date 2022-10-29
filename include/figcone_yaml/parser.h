#ifndef FIGCONE_YAML_PARSER_H
#define FIGCONE_YAML_PARSER_H

#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>

namespace figcone::yaml{
class Parser : public IParser{
public:
    TreeNode parse(std::istream& stream) override;
};

}

#endif //FIGCONE_YAML_PARSER_H