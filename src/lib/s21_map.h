#ifndef __MAP_H__
#define __MAP_H__

#include <vector>

#include "s21_tree.h"

namespace s21 {

template <typename K, typename V>
class map : public tree<K, V> {
 public:
  // CONSTRUCTORS
  map() : tree<K, V>(){};
  map(std::initializer_list<typename tree<K, V>::value_type> const &items)
      : tree<K, V>(items){};
  map(const map &m) : tree<K, V>(m){};
  map(const std::pair<const K, V> &elem) : tree<K, V>(elem){};
  map(map &&m) noexcept : tree<K, V>(std::move(m)){};

  // DESTRUCTOR
  ~map() = default;

  map &operator=(map &&m) noexcept {
    tree<K, V>::operator=(std::move(m));
    return *this;
  }

  std::pair<typename map<K, V>::iterator, bool> insert(
      const typename tree<K, V>::value_type &value) {
    return tree<K, V>::add(value);
  }

  std::pair<typename map<K, V>::iterator, bool> insert(const K &key,
                                                       const V &obj) {
    return tree<K, V>::add(key, obj);
  }

  std::pair<typename tree<K, V>::iterator, bool> insert_or_assign(
      const K &key, const V &obj) {
    return tree<K, V>::add_or_assign(key, obj);
  }
  V &operator[](const K &key) {
    typename tree<K, V>::node *tmp = tree<K, V>::search(key);

    if (!tmp) {
      tmp = insert(key, V()).first.GetNode();
    }

    return tmp->element_->second;
  };

  V &at(const K &key) const {
    typename tree<K, V>::node *tmp = tree<K, V>::search(key);

    if (!tmp) {
      throw std::out_of_range("Key not found");
    }

    return tmp->element_->second;
  };

  template <class... Args>
  std::vector<std::pair<typename map<K, V>::iterator, bool>> insert_many(
      Args &&...args) {
    std::vector<std::pair<typename map<K, V>::iterator, bool>> vec;
    for (const auto &arg : {args...}) {
      vec.push_back(tree<K, V>::add(arg));
    }
    return vec;
  }
};
}  // namespace s21

#endif  // __MAP_H__
