#ifndef __SET_H__
#define __SET_H__

#include <cstdint>

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename K>
class set : public tree<K, K> {
 public:
  class ConstSetIterator;
  class SetIterator;
  using Key = K;
  using value_type = K;
  using reference = K &;
  using const_reference = const K &;
  using size_type = size_t;
  using const_iterator = ConstSetIterator;
  using iterator = SetIterator;

  set() : tree<K, K>(){};

  set(const set &s) : tree<K, K>(s){};

  set(set &&s) : tree<K, K>(std::move(s)){};

  set &operator=(set &&s) noexcept {
    tree<K, K>::operator=(std::move(s));
    return *this;
  }

  set(std::initializer_list<value_type> const &items) : tree<K, K>() {
    for (value_type i : items) tree<K, K>::add({i, i});
  };

  ~set() = default;

  class ConstSetIterator : public tree<K, K>::const_iterator {
   public:
    using tree<K, K>::const_iterator::current_;

    using tree<K, K>::const_iterator::operatorPlus;
    using tree<K, K>::const_iterator::operatorMinus;

    ConstSetIterator(const ConstSetIterator &) = default;

    ConstSetIterator(ConstSetIterator &&) noexcept = default;
    ConstSetIterator &operator=(ConstSetIterator &&) noexcept = default;

    ConstSetIterator(typename tree<K, K>::node *node_)
        : tree<K, K>::const_iterator(node_){};

    ConstSetIterator(tree<K, K> *tree_) : tree<K, K>::const_iterator(tree_){};

    ~ConstSetIterator() = default;

    ConstSetIterator &operator=(const ConstSetIterator &other) {
      ConstSetIterator tmp(other);
      current_ = tmp.GetNode();
      return *this;
    };

    value_type operator*() {
      if (!current_) {
        throw std::logic_error("Пустой итератор");
      }
      return current_->element_->first;
    }

    ConstSetIterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    ConstSetIterator operator++(int) {
      iterator tmp(*this);
      if (current_) {
        operatorPlus();
      }
      return tmp;
    }

    ConstSetIterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    ConstSetIterator operator--(int) {
      iterator tmp(*this);
      if (current_) {
        operatorMinus();
      }
      return tmp;
    }
  };

  class SetIterator : public ConstSetIterator {
   private:
    using ConstSetIterator::current_;
    using ConstSetIterator::operatorMinus;
    using ConstSetIterator::operatorPlus;

   public:
    SetIterator(typename tree<K, K>::node *node_) : ConstSetIterator(node_){};

    SetIterator(tree<K, K> *tree_) : ConstSetIterator(tree_){};

    ~SetIterator() = default;

    SetIterator &operator=(SetIterator &other) {
      SetIterator tmp(other);
      current_ = tmp.GetNode();
      return *this;
    };

    SetIterator(const SetIterator &) = default;
    SetIterator &operator=(const SetIterator &) = default;

    SetIterator(SetIterator &&) noexcept = default;
    SetIterator &operator=(SetIterator &&) noexcept = default;

    value_type operator*() {
      if (!current_) {
        throw std::logic_error("Пустой итератор");
      }
      return current_->element_->first;
    }

    SetIterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    SetIterator operator++(int) {
      iterator tmp(*this);
      if (current_) {
        operatorPlus();
      }
      return tmp;
    }

    SetIterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    SetIterator operator--(int) {
      iterator tmp(*this);
      if (current_) {
        operatorMinus();
      }
      return tmp;
    }
  };

  iterator begin() const {
    if (!this->root) throw std::out_of_range("tree does not exist");
    auto tmp = this->findMin(this->root);
    while (tmp->parent &&
           tmp->parent->element_->first == tmp->element_->first) {
      tmp = tmp->parent;
    }
    return iterator(tmp);
  }
  iterator end() const {
    if (!this->root) throw std::out_of_range("tree does not exist");
    return iterator(this->findMax(this->root));
  }

  void erase(iterator pos) {
    auto it = tree<K, K>::search(pos.GetNode()->element_->first);
    tree<K, K>::erase(it);
  }

  iterator find(const Key &key) {
    auto tmp = tree<K, K>::search(key);
    return tmp ? iterator(tmp) : this->end();
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    auto tmp = tree<K, K>::add(value, value);
    return {iterator(tmp.first.GetNode()), tmp.second};
  }

  template <class... Args>
  std::vector<std::pair<typename set<K>::iterator, bool>> insert_many(
      Args &&...args) {
    std::vector<std::pair<typename set<K>::iterator, bool>> vec;
    for (const auto &arg : {args...}) {
      vec.push_back(insert(arg));
    }
    return vec;
  }

  size_type max_size() { return (SIZE_MAX / sizeof(value_type)) / 10; }

  K &operator[](const K &key) {
    typename tree<K, K>::node *tmp = tree<K, K>::search(key);

    if (!tmp) {
      tmp = insert(key, K()).first.GetNode();
    }

    return tmp->element_->first;
  };
};

}  // namespace s21

#endif  // __SET_H__
