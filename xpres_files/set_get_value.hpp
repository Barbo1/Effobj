
/* Give a value to the token with the name equal to 'name'. If there is no token with such name,
 * nothing will change and false will return. 
 * */
template<typename T>
bool set_value(std::string_view name, const T& value) {
    auto it = this->token_info.begin();
    while (it != this->token_info.end() && std::get<0>(*it) != name) {
        it++;
    }
    if (it != this->token_info.end()) {
        auto& [_, type, data] = *it;
        switch (type) {
            case 'E':
                delete (Matrix<Xpres> *)data;
                break;
            case 'M':
                delete (Matrix<double> *)data;
                break;
            case 'm':
                delete (Matrix<int64_t> *)data;
                break;
            case 'e':
                delete (Xpres *)data;
                break;
            case 'd':
                delete (double *)data;
                break;
            case 'i':
                delete (int64_t *)data;
                break;
            default:
                break;
        }
        type = '\0';
        if (std::is_same_v<Matrix<Xpres>, T>) {
            type = 'E';
        } else if (std::is_same_v<Matrix<double>, T>) {
            type = 'M';
        } else if (std::is_same_v<Matrix<int64_t>, T>) {
            type = 'm';
        } else if (std::is_same_v<Xpres, T>) {
            type = 'e';
        } else if (std::is_same_v<double, T>) {
            type = 'd';
        } else if (std::is_same_v<int64_t, T>) {
            type = 'i';
        } else {
            std::cout << "retorno falso" << std::endl;
            return false;
        }
        data = (void *) (new T(value));
        return true;
    }
    return false;
}

/* Take the value of the token with the name equal to 'name'. If there is no token with such name,
 * return a {0, null} pair. 
 * */
std::pair<char, void*> get_value(std::string_view name) {
    auto it = token_info.begin();
    while (it != token_info.end() && std::get<0>(*it) != name) {
        it++;
    }
    if (it == token_info.end()) {
        return {'\0', (void*)nullptr};
    } else {
        return {std::get<1>(*it), std::get<2>(*it)};
    }
}

/*
   Get the token's information: their names, type and a pointer to 
   their value.
*/
std::vector< std::tuple< std::string, char, void*> > get_tokens () {
    return this->token_info;
}
