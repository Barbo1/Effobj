/* 
 * This module was made to store data in a tree. It defines the wordSet class that can store 
 * words in a tree that represents a set. The wordSets don't work for words larger than MAX_LEN_WORD, 
 * and the amount of letters allowed are LETTER_QUAN.
 * Methods:
 *  - aggregate_word, delete_word; that can change the set.
 *  - is_word, get_words_number, get_words_l, get_words_r; that doesn't alloc new 
 *      memory ones finished the operation.
 *  - +, -, *, !, n_defined, find_subword; that create an enterely new set.
 * */

#pragma once

#include <vector>
#include <string>

#define MAX_LEN_WORD 35
#define LETTER_QUAN 27

typedef struct node_word_set_struct * nodeWS;

struct node_word_set_struct {
  nodeWS sibling;
  nodeWS son;
  char letter;
  bool finished;
};

class WordSet {
  private:
    static nodeWS create_node (
        char letter, 
        bool finished, 
        nodeWS sibling = nullptr, 
        nodeWS son = nullptr
      );

    /* Delete a node, and the nodes below and along it. */
    static void delete_nodes (nodeWS node);

    /* Make a copy of the intern structure below a node of the WordSet and return
     * it. If the parameter first == false, the procedure also will copy the structure
     * along.
     * */
    static nodeWS copy_nodes (nodeWS node, bool first = true);

    /* Return a node that contain the words below either ws_1 or ws_2.
     * preconditions: ws_1, ws_2 != nullptr.
     * */
    static nodeWS aux_sum (nodeWS ws_1, nodeWS ws_2);

    /* Return a node that contain the words below both ws_1 and ws_2.
     * preconditions: ws_1, ws_2 != nullptr.
     * */
    static nodeWS aux_int (nodeWS ws_1, nodeWS ws_2);

    /* Return a node that contains the words below ws_1 with height less than top.
     * preconditions: node != nullptr.
     * */
    static nodeWS aux_less (nodeWS node, unsigned n, unsigned & top);

    /* Return a node that contain the words below ws_1 with the words with length 
     * greater than top.
     * preconditions: node != nullptr.
     * */
    static nodeWS aux_great (nodeWS node, unsigned n, unsigned & top);

    /* Return a node that contain the words below ws_1 but no ws_2.
     * preconditions: ws_1, ws_2 != nullptr.
     * */
    static nodeWS aux_sub (nodeWS ws_1, nodeWS ws_2);

    /* Put the words that start in tr in the std::vector vt by increase-lenght 
     * order. 
     * */
    static void aux_ordered_by_length (
        nodeWS node, 
        std::string str, 
        unsigned char m, 
        std::vector<std::string> * vt
      );

    /* Return the lenght of the most large word counting below the node. */
    static unsigned char aux_get_largest (nodeWS node, unsigned char m);

    /* Return a copy of the nodes that leads to, or follow, a node in the n-height
     * that have a 'letter' character, counting n below the node passed by parameter.
     * */
    static nodeWS aux_n_defined (nodeWS node, unsigned len, char & letter, unsigned char & n);

    /* Calculate the quantity of the words below the node. */
    static unsigned aux_many_word (nodeWS node);

    /* Return a copy of the nodes that leads to, or follow, a node that have a 
     * secuences of nodes with the subword in str.
     * */
    static nodeWS aux_find_subword (nodeWS node, unsigned pos, const char * str, const int & n); 


    nodeWS root;
  public:
    WordSet ();
    WordSet (const WordSet &);
    WordSet (WordSet &&) noexcept;
    WordSet & operator= (const WordSet &);
    WordSet & operator= (WordSet &&) noexcept;
    ~WordSet ();

    /* Put the word in the WordSet. Return 0 if all was ok, return 1
     * if there were a problem and the word will not be aggregated.
     * Theoretically, is posible to aggregate an word while having an 
     * iterator to another word in any case.
     * */
    unsigned aggregate_word (std::string_view word);

    /* Quit the word of the WordSet. Return 0 if all was ok, return 1
     * if there were a problem and the word will not be deleted.
     * */
    unsigned delete_word (const std::string & word);

    /* Return true if the parameter is in the WordSet, return false otherwise. */
    bool is_word (const std::string & word) const;

    /* Return the number of the words in the WordSet. */
    unsigned many_word () const;

    /* Return a vector with the words in the utter set, in increase-lenght order. */
    std::vector<std::string> ordered_by_length () const; 

    /* Return a vector with the specified number of words, taked randomly.
     * This method isn't yet declared as const.
     * Precondition: ws != null, cant_words <= gen_words_number().
     * */
    std::vector<std::string> pick_random (unsigned cant_words);

    /* Make a WordSet with the words of both operands. */
    WordSet operator+ (const WordSet &) const;

    /* Make a WordSet with the elements in ws1 who are not in ws2. */
    WordSet operator- (const WordSet &) const;

    /* Make a WordSet with the words that are in both operands. */
    WordSet operator* (const WordSet &) const;

    /* Make a WordSet with the reversed of the words in the operand. */
    WordSet operator! () const;

    /* Make a WordSet with the words that have a length shorter than the parameter. */
    WordSet operator< (unsigned top_length) const;

    /* Make a WordSet with the words that have a length larger than the parameter. */
    WordSet operator> (unsigned base_length) const;

    /* Make a WordSet with the words who's (unsigned parameter)-th 
     * letter is the defined by (char paramenter).
     * Precondition: unsigned char parameter > 0
     * */
    WordSet n_defined (unsigned char position, char letter) const;

    /* Make a WordSet with the words that contain the parameter.
     * ie.: parameter = "in" ->
     *      ...the WordSet could contain: "in", "inside", "minus", "principle", ...
     *      ...and couldn't contain: "hello", "cry", "breath", "notion", ...
     * Precodition: s != "";
     * */
    WordSet find_subword (const std::string & subword) const;

    /* The iterators are arrays of nodeWS of length MAX_LEN_WORD in where are stored the exact path to reach 
     * a word. It is useless after draw on the final word. If a iterator is used after the pointed word is 
     * deleted, the program will fail. The trick is to not have an iterator while deleting a word randomly 
     * from the set, but is posible delete if the iterator is pointing another one.
     * */
    class iterator {
      private:
        nodeWS * _nodes_;
        signed char _large_ = 0;

      public:
        iterator ();
        iterator (const WordSet &);
        iterator (const iterator &);
        iterator (iterator &&);
        iterator operator= (const iterator &);
        iterator operator= (iterator &&);
        ~iterator ();

        /* Return the pointed word by this iterator. */
        std::string operator* () const;

        /* Return true if both iterators points at the same word, in the same set. */
        bool operator== (const iterator&) const;

        /* Return true if this iterator is pointing "after" the last word
         * in the set, false otherwise.
         * */
        bool is_finished () const;

        /* Move forward this iterator to the next word. If the operation is used 
         * when is_finished() return true, an error will ocurre.
         * */
        iterator& operator++ ();

        friend class WordSet;
    };

    /* Return an iterator that points at the word passed by parameter. If the word
     * isn't in the set, an finished iterator will be returned.
     * */
    iterator find_word (const std::string & word) const;

    /* Quit the word of the WordSet. The iterator passed by parameter will last
     * finished.
     * */
    void delete_word (iterator & it);
};

/* Return a new WordSet with the words that are find in the file represented
 * by the path passed by parameter. The function checks if the path represent
 * an existent file, and if not, return a empty set. If the file is not "properly 
 * write"(this is, in an non-existent latin-based language) is posible that some
 * words will not be recognized.
 * */
WordSet from_file_to_set (const std::string &);
