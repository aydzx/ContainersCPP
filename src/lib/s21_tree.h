#ifndef __TREE_H__
#define __TREE_H__

namespace s21 {
template <typename K, typename V>
class tree {
 public:
  //   Member type

  // Тип ключа в дереве
  using key_type = K;

  // Тип значения (значение, связанное с каждым ключом) в дереве
  using mapped_type = V;

  // Тип элемента, представляющего собой пару из ключа и значения
  using value_type = std::pair<const key_type, mapped_type>;

  // Псевдоним типа ссылки на элемент
  using reference = value_type &;

  // Псевдоним типа константной ссылки на элемент
  using const_reference = value_type &;

  // Тип размера, используемый для представления размера дерева
  using size_type = size_t;

  class node {
   public:
    value_type *element_;

    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;

    node();
    node(const value_type elem);
    virtual ~node() {
      if (this->right) delete this->right;
      if (this->element_) delete this->element_;
      if (this->left) delete this->left;
      // if (this->parent) delete this->parent;
    };

    void setElement(const value_type *elem) {
      delete this->element_;
      this->element_ = elem ? new value_type(*elem) : nullptr;
    }
  };

  node *root = nullptr;
  unsigned int count = 0;

  // CONSTRUCTORS
  tree() noexcept;
  tree(const value_type &elem) noexcept;
  tree(std::initializer_list<value_type> const &items) noexcept;
  tree(tree &&other) noexcept;
  tree(const tree &other) noexcept;

  // DESTRUCTOR
  virtual ~tree();

  // OVERLOAD OPERATORS
  tree &operator=(const tree &other) noexcept;
  tree &operator=(tree &&other) noexcept;

  // ITERATORS
  class const_iterator {
   public:
    using value_type = typename tree<K, V>::value_type;

    typename tree<K, V>::node *current_;
    void operatorPlus() {
      node *tmp = current_;
      if (current_->right) {
        tmp = tmp->right;
        while (tmp->left) {
          tmp = tmp->left;
        }
      } else {
        while ((tmp->parent) && tmp->parent->right == tmp) {
          tmp = tmp->parent;
        }
        if (tmp) tmp = tmp->parent;
      }
      current_ = tmp ? tmp : current_;
    }

    void operatorMinus() {
      node *tmp = current_;
      if (current_->left) {
        tmp = tmp->left;
        while (tmp->right) {
          tmp = tmp->right;
        }
      } else {
        while ((tmp->parent) && tmp->parent->left == tmp) {
          tmp = tmp->parent;
        }
        if (tmp) tmp = tmp->parent;
      }
      current_ = tmp ? tmp : current_;
    }

   public:
    const_iterator(const tree<K, V> *tree) : current_(tree->root){};
    const_iterator(typename tree<K, V>::node *node_) : current_(node_){};
    const_iterator(const const_iterator &other) : current_(other.current_){};
    // Операторы сравнения
    bool operator==(const const_iterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }

    const_iterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp(*this);
      if (current_) {
        operatorPlus();
      }
      return tmp;
    }

    const_iterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp(*this);
      if (current_) {
        operatorMinus();
      }
      return tmp;
    }

    value_type &operator*() const {
      if (!current_) {
        throw std::logic_error("Пустой итератор");
      }
      return *(current_->element_);
    }

    const value_type *operator->() const {
      if (current_) {
        return &(current_->element_);
      } else {
        return nullptr;
      }
    }

