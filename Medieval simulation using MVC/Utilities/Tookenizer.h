//
// Created by merom on 5/21/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_TOOKENIZER_H
#define HOMEWORK2_DEADLINE_04_06_23_TOOKENIZER_H
#include <iostream>
#include <algorithm>
#include <utility>
/**

    @brief The Isalpha struct is a predicate used to check if a character is alphabetic (a-z or A-Z).
    The struct overloads the function call operator () to implement the predicate logic.
    */

/**

    @brief The Delimiters class is used to define delimiters for tokenization.
    The class provides a way to specify excluded delimiters and defines the operator() to check if a character is a delimiter or not.
    */

/**

    @brief The TokenIterator class is an iterator for tokenizing a sequence of characters.
    The class template takes an input iterator and a predicate as template arguments.
    It provides the functionality to iterate over a range of characters and tokenize them based on the given predicate.
    The iterator returns tokens as strings.
    */

/**

    @brief Constructs a TokenIterator object with the given input range and predicate.
    @param begin The beginning of the input range.
    @param end The end of the input range.
    @param pred The predicate used to determine the tokenization criteria.
    */

/**

    @brief Dereferences the iterator to obtain the current token.
    @return The current token as a string.
    */

/**

    @brief Returns a pointer to the current token.
    @return A pointer to the current token.
    */

/**

    @brief Compares the iterator with another TokenIterator for equality.
    @param rv The other TokenIterator to compare with.
    @return true if the iterators are equal, false otherwise.
    */

/**

    @brief Compares the iterator with another TokenIterator for inequality.
    @param rv The other TokenIterator to compare with.
    @return true if the iterators are not equal, false otherwise.
    */

/**

    @brief Advances the iterator to the next token in the sequence.
    @return A reference to the updated iterator.
    */

/**

    @brief Postfix increment operator that returns a Proxy object holding the previous token.
    @return A Proxy object holding the previous token.
    */

/**

    @brief The Proxy class is used to hold the previous token when using the postfix increment operator.
    The class provides an operator* to access the previous token.
    */
struct Isalpha {
    bool operator()(char c) {
        return isalpha(c);
    }
};

class Delimiters {
    std::string exclude;
public:
    Delimiters() = default;
    explicit Delimiters(std::string excl)
            : exclude(std::move(excl)) {}
    bool operator()(char c) {
        return exclude.find(c) == std::string::npos;
    }
};

template<class InputIter, class Pred = Isalpha>
class TokenIterator : public std::iterator<
        std::input_iterator_tag, std::string, std::ptrdiff_t> {
    InputIter first, last;
    std::string word;
    Pred predicate;
public:
    TokenIterator(InputIter begin, InputIter end, Pred pred =
    Pred()) : first(begin), last(end), predicate(pred) { ++*this; }
    TokenIterator() = default;
/* SEE NEXT CHART for operator++() etc. */
    std::string operator*() const { return word; }

    const std::string* operator->() const { return &word; }

    bool operator==(const TokenIterator&) const {
        return word.size() == 0 && first == last;
    }
    bool operator!=(const TokenIterator& rv) const {
        return !(*this == rv);
    }

    // Prefix increment:
    TokenIterator& operator++() {
        word.resize(0);
        first = std::find_if(first, last, predicate);
        while (first != last && predicate(*first)){
            word.push_back(*first++);
        }

        return *this;
    }
// Postfix increment
    class Proxy {
        std::string word;
    public:
        explicit Proxy(std::string  w) : word(std::move(w)) {}
        std::string operator*() { return word; }
    };
    Proxy operator++(int) {
        Proxy d(word);
        ++*this;
        return d;
    }
};

#endif //HOMEWORK2_DEADLINE_04_06_23_TOOKENIZER_H
