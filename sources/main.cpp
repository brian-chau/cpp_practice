#include <memory>

#include "DictionaryTrie.hpp"

int main() {
    std::unique_ptr<DictionaryTrie> dt(new DictionaryTrie());

    dt->predictCompletions("a", 10);
}