#include <fstream>
#include <utility>
#include "./worst.hpp"

#define PERMITED_CHAR(pt) ((65 <= *pt && *pt <= 90) || (97 <= *pt && *pt <= 122))

struct nodeWordSet{
    nodeWS sibling;
    nodeWS son;
    char letter;
    bool finished;
};

/*
   -----------------------------------------------------------------------------
   Here are the auxiliary functions used to implement the WordSet operations.
   -----------------------------------------------------------------------------
*/

/* Delete a node, and the nodes below and along it. */
static void delete_nodes(nodeWS node){
    if(node != nullptr){
        delete_nodes(node->sibling);
        delete_nodes(node->son);
        delete node;
    }
}

/*
    Make a copy of the intern structure below a node of the WordSet and return
    it. If the parameter first == false, the procedure also will copy the structure
    along.
*/
static nodeWS copy_nodes(nodeWS node, bool first = true){
    if(node != nullptr){
        nodeWS node_new = new nodeWordSet;
        node_new->letter = node->letter;
        node_new->finished = node->finished;
        if(first) [[unlikely]] {
            node_new->sibling = nullptr;
        } else [[likely]] {
            node_new->sibling = copy_nodes(node->sibling, false);
        }
        node_new->son = copy_nodes(node->son , false);
        return node_new;
    }
    return nullptr;
}

/* Calculate the quantity of the words below the node. */
static unsigned aux_words_number(nodeWS node){
    if(node != nullptr) 
        return node->finished + aux_words_number(node->sibling) + aux_words_number(node->son);
    return 0;
}

/* Return the lenght of the most large word counting below the node. */
static unsigned char aux_get_largest(nodeWS node, unsigned char m){
    if(node != nullptr){
        unsigned a = aux_get_largest(node->son, m+1), b = aux_get_largest(node->sibling, m);
        return b > a ? b : a;
    }
    return m;
}

/* 
   Return a copy of the nodes that leads to, or follow, a node in the n-height
   that have a 'letter' character, counting n below the node passed by parameter.
*/
static nodeWS aux_n_defined(nodeWS node, unsigned len, char & letter, unsigned char & n){ 
    if(node != nullptr) {
        if(len < n) {
            /* son_i iterate for the sons of the node, constructing the node if
            at least one son return a copied node(copied in the elseif) */
            nodeWS son_i = node->son, sons = nullptr, res, son_f = nullptr;
            while(son_i != nullptr) {
                res = aux_n_defined(son_i, len+1, letter, n);
                if(res != nullptr) {
                    (sons != nullptr ? sons->sibling : son_f) = res;
                    sons = res;
                }
                son_i = son_i->sibling;
            }
            if(son_f != nullptr) {
                nodeWS node_new = new nodeWordSet;
                node_new->letter = node->letter;
                node_new->finished = false;
                node_new->son = son_f;
                node_new->sibling = nullptr;
                return node_new;
            }
        } else if(node->letter == letter) { // len == n &&
            return copy_nodes(node);
        }
    }
    return nullptr;
}

/* 
   Return a copy of the nodes that leads to, or follow, a node that have a 
   secuences of nodes with the subword in str.
*/
static nodeWS aux_find_subword(nodeWS node, unsigned pos, const char * str, const int & n){ 
    if(node != nullptr) {
        if(pos < n || node->letter != str[pos]) {
            nodeWS son_i = node->son, sons = nullptr, res, son_f = nullptr;
            if(node->letter == str[pos]) 
                pos++;
            else
                pos = (node->letter == str[0] ? 1 : 0);
            while(son_i != nullptr) {
                res = aux_find_subword(son_i, pos, str, n);
                if(res != nullptr) {
                    (sons != nullptr ? sons->sibling : son_f) = res;
                    sons = res;
                }
                son_i = son_i->sibling;
            }
            if(son_f != nullptr) {
                res = node;
                node = new nodeWordSet;
                node->letter = res->letter;
                node->finished = false;
                node->son = son_f;
            node->sibling = nullptr;
            return node;
            }
        }
        return copy_nodes(node);
    }
    return nullptr;
}