    tree<K, V>::node *GetNode() { return this->current_; }
  };

  class iterator : public const_iterator {
   private:
    using const_iterator::current_;

    using const_iterator::operatorMinus;
    using const_iterator::operatorPlus;

   public:
    iterator(tree<K, V> *tree) : const_iterator(tree) {}
    iterator(typename tree<K, V>::node *node_) : const_iterator(node_) {}

    iterator operator++() {
      if (current_) {
        operatorPlus();
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      if (current_) {
        operatorPlus();
      }
      return tmp;
    }

    iterator operator--() {
      if (current_) {
        operatorMinus();
      }
      return *this;
    }

    iterator operator--(int) {
      iterator tmp(*this);
      if (current_) {
        operatorMinus();
      }
      return tmp;
    }

    value_type *operator->() {
      if (current_) {
        return current_->element_;
      } else {
        return nullptr;
      }
    }

    value_type &operator*() {
      if (!current_) {
        throw std::logic_error("Пустой итератор");
      }
      return *(current_->element_);
    }
  };

  // Возвращает итератор, указывающий на минимальный элемент в дереве
  iterator begin() const;

  // Возвращает итератор, указывающий на элемент, следующий за последним в
  // дереве
  iterator end() const;

  // Проверяет, пустое ли дерево
  bool empty();

  // Возвращает количество элементов в дереве
  size_type size();

  // Возвращает максимально возможное количество элементов в дереве
  size_type max_size();

  // Очищает содержимое дерева, удаляя все его элементы
  void clear();

  // Вставляет элемент в дерево и возвращает пару, содержащую итератор на
  // вставленный элемент и флаг, указывающий, был ли элемент успешно вставлен
  std::pair<iterator, bool> add(const value_type &value);

  // Вставляет пару ключ-значение в дерево и возвращает пару, содержащую
  // итератор на вставленный элемент и флаг, указывающий, был ли элемент успешно
  // вставлен
  std::pair<iterator, bool> add(const K &key, const V &obj);

  // Вставляет новый узел в дерево с указанным родительским узлом и возвращает
  // указатель на новый узел
  node *add(node *new_node, node *parent_node);

  // Вставляет пару ключ-значение в дерево или обновляет значение существующего
  // ключа, если он уже присутствует, и возвращает пару, содержащую итератор на
  // вставленный или обновленный элемент и флаг, указывающий, был ли элемент
  // вставлен или обновлен
  std::pair<iterator, bool> add_or_assign(const K &key, const V &obj);

  // Обменивает содержимое данного дерева с содержимым другого дерева
  void swap(tree &other);

  // Объединяет содержимое данного дерева с содержимым другого дерева, добавляя
  // элементы из другого дерева в данное дерево
  void merge(tree &other);

  // Ищет узел с указанным ключом в дереве и возвращает указатель на этот узел
  node *search(const K &key_search) const;

  // Ищет узел с указанным ключом в дереве, начиная с указанного родительского
  // узла, и возвращает указатель на этот узел
  node *search(const K &key_search, node *parent_node) const;

  // Удаляет узел с указанным ключом из дерева и возвращает указатель на новый
  // корень дерева
  node *erase(const K &key_del);

  // Удаляет указанный узел из дерева и возвращает указатель на новый корень
  // дерева
  node *erase(node *_node);

  // Удаляет элемент, на который указывает итератор
  void erase(iterator pos);

  // Проверяет, содержит ли дерево узел с указанным ключом
  bool contains(const K &key);

 protected:
  // Находит узел с минимальным значением ключа в дереве, начиная с указанного
  // родительского узла, и возвращает указатель на этот узел
  node *findMin(const node *parent_node) const;

  // Находит узел с максимальным значением ключа в дереве, начиная с указанного
  // родительского узла, и возвращает указатель на этот узел
  node *findMax(const node *parent_node) const;

  unsigned int *setCount();
};

// Перегруженный оператор вставки в поток для класса tree.
// Выводит элементы дерева в отсортированном порядке.
template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, tree<K, V> &t);

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, tree<K, V> &t) {
  auto it = t.begin();
  while (it != t.end()) {
    os << "Key: " << it->first << ", Value: " << it->second << "\n";
    it++;
  }
  os << "Key: " << it->first << ", Value: " << it->second << "\n";
  return os;
};

template <typename K, typename V>
tree<K, V>::tree() noexcept : root(nullptr), count(0) {
  this->root = new node();
};

template <typename K, typename V>
tree<K, V>::tree(const value_type &elem) noexcept {
  this->count = 1;
  this->root = new node(elem);
  this->root->right = new node();
  this->root->right->parent = this->root;
}

template <typename K, typename V>
tree<K, V>::tree(std::initializer_list<value_type> const &items) noexcept
    : root(nullptr), count(0) {
  for (value_type i : items) add(i);
};

