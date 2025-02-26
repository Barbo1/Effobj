#include "../../xpres.hpp"

std::pair<char, void*> Xpres::iterator::evaluate () const {
    return evaluate_aux (points.top(), token_info);
}