/* put the words that start in tr in the std::vector vt by increase-lenght order. */
static void aux_get_words_l(nodeWS node, std::string str, unsigned char m, std::vector<std::string> * vt){
   if(node != nullptr){
      aux_get_words_l(node->sibling, str, m, vt);
      if(node->letter != 0) 
         str += node->letter;
      if(node->finished)
         vt[m-1].push_back(str);
      aux_get_words_l(node->son, str, m+1, vt);
   }
}

/*
   Return a node that contain the words below either ws_1 or ws_2.
   preconditions: ws_1, ws_2 != nullptr.
*/
static nodeWS aux_sum(nodeWS ws_1, nodeWS ws_2){
    nodeWS res, res_prev = nullptr, res_f = nullptr;
    ws_1 = ws_1->son;
    ws_2 = ws_2->son;
    while(ws_1 != nullptr && ws_2 != nullptr) {
        if(ws_1->letter == ws_2->letter) {
            res = new nodeWordSet;
            res->letter = ws_1->letter;
            res->finished = ws_1->finished || ws_2->finished;
            res->sibling = nullptr;
            res->son = aux_sum(ws_1, ws_2);
            ws_1 = ws_1->sibling;
            ws_2 = ws_2->sibling;
        } else if(ws_1->letter < ws_2->letter) {
            res = copy_nodes(ws_1);
            ws_1 = ws_1->sibling;
        } else {
            res = copy_nodes(ws_2);
            ws_2 = ws_2->sibling;
        }
        (res_prev == nullptr ? res_f : res_prev->sibling) = res;
        res_prev = res;
    }
    if(ws_2 != nullptr) {
        ws_1 = ws_2;
    }
    if(ws_1 != nullptr) {
        (res_prev == nullptr ? res_f : res_prev->sibling) = copy_nodes(ws_1, false);
    }
    return res_f;
}

/*
   Return a node that contain the words below both ws_1 and ws_2.
   preconditions: ws_1, ws_2 != nullptr.
*/
static nodeWS aux_int(nodeWS ws_1, nodeWS ws_2){
    nodeWS res, res1, res_prev = nullptr, res_f = nullptr;
    ws_1 = ws_1->son;
    ws_2 = ws_2->son;
    while(ws_1 != nullptr && ws_2 != nullptr){
        if(ws_1->letter == ws_2->letter){
            if((res1 = aux_int(ws_1, ws_2)) != nullptr || 
                    (ws_1->finished && ws_2->finished)) {
                res = new nodeWordSet;
                res->letter = ws_1->letter;
                res->finished = ws_1->finished && ws_2->finished;
                res->sibling = nullptr;
                res->son = res1;
                (res_prev == nullptr ? res_f : res_prev->sibling) = res;
                res_prev = res;
             }
             ws_1 = ws_1->sibling;
             ws_2 = ws_2->sibling;
        } else if(ws_1->letter < ws_2->letter) {
            ws_1 = ws_1->sibling;
        } else {
             ws_2 = ws_2->sibling;
        }
    }
    return res_f;
}

/*
   Return a node that contain the words below ws_1 but no ws_2.
   preconditions: ws_1, ws_2 != nullptr.
*/
static nodeWS aux_sub(nodeWS ws_1, nodeWS ws_2){
    nodeWS son, res, son_prev = nullptr, son_f = nullptr;
    ws_1 = ws_1->son;
    ws_2 = ws_2->son;
    while(ws_1 != nullptr && ws_2 != nullptr) {
        if(ws_1->letter == ws_2->letter) {
            if((res = aux_sub(ws_1, ws_2)) != nullptr || 
                    (ws_1->finished && !ws_2->finished)) {
                son = new nodeWordSet;
                son->letter = ws_1->letter;
                son->finished = ws_1->finished && !ws_2->finished;
                son->son = res; 
                son->sibling = nullptr;
                (son_prev == nullptr ? son_f : son_prev->sibling) = son;
                son_prev = son;
            }
            ws_1 = ws_1->sibling;
            ws_2 = ws_2->sibling;
        } else if(ws_1->letter < ws_2->letter) {
            son = copy_nodes(ws_1);
            (son_prev == nullptr ? son_f : son_prev->sibling) = son;
            son_prev = son;
            ws_1 = ws_1->sibling;
        } else {
            ws_2 = ws_2->sibling;
        }
    }
    if(ws_1 != nullptr) {
        (son_prev == nullptr ? son_f : son_prev->sibling) = copy_nodes(ws_1, false);
    }
    return son_f;
}

