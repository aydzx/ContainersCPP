#ifndef __MULTISET_H__
#define __MULTISET_H__

#include "../lib/s21_set.h"

namespace s21 {
template <typename K>
class multiset : public set<K> {
 public:
  class MultisetConstIterator;
  class MultisetIterator;
  using key_type = typename set<K>::key_type;
  using value_type = typename set<K>::value_type;
  using size_type = size_t;

  using const_iterator = MultisetConstIterator;
  using iterator = MultisetIterator;

  multiset() : set<K>(){};
  multiset(std::initializer_list<value_type> const &items) {
    for (value_type i : items) insert(i);
  };
  multiset(const multiset &s) : set<K>(s){};
  multiset(multiset &&s) noexcept : set<K>(std::move(s)){};
  ~multiset() = default;

  multiset &operator=(multiset &&s) noexcept {
    set<K>::operator=(std::move(s));
    return *this;
  }

  class MultisetConstIterator : public tree<K, K>::const_iterator {
   public:
    using tree<K, K>::const_iterator::current_;

    MultisetConstIterator(const MultisetConstIterator &) = default;

    MultisetConstIterator(MultisetConstIterator &&) noexcept = default;

    MultisetConstIterator(typename tree<K, K>::node *node_)
        : tree<K, K>::const_iterator(node_){};

    MultisetConstIterator(tree<K, K> *tree_)
        : tree<K, K>::const_iterator(tree_){};

    ~MultisetConstIterator() = default;

    MultisetConstIterator &operator=(const MultisetConstIterator &other) {
      MultisetConstIterator tmp(other);
      current_ = tmp.GetNode();
      return *this;
    };

    value_type operator*() {
      if (!current_) {
        throw std::logic_error("Пустой итератор");
      }
      return current_->element_ ? current_->element_->first : value_type();
    }

    typename tree<K, K>::node *max_range(typename tree<K, K>::node *tmp) {
      while (tmp->left && tmp->left->element_->first == tmp->element_->first) {
        tmp = tmp->left;
      };
      while (tmp->right && tmp->right->element_ &&
             tmp->right->element_->first == tmp->element_->first) {
        tmp = tmp->right;
      }
      return tmp;
    }

    typename tree<K, K>::node *min_range(typename tree<K, K>::node *tmp) {
      while (tmp->parent && tmp->element_ &&
             tmp->parent->element_->first == tmp->element_->first) {
        tmp = tmp->parent;
      }
      return tmp;
    }

    void operatorPlus() {
      typename tree<K, K>::node *tmp = current_;
      if (!tmp->element_) {
      } else if (tmp->left &&
                 tmp->left->element_->first == tmp->element_->first) {
        tmp = tmp->left;
      } else if (tmp->right && tmp->right->element_ &&
                 tmp->right->element_->first == tmp->element_->first) {
        tmp = tmp->right;
      } else if (current_->right) {
        tmp = tmp->right;
        typename tree<K, K>::node *tmp2 = tmp;
        while (tmp2->right && tmp2->right->element_ &&
               tmp2->element_->first == tmp2->right->element_->first)
          tmp2 = tmp2->right;
        if (tmp2->left) {
          tmp = tmp2;
          while (tmp->left) {
            tmp = tmp->left;
          }
          while (tmp->parent->element_->first == tmp->element_->first) {
            tmp = tmp->parent;
          }
        }
      } else if (tmp->parent && tmp->parent->left == tmp &&
                 tmp->parent->element_->first != tmp->element_->first) {
        typename tree<K, K>::node *upper = tmp->parent;
        while (upper->parent &&
               upper->element_->first == upper->parent->element_->first) {
          upper = upper->parent;
          tmp = upper;
        }
      }
      if (tmp == current_) {
        while ((tmp->parent) && tmp->parent->right == tmp) {
          tmp = tmp->parent;
        }
        if (tmp) {
          while (tmp->parent &&
                 tmp->parent->element_->first == tmp->element_->first)
            tmp = tmp->parent;
          if (tmp->parent) tmp = tmp->parent;
          while (tmp->parent &&
                 tmp->parent->element_->first == tmp->element_->first)
            tmp = tmp->parent;
        }
      }
      current_ = tmp ? tmp : current_;
    }

    void operatorMinus() {
      typename tree<K, K>::node *tmp = current_;

      typename tree<K, K>::node *last_element = max_range(tmp);
      typename tree<K, K>::node *first_element = min_range(tmp);

      if (tmp->parent && (!tmp->element_ || tmp->parent->element_->first ==
                                                tmp->element_->first)) {
        tmp = tmp->parent;
      } else if (last_element->left) {
        tmp = max_range(last_element->left);
        while (tmp->right) {
          tmp = tmp->right;
        }
      } else {
        tmp = first_element;
        while ((tmp->parent) && tmp->parent->left == tmp) {
          tmp = tmp->parent;
        }
        tmp = min_range(tmp);
        if (tmp) tmp = tmp->parent;
      }
      current_ = tmp ? tmp : current_;
    }

    MultisetConstIterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    MultisetConstIterator operator++(int) {
      this->operator++();
      return *this;
    }

    MultisetConstIterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    MultisetConstIterator operator--(int) {
      this->operator--();
      return *this;
    }
  };

  class MultisetIterator : public MultisetConstIterator {
   private:
    using MultisetConstIterator::current_;

    using MultisetConstIterator::operatorMinus;
    using MultisetConstIterator::operatorPlus;

   public:
    MultisetIterator(typename tree<K, K>::node *node_)
        : MultisetConstIterator(node_){};

    MultisetIterator(tree<K, K> *tree_) : MultisetConstIterator(tree_){};

    ~MultisetIterator() = default;

    MultisetIterator &operator=(MultisetIterator &other) {
      MultisetIterator tmp(other);
      current_ = tmp.GetNode();
      return *this;
    };

    MultisetIterator(const MultisetIterator &) = default;
    MultisetIterator &operator=(const MultisetIterator &) = default;

    MultisetIterator(MultisetIterator &&) noexcept = default;
    MultisetIterator &operator=(MultisetIterator &&) noexcept = default;

    MultisetIterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    MultisetIterator operator++(int) {
      this->operator++();
      return *this;
    }

    MultisetIterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    MultisetIterator operator--(int) {
      this->operator--();
      return *this;
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

  typename tree<K, K>::node *max_range(typename tree<K, K>::node *tmp) {
    auto it = iterator(tmp);
    return it.max_range(tmp);
  }

  typename tree<K, K>::node *min_range(typename tree<K, K>::node *tmp) {
    auto it = iterator(tmp);
    return it.min_range(tmp);
  }

  iterator min_range(const K &key) {
    auto tmp = tree<K, K>::search(key);
    return tmp ? iterator(min_range(tmp)) : iterator(this->end());
  }
  iterator max_range(const K &key) {
    auto tmp = tree<K, K>::search(key);
    return tmp ? iterator(max_range(tmp)) : iterator(this->end());
  }

  iterator upper_bound(const K &key) {
    auto it = this->begin();
    while (it != this->end() && *it <= key) {
      it++;
    }
    return it;
  }

  iterator lower_bound(const K &key) {
    auto it = this->begin();
    while (it != this->end() && *it < key) {
      it++;
    }
    return it;
  }

  void erase(iterator pos) {
    auto it = tree<K, K>::search(pos.GetNode()->element_->first);
    tree<K, K>::erase(it);
  }

  iterator find(const K &key) {
    auto tmp = tree<K, K>::search(key);
    return tmp ? iterator(tmp) : this->end();
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) {
      vec.push_back(insert(arg));
      // vec.push_back(insert(std::forward<Args>(arg)));
    }
    return vec;
  }

  std::pair<typename multiset<K>::iterator, bool> insert(
      const value_type &value) noexcept {
    auto tmp = tree<K, K>::search(value);
    typename tree<K, K>::node *node_new;
    if (tmp) {
      node_new = new typename tree<K, K>::node({value, value});
      if (this->root->element_ &&
          this->root->element_->first == tmp->element_->first) {
        if (this->root->right && this->root->right->element_ &&
            this->root->right->element_->first == tmp->element_->first) {
          tmp = this->root->right;
        }
        auto tmp2 = this->root;
        node_new->right = tmp2;
        tmp2->parent = node_new;
        this->root = node_new;
      } else {
        if (tmp->parent) {
          if (tmp->parent->left == tmp) {
            tmp->parent->left = node_new;
            node_new->parent = tmp->parent;
            tmp->parent = node_new;
            node_new->left = tmp;
          } else if (tmp->parent->right == tmp) {
            tmp->parent->right = node_new;
            node_new->parent = tmp->parent;
            tmp->parent = node_new;
            node_new->right = tmp;
          }
        }
      }
      (*this->setCount())++;
    } else {
      tmp = tree<K, K>::add(value, value).first.GetNode();
    }
    return {typename multiset<K>::iterator(tmp), 0};
  }

  std::pair<iterator, iterator> equal_range(const K &key) {
    return {lower_bound(key), upper_bound(key)};
  }

  size_type count(const K &key) {
    size_type c = 0;
    auto tmp = this->min_range(key);
    auto upper = this->max_range(key);
    while (tmp != upper) {
      tmp++;
      c++;
    }
    return ++c;
  }

  void merge(multiset &other) {
    if (!other.root || this->root == other.root) return;

    auto it = other.begin();
    while (it != other.end()) {
      it = other.max_range(*it);
      this->insert(*it);
      other.erase(it);
      it++;
    }
  }
};
}  // namespace s21

#endif  // __MULTISET_H__