template <typename K, typename V>
tree<K, V>::tree(tree &&other) noexcept {
  *this = std::move(other);
  other.clear();
};

template <typename K, typename V>
tree<K, V>::tree(const tree &other) noexcept {
  *this = other;
};

template <typename K, typename V>
tree<K, V>::~tree() {
  this->clear();
};

template <typename K, typename V>
tree<K, V> &tree<K, V>::operator=(const tree<K, V> &other) noexcept {
  if (this == &other) return *this;

  if (this->root != nullptr) clear();

  auto it = other.begin();
  while (it != other.end()) {
    this->add(it->first, it->second);
    it++;
  }
  // this->add(it->first, it->second);
  return *this;
}

template <typename K, typename V>
tree<K, V> &tree<K, V>::operator=(tree<K, V> &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->root = other.root;
    this->count = other.count;
    // other.clear();
    other.root = nullptr;
    other.count = 0;
  }

  return *this;
}

template <typename K, typename V>
tree<K, V>::node::node() {
  element_ = nullptr;

  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

template <typename K, typename V>
tree<K, V>::node::node(const value_type elem) {
  element_ = new value_type(elem);

  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

template <typename K, typename V>
typename tree<K, V>::iterator tree<K, V>::begin() const {
  if (!this->root) throw std::out_of_range("tree does not exist");

  return iterator(this->findMin(this->root));
}

template <typename K, typename V>
typename tree<K, V>::iterator tree<K, V>::end() const {
  if (!this->root) throw std::out_of_range("tree does not exist");
  return iterator(this->findMax(this->root));
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> tree<K, V>::add(
    const tree<K, V>::value_type &value) {
  return this->add(value.first, value.second);
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> tree<K, V>::add(const K &key,
                                                               const V &obj) {
  this->count++;
  bool flag = 1;
  node *tmp = new node({key, obj});
  if (!this->root || (this->root && !this->root->element_)) {
    if (this->root && !this->root->element_) {
      erase(this->root);
      this->count++;
    }
    this->root = tmp;
    this->root->right = new node();
    this->root->right->parent = this->root;
  } else if (!this->add(tmp, this->root))
    flag = 0;
  return {tree<K, V>::iterator(tmp), flag};
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::add(node *new_node, node *parent_node) {
  node *tmp = new_node;

  while (parent_node->left &&
         parent_node->element_->first == parent_node->left->element_->first)
    parent_node = parent_node->left;
  while (parent_node->right && parent_node->right->element_ &&
         parent_node->element_->first == parent_node->right->element_->first)
    parent_node = parent_node->right;

  if (parent_node->right && !parent_node->right->element_)
    erase(parent_node->right);

  if (!parent_node) {
    parent_node = new_node;
  } else if (new_node->element_->first == parent_node->element_->first) {
    delete tmp;
    this->count--;
    tmp = nullptr;
  } else if (new_node->element_->first < parent_node->element_->first) {
    if (parent_node->left)
      tmp = this->add(new_node, parent_node->left);
    else {
      parent_node->left = new_node;
    }
    parent_node->left->parent = parent_node;
  } else if (new_node->element_->first > parent_node->element_->first) {
    if (parent_node->right)
      tmp = this->add(new_node, parent_node->right);
    else {
      parent_node->right = new_node;
    }
    parent_node->right->parent = parent_node;
  }
  node *max = findMax(root);
  if (max->element_) {
    max->right = new node();
    max->right->parent = max;
    this->count++;
  }
  return tmp;
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::search(const K &key_search) const {
  return this->search(key_search, this->root);
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::search(const K &key_search,
                                              node *parent_node) const {
  node *tmp = nullptr;
  if (parent_node && parent_node->element_) {
    while (parent_node->left &&
           parent_node->element_->first == parent_node->left->element_->first)
      parent_node = parent_node->left;
    while (parent_node->right && parent_node->right->element_ &&
           parent_node->element_->first == parent_node->right->element_->first)
      parent_node = parent_node->right;

    if (key_search < parent_node->element_->first) {
      tmp = this->search(key_search, parent_node->left);
    } else if (key_search > parent_node->element_->first) {
      tmp = this->search(key_search, parent_node->right);
    } else if (key_search == parent_node->element_->first) {
      tmp = parent_node;
    }
  }
  return tmp;
}

template <typename K, typename V>
void tree<K, V>::erase(typename tree<K, V>::iterator pos) {
  this->erase(pos.GetNode());
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::erase(const K &key_del) {
  return this->erase(this->search(key_del));
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::erase(node *_node) {
  if (!_node) return nullptr;
  node *tmp = _node;

  auto it = tree<K, V>::iterator(_node);

  if (_node->right || _node->left || _node->parent) {
    if (_node->left) {
      it--;
      tmp = it.GetNode();
      _node->setElement(tmp->element_);
      if (tmp->parent == _node) {
        _node->left = tmp->left;
        if (_node->left) _node->left->parent = _node;
      } else
        tmp->parent->right = tmp->left;
    } else if (_node->right) {
      it++;
      tmp = it.GetNode();
      _node->setElement(tmp->element_);

      if (tmp->parent == _node) {
        _node->right = tmp->right;
        if (_node->right) _node->right->parent = _node;
      } else
        tmp->parent->left = tmp->right;
    } else if (!_node->right && !_node->left) {
      if (tmp->parent->left == _node)
        tmp->parent->left = nullptr;
      else if (tmp->parent->right == _node)
        tmp->parent->right = nullptr;
    }
  } else {
    root = nullptr;
  }
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->parent = nullptr;

  delete tmp;
  this->count--;
  return 0;
}

template <typename K, typename V>
void tree<K, V>::swap(tree<K, V> &other) {
  tree<K, V>::node *tmp = other.root;
  other.root = this->root;
  this->root = tmp;

  std::swap(this->count, other.count);
}

template <typename K, typename V>
unsigned int *tree<K, V>::setCount() {
  return &count;
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::findMax(const node *parent_node) const {
  while (parent_node && parent_node->left &&
         parent_node->left->element_->first == parent_node->element_->first) {
    parent_node = parent_node->left;
  }
  return (parent_node && parent_node->right) ? findMax(parent_node->right)
                                             : (tree<K, V>::node *)parent_node;
}

template <typename K, typename V>
typename tree<K, V>::node *tree<K, V>::findMin(const node *parent_node) const {
  while (parent_node && parent_node->right && parent_node->right->element_ &&
         parent_node->right->element_->first == parent_node->element_->first) {
    parent_node = parent_node->right;
  }
  return (parent_node && parent_node->left) ? findMin(parent_node->left)
                                            : (tree<K, V>::node *)parent_node;
}

template <typename K, typename V>
bool tree<K, V>::empty() {
  return !this->root || (this->root && !this->root->element_);
}

template <typename K, typename V>
bool tree<K, V>::contains(const K &key) {
  return search(key);
}

template <typename K, typename V>
typename tree<K, V>::size_type tree<K, V>::size() {
  return this->count;
}

template <typename K, typename V>
typename tree<K, V>::size_type tree<K, V>::max_size() {
  std::allocator<std::pair<key_type, mapped_type>> Alloc;
  return std::allocator_traits<decltype(Alloc)>::max_size(Alloc) / 5;
}

template <typename K, typename V>
void tree<K, V>::clear() {
  if (this->root != nullptr) {
    delete this->root;
    this->root = nullptr;
    this->count = 0;
  }
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> tree<K, V>::add_or_assign(
    const K &key, const V &obj) {
  bool flag = 0;
  node *tmp = this->search(key);
  if (!tmp) {
    tmp = new node({key, obj});
    if (!this->root)
      this->root = tmp;
    else
      this->add(tmp, this->root);
  } else {
    tmp->element_->second = obj;
    flag = 1;
  }
  return {iterator(tmp), flag};
}

template <typename K, typename V>
void tree<K, V>::merge(tree<K, V> &other) {
  if (!other.root || this->root == other.root) return;

  auto it = other.begin();
  while (it != other.end()) {
    this->add(it->first, it->second);
    it++;
  }
  // this->add(it->first, it->second);

  other.clear();
}
}  // namespace s21
#endif  // TREE_H