/*
   Return a node that contains the words below ws_1 with height less than top.
   preconditions: node != nullptr.
*/
static nodeWS aux_less(nodeWS node, unsigned n, unsigned & top){
    nodeWS sons_iter, res, res_prev = nullptr, res_f = nullptr;
    sons_iter = node->son;
    if(n < top){
        n++;
        while(sons_iter != nullptr){
            res = aux_less(sons_iter, n, top);
            if(res != nullptr){
                (res_f == nullptr ? res_f : res_prev->sibling) = res;
                res_prev = res;
            }
            sons_iter = sons_iter->sibling;
        }
        if(res_f != nullptr || node->finished){
            res = new nodeWordSet;
            res->finished = node->finished;
            res->letter = node->letter;
            res->sibling = nullptr;
            res->son = res_f;
        }
        return res;
    }
    return nullptr;
}

/*
   Return a node that contain the words below ws_1 with the words with length 
   greater than top.
   preconditions: node != nullptr.
*/
static nodeWS aux_great(nodeWS node, unsigned n, unsigned & top){
    nodeWS sons_iter, res, res_prev = nullptr, res_f = nullptr;
    sons_iter = node->son;
    if(n == top) {
        return copy_nodes(sons_iter, false);
    }
    n++;
    while(sons_iter != nullptr) {
        res = aux_great(sons_iter, n, top);
        if(res != nullptr)  {
            node = new nodeWordSet;
            node->finished = false;
            node->letter = sons_iter->letter;
            node->sibling = nullptr;
            node->son = res;
            (res_f == nullptr ? res_f : res_prev->sibling) = node;
            res_prev = node;
        }
        sons_iter = sons_iter->sibling;
    }
    return res_f;
}

/*
   ---------------------------------------------------------------------
   Here are the implementation of the operations described in worst.hpp.
   ---------------------------------------------------------------------
*/
/*
   --------------------
   iterator operations.
   --------------------
*/

WordSet::iterator::iterator(){
    _nodes_ = new nodeWS[MAX_LEN_WORD];
    _large_ = -1;
}

WordSet::iterator::iterator(const WordSet & ws){
    nodeWS tr = ws.root;
    _large_ = 0;
    _nodes_ = new nodeWS[MAX_LEN_WORD];
    while (tr->son != nullptr && !tr->finished){
        tr = tr->son;
        _nodes_[_large_] = tr;
        _large_++;
    }
    _large_--;
}

WordSet::iterator::iterator(const iterator& it){
    _large_ = it._large_;
    _nodes_ = new nodeWS[MAX_LEN_WORD];
    for(char unsigned i = 0; i < _large_; i++){
        _nodes_[i] = it._nodes_[i];
    }
}

WordSet::iterator::iterator(iterator&& it){
    delete [] _nodes_;
    _large_ = std::exchange(it._large_, -1); 
    _nodes_ = std::exchange(it._nodes_, nullptr);
}

WordSet::iterator WordSet::iterator::operator=(const iterator & it){
    _large_ = it._large_;
    _nodes_ = new nodeWS[MAX_LEN_WORD];
    for(char unsigned i = 0; i < _large_; i++){
        _nodes_[i] = it._nodes_[i];
    }
    return *this;
}

WordSet::iterator WordSet::iterator::operator=(iterator && it){
    delete [] _nodes_;
    _large_ = std::exchange(it._large_, -1);
    _nodes_ = std::exchange(it._nodes_, nullptr);
    return *this;
}

WordSet::iterator::~iterator(){
   delete [] _nodes_;
}

WordSet::iterator& WordSet::iterator::operator++(){
    nodeWS tr = _nodes_[_large_];
    if(tr->son != nullptr){
        tr = tr->son;
        _large_++;
        _nodes_[_large_] = tr;
    } else {
        while(_large_ >= 0 && _nodes_[_large_]->sibling == nullptr) {
            _large_--;
        }
        if(_large_ < 0) {
            return *this;
        }
        tr = _nodes_[_large_] = _nodes_[_large_]->sibling;
    }
    while(tr->son != nullptr && !tr->finished)  {
        tr = tr->son;
        _large_++;
        _nodes_[_large_] = tr;
    }
    return *this;
}

std::string WordSet::iterator::operator*() const {
    std::string str("");
    unsigned char i = 0;
    while(i <= _large_){
        str += _nodes_[i]->letter;
        i++;
    }
    return str;
}

