#include "../../xpres.hpp"

std::pair<char, void*> Xpres::evaluate () const {
    return evaluate_aux (this->root, this->token_info);
}
