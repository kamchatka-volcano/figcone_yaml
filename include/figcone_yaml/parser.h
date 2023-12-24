#ifndef FIGCONE_YAML_PARSER_H
#define FIGCONE_YAML_PARSER_H

#include <figcone_tree/iparser.h>
#include <figcone_tree/tree.h>

namespace figcone::yaml {
class Parser : public IParser {
public:
    Tree parse(std::istream& stream) override;
};

} //namespace figcone::yaml

#endif //FIGCONE_YAML_PARSER_H