bool WordSet::iterator::operator==(const iterator & it) const {
    if(it._large_ != _large_)
        return false;
    char i = 0;
    while(i <= _large_ && it._nodes_[i] == _nodes_[i]) {
        i++;
    }
    return i > _large_;
}

bool WordSet::iterator::is_finished() const {
   return _large_ == -1;
}

/*
   -------------------
   WordSet operations.
   -------------------
*/

WordSet::WordSet(){
   this->root = new nodeWordSet;
   this->root->letter = 0;
   this->root->finished = false;
   this->root->son = this->root->sibling = nullptr;
}

WordSet::WordSet(const WordSet & tr){
   if(&tr != this)
      this->root = copy_nodes(tr.root); 
}

WordSet::WordSet(WordSet && tr) noexcept{
   if(&tr != this){
      this->root = tr.root;
      tr.root = new nodeWordSet;
      tr.root->letter = 0;
      tr.root->finished = false;
      tr.root->son = tr.root->sibling = nullptr;
   }
}

WordSet & WordSet::operator=(const WordSet & tr){
   if(&tr != this){
      delete_nodes(this->root);
      this->root = copy_nodes(tr.root);
   }
   return *this;
}

WordSet & WordSet::operator=(WordSet && tr) noexcept {
   if(&tr != this){
      delete_nodes(this->root);
      this->root  = tr.root;
      tr.root = new nodeWordSet;
      tr.root->letter = 0;
      tr.root->finished = false;
      tr.root->son = tr.root->sibling = nullptr;
   }
   return *this;
}

WordSet::~WordSet(){
   delete_nodes(this->root);
}

unsigned WordSet::aggregate_word(const std::string & word){
    char * com = new char[MAX_LEN_WORD];
    char * str = com;
    char * fin;
    char * i;
    nodeWS tr;
    nodeWS tr_prev;
    nodeWS tr_father;
    unsigned char n = word.length();

    if(n <= MAX_LEN_WORD){
        word.copy(str, n);
        fin = str+n-1;
        while(fin != str && !PERMITED_CHAR(fin))
            fin--;
        while(fin != str && !PERMITED_CHAR(str))
            str++;
        /*
            enter if the there is to letters in distincts positions.
        */
        if(fin != str || PERMITED_CHAR(str)){
            fin++;
            i = str;
            while(i < fin && (PERMITED_CHAR(i) || *i == 39)){
                *i |= 32;
                i++;
            }
            /*
                enter if the symbols of the word are letters or '.
            */
            if(i == fin){
                tr = this->root->son;
                tr_father = this->root;
                tr_prev = nullptr;
                while(tr != nullptr && str < fin && tr->letter <= *str){
                    if(tr->letter != *str) {
                        tr_prev = std::exchange(tr, tr->sibling);
                    } else {
                        tr_father = std::exchange(tr, tr->son);
                        tr_prev = nullptr;
                        str++;
                    }
                }
                /*
                    enter if the word were not found.
                */
                if(!tr_father->finished || str < fin){
                    if(str < fin){
                        if(tr_prev == nullptr){
                            if(tr != nullptr && tr->letter > *str){
                                tr_prev = tr;
                                tr = new nodeWordSet;
                                tr->sibling = tr_prev;
                                tr_father->son = tr;
                                tr->finished = false;
                                tr->letter = *str;
                                tr->son = nullptr;
                                tr_father = tr;
                                str++;
                            }
                        }else{
                            if(tr == nullptr || tr->letter > *str){
                                tr = new nodeWordSet;
                                tr->sibling = std::exchange(tr_prev->sibling, tr);
                                tr->finished = false;
                                tr->letter = *str;
                                tr->son = nullptr;
                                tr_father = tr;
                                str++;
                            }
                        }
                    }
                    while(str < fin){
                        tr = new nodeWordSet;
                        tr->sibling = std::exchange(tr_father->son, tr);
                        tr->finished = false;
                        tr->letter = *str;
                        tr->son = nullptr;
                        tr_father = tr;
                        str++;
                    }
                    tr_father->finished = true;
                    delete [] com;
                    return 0;
                }
            }
        }   
    }
    delete [] com;
    return 1;
}

unsigned WordSet::delete_word(const std::string & word) {
    char * com = new char[MAX_LEN_WORD];
    char * str = com;
    char * fin;
    char n = word.length();
    nodeWS * data = new nodeWS[MAX_LEN_WORD];
    char i = -1;
    nodeWS tr_father = this->root;
    nodeWS tr = tr_father->son;
   
    if(n <= MAX_LEN_WORD) {
        word.copy(com, n);
        fin = str+n;
        /*
            search a word to delete.
        */
        while(tr != nullptr && str < fin) {
            if(tr->letter == *str) [[unlikely]] { 
                i++;
                data[i] = tr_father;
                tr_father = std::exchange(tr, tr->son);
                str++;
            }else [[likely]] {
                tr = tr->sibling;
            }
        }
        /*
            delete the finded word.
        */
        if(tr_father->finished && str == fin) {
            tr_father->finished = false;
            tr = std::exchange(tr_father, data[i]);
            i--;
            while(i != -1 && !tr->finished && tr->son == nullptr && 
                    tr->sibling == nullptr && tr_father->son == tr) {
                tr_father->son = nullptr;
                delete tr;
                tr = std::exchange(tr_father, data[i]);
                i--;
            }
            if(tr->son == nullptr && !tr->finished) {
                if(tr_father->son == tr) [[unlikely]] {
                    tr_father->son = tr->sibling;
                } else [[likely]] {
                    tr_father = tr_father->son;
                    while(tr_father->sibling != tr) {
                        tr_father = tr_father->sibling;
                    }
                    tr_father->sibling = tr->sibling;
                }
                delete tr;
            }
            delete [] com;
            delete [] data;
            return 0;
        }
    }
    delete [] data;
    delete [] com;
    return 1;
}

bool WordSet::is_word(const std::string & word) const {
    char i = 0;
    char n = word.length();
    nodeWS tr_father = this->root;
    nodeWS tr = tr_father->son;

    while(tr != nullptr && i < n) {
        if(tr->letter == word[i]) [[unlikely]] {
            tr_father = std::exchange(tr, tr->son);
            i++;
        }else [[likely]] {
            tr = tr->sibling;
        }
    }
    return tr_father->finished && i == n;
}

unsigned WordSet::get_words_number() const { return aux_words_number(this->root); }

std::vector<std::string> WordSet::get_words_l() const {
    unsigned char i = 0;
    unsigned char n = aux_get_largest(this->root->son, 0);
    std::vector<std::string> * vt = new std::vector<std::string>[n];
    std::vector<std::string> vt_new;
   
    aux_get_words_l(this->root, "", 0, vt);
    while(i < n) {
        while(!vt[i].empty()) {
            vt_new.push_back(vt[i].back());
            vt[i].pop_back();
        }
        i++;
    }
    delete [] vt;
    return vt_new;
}

std::vector<std::string> WordSet::get_words_r(unsigned cant_words) {
    std::vector<std::string> vt;
    std::vector<std::string>::iterator it;
    std::string str;
    nodeWS res;
    nodeWS * node_arr = new nodeWS[LETTER_QUAN];
    nodeWS * node_word = new nodeWS[MAX_LEN_WORD];
    char n;
    char i;
    char cant_;
   
    srand((unsigned)clock());
    while(cant_words > 0) {
        i = 0;
        cant_ = 0;
        res = this->root->son;
        
        /* pick a random branch of the tree. */
        while(res != nullptr) {
            
            /* pick all the childs. */
            n = 0;
            while(res != nullptr) {
                node_arr[n] = std::exchange(res, res->sibling);
                n++;
            }

            /* store one of the child randomly */
            res = node_arr[rand() % n];
            node_word[i] = res;
            cant_ += res->finished;
            i++;
            res = res->son;
        }

        /* pick a random word of the selected branch. */
        cant_ = (rand() % cant_) + 1;
        i = 0;
        str = "";
        while(cant_ > 0) {
            str += node_word[i]->letter; 
            if(node_word[i]->finished) {
                cant_--;
            }
            i++;
        }

        /* delete the selected word and store it*/
        vt.push_back(str);
        this->delete_word(str);
        cant_words--;
    }
    for(it = vt.begin(); it != vt.end(); it++) {
        this->aggregate_word(*it);
    }
    delete [] node_arr;
    delete [] node_word; 
    return vt;
}

WordSet WordSet::operator+(const WordSet & ws) const {
    WordSet ws_new = WordSet();
    ws_new.root->son = aux_sum(this->root, ws.root);
    return ws_new;
}

WordSet WordSet::operator-(const WordSet & ws) const {
    WordSet ws_new = WordSet();
    ws_new.root->son = aux_sub(this->root, ws.root);
    return ws_new;
}

WordSet WordSet::operator*(const WordSet & ws) const {
    WordSet ws_new = WordSet();
    ws_new.root->son = aux_int(this->root, ws.root);
    return ws_new;
}

WordSet WordSet::operator!() const {
    unsigned l, le, i;
    std::string str;
    WordSet::iterator it;
    WordSet ws;
    for(it = WordSet::iterator(*this); !it.is_finished(); ++it){
        str = *it;
        le = str.length();
        l = le>>1;
        le--;
        for(i = 0; i < l; i++)
            std::swap(str[le-i], str[i]);
        ws.aggregate_word(str);
    }
    return ws;
}

WordSet WordSet::operator<(unsigned top_lenght) const{
    WordSet ws = WordSet();
    ws.root->son = aux_less(this->root, 0, top_lenght);
    return ws;
}

WordSet WordSet::operator>(unsigned base_lenght) const{
    WordSet ws = WordSet();
    ws.root->son = aux_great(this->root, 0, base_lenght);
    return ws;
}

WordSet WordSet::n_defined(unsigned char position, char letter) const {
    WordSet tr = WordSet();
    nodeWS res = aux_n_defined(this->root, 0, letter, position);
    if(res != nullptr) {
        delete tr.root;
        tr.root = res;
    }
    return tr;
}

WordSet WordSet::find_subword(const std::string & word) const {
    WordSet tr = WordSet();
    nodeWS res = aux_find_subword(this->root, 0, word.c_str(), word.length()-1);
    if(res != nullptr){
        delete tr.root;
        tr.root = res;
    }
    return tr;
}

WordSet::iterator WordSet::find_word(const std::string & word) const {
    char i = 0;
    char n = word.length();
    nodeWS tr_father = this->root;
    nodeWS tr = tr_father->son;
    WordSet::iterator it;

    while(tr != nullptr && i < n) {
        if(tr->letter == word[i]) [[unlikely]] {
            it._nodes_[i] = tr;
            tr_father = std::exchange(tr, tr->son);
            i++;
        } else [[likely]] {
            tr = tr->sibling;
        }
    }
    if(tr_father->finished && i == n) {
        i--;
        it._large_ = i;
    } else {
        delete [] it._nodes_;
    }
    return it;
}

void WordSet::delete_word(WordSet::iterator & it){
    char i = it._large_;
    nodeWS nd = it._nodes_[i];
    nodeWS nd_father = it._nodes_[i-1];
    nd->finished = false;

    if(nd->son == nullptr){
        while(i > 0 && !nd->finished && nd->sibling == nullptr 
                && nd_father->son == nd) {
            delete nd;
            i--;
            nd = it._nodes_[i];
            nd_father = it._nodes_[i-1];
        }
        if(!nd->finished) {
            if(i == 0) {
                nd_father = this->root;
            }
            if(nd_father->son == nd) {
                nd_father->son = nd->sibling;
            } else {
                nd_father = nd_father->son;
                while(nd_father->sibling != nd) {
                    nd_father = nd_father->sibling;
                }
                nd_father->sibling = nd->sibling;
            }
            delete nd;
        } else {
            nd->son = nullptr;
        }
    }
    it._large_ = -1;
}

WordSet from_file_to_set(const std::string & path){
    char lett, *text;
    unsigned len, i = 0;
    std::string word = "";
    std::ifstream file(path);
    WordSet ws = WordSet();

    if(file.is_open()){
        file.seekg(0, std::ios_base::end);
        len = file.tellg();
        text = new char[len];
        file.seekg(0, std::ios_base::beg);
        file.read(text, len);
      
        while(i < len){
            lett = text[i];
            if(lett != ' ' && lett != '\n') [[likely]] {
                word += lett;
            }
            else [[unlikely]] {
                if(word.length() > 0) {
                    ws.aggregate_word(word);
                }
                word = "";
            }
            i++;
        }
        delete [] text;
        file.close();
    }
    return ws;
}

