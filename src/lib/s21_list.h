#ifndef S21_LIST_H_
#define S21_LIST_H_

// CONTENTS

// - MEMBER_TYPE
// - CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS
// - ELEMENT_ACCESS
// - CAPACITY
// - MODIFIERS
// - ITERATORS
// - NODE_STRUCT

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

 private:
  struct _node;

 public:
  // MEMBER_TYPE
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using pointer = struct _node*;

 private:
  pointer _first;
  pointer _last;
  size_type _size;

  // CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS

 public:
  list() : _first(nullptr), _last(nullptr), _size(0) {
    _last = new _node({}, nullptr, nullptr);
    _first = _last;
  }

  list(size_type n) : list() {
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push_back(*it);
    }
  }

  list(const list& l) : list() {
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  }

  list(list&& l) : list() { *this = std::move(l); }

  list& operator=(list&& l) {
    clear();
    delete _last;
    _first = l._first;
    _last = l._last;
    _size = l._size;
    l._first = nullptr;
    l._last = nullptr;
    l._size = 0;
    return *this;
  }

  list& operator=(const list& l) {
    clear();
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
    return *this;
  }

  bool operator==(const list& other) {
    if (_size != other._size) {
      return false;
    }
    bool res = true;
    auto this_it = begin();
    auto other_it = other.begin();

    while (this_it != end() && other_it != other.end() && res == true) {
      if (*this_it != *other_it) {
        res = false;
      }
      this_it++;
      other_it++;
    }

    return res;
  }

  bool operator!=(const list& other) { return !((*this) == other); }

  ~list() {
    clear();
    delete _last;
  }

  // ELEMENT_ACCESS

  const_reference front() {
    if (size() == 0) {
      throw std::out_of_range("List is empty");
    }
    return _first->_value;
  }

  const_reference back() {
    if (size() == 0) {
      throw std::out_of_range("List is empty");
    }
    return _last->_prev->_value;
  }

  // MODIFIERS

  void clear() {
    while (empty() == false) {
      pop_front();
    }
  }

  void pop_front() {
    if (empty() == false) {
      _size--;
      if (empty() == true) {
        delete _first;
        _first = nullptr;
        _last->_prev = nullptr;
      } else {
        _first = _first->_next;
        delete _first->_prev;
        _first->_prev = nullptr;
      }
    }
  }

  void pop_back() {
    if (empty() == false) {
      _size--;
      if (empty() == true) {
        delete _first;
        _first = nullptr;
        _last->_prev = nullptr;
      } else {
        pointer to_remove = _last->_prev;
        to_remove->_prev->_next = _last;
        _last->_prev = to_remove->_prev;
        delete to_remove;
      }
    }
  }

  void push_front(value_type value) {
    if (empty() == true) {
      _first = new _node(value, nullptr, _last);
      _last->_prev = _first;
    } else {
      _first->_prev = new _node(value, nullptr, _first);
      _first = _first->_prev;
    }
    _size++;
  }

  void push_back(value_type value) {
    if (empty() == true) {
      _first = new _node(value, nullptr, _last);
      _last->_prev = _first;
    } else {
      pointer lastValid = _last->_prev;
      lastValid->_next = new _node(value, lastValid, _last);
      _last->_prev = lastValid->_next;
    }
    _size++;
  }

  void erase(iterator pos) {
    pointer _tmp = pos._current;
    if (_tmp == _first) {
      pop_front();
    } else if (_tmp == _last->_prev) {
      pop_back();
    } else {
      --_size;
      _tmp->_prev->_next = _tmp->_next;
      _tmp->_next->_prev = _tmp->_prev;
      delete _tmp;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    iterator new_it = iterator();
    if (pos._current->_prev == nullptr) {
      push_front(value);
      new_it = begin();
    } else if (pos == end()) {
      push_back(value);
      new_it = end();
      --new_it;
    } else {
      pointer new_node = new _node(value, pos._current->_prev, pos._current);
      pos._current->_prev->_next = new_node;
      pos._current->_prev = new_node;
      new_it = iterator(new_node);
      _size++;
    }
    return new_it;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    list<value_type> temp = list();
    (temp.push_front(args), ...);
    iterator new_pos = iterator();
    new_pos._current = pos._current;
    for (auto it = temp.begin(); it != temp.end(); ++it) {
      new_pos = insert(new_pos, *it);
    }
    return new_pos;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(args), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    list<value_type> temp = list();
    (temp.push_back(args), ...);
    splice(begin(), temp);
  }

  void swap(list& other) {
    list temp = other;
    other = *this;
    *this = temp;
  }

  void merge(list& other) {
    if (this != &other) {
      list<value_type> temp = list();
      auto it_this = begin();
      auto it_other = other.begin();
      while (it_this != end() && it_other != other.end()) {
        if (*it_this < *it_other) {
          temp.push_back(*it_this);
          it_this++;
        } else {
          temp.push_back(*it_other);
          it_other++;
        }
      }
      while (it_this != end()) {
        temp.push_back(*it_this);
        it_this++;
      }
      while (it_other != other.end()) {
        temp.push_back(*it_other);
        it_other++;
      }
      swap(temp);
      other.clear();
    }
  }

  void splice(iterator pos, list& other) {
    other.reverse();
    for (auto it = other.begin(); it != other.end(); ++it) {
      pos = insert(pos, *it);
    }
    other.clear();
  }

  void reverse() {
    if (size() > 1) {
      auto forward = begin();
      auto backward = --end();
      while (forward != backward && forward != backward.next()) {
        std::swap(*forward, *backward);
        ++forward;
        --backward;
      }
    }
  }

  void unique() {
    auto it = begin();
    auto it_next = it;
    ++it_next;
    while (it_next != end()) {
      if (*it == *it_next) {
        auto temp = it_next;
        temp++;
        erase(it_next);
        it_next = temp;
      } else {
        ++it_next;
        ++it;
      }
    }
  }

  void sort() {
    if (_size > 1) {
      iterator begin = (*this).begin();
      iterator middle = (*this).begin();
      iterator end = --(*this).end();
      for (int i = 0; i < ((int)_size - 1) / 2; i++) {
        middle++;
      }
      iterator middle2 = middle;
      middle2++;
      list<value_type> left = split(begin, middle);
      left.sort();
      list<value_type> right = split(middle2, end);
      right.sort();
      *this = merge_sort(left, right);
    }
  }

  // CAPACITY

  bool empty() { return size() == 0 ? true : false; }

  size_type size() { return _size; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(list<value_type>);
  }

  // ITERATORS

  iterator begin() { return iterator(_first); }

  iterator end() { return iterator(_last); }

  const_iterator begin() const { return const_iterator(_first); }

  const_iterator end() const { return iterator(_last); }

 private:
  list<value_type> merge_sort(list<value_type>& left, list<value_type>& right) {
    list<value_type> result;
    while (left.empty() == false && right.empty() == false) {
      if (left.front() < right.front()) {
        result.push_back(left.front());
        left.pop_front();
      } else {
        result.push_back(right.front());
        right.pop_front();
      }
    }
    while (left.empty() == false) {
      result.push_back(left.front());
      left.pop_front();
    }
    while (right.empty() == false) {
      result.push_back(right.front());
      right.pop_front();
    }
    return result;
  }

  list<value_type> split(iterator from, iterator to) {
    list<value_type> result = list();
    while (from != to && from != end()) {
      result.push_back(*from);
      ++from;
    }
    if (from != end()) {
      result.push_back(*from);
    }
    return result;
  }

 public:
  class ListIterator {
    friend class list;
    friend class ListConstIterator;

   private:
    pointer _current;

   public:
    ListIterator() : _current(nullptr) {}

    ListIterator(pointer node) : ListIterator() {
      if (node != nullptr) {
        _current = node;
      }
    }

    ListIterator(const iterator& it) : ListIterator() {
      _current = it._current;
    }

    ListIterator(iterator&& it) : ListIterator() {
      _current = it._current;
      it._current = nullptr;
    }

    iterator& operator=(const iterator& other) {
      _current = other._current;
      return *this;
    }

    iterator& operator++() {
      if (_current->_next == nullptr) {
        throw std::out_of_range(
            "Attempt to increment a past-the-end iterator.");
      }
      _current = _current->_next;
      return *this;
    }

    iterator operator++(int) {
      iterator old(*this);
      ++(*this);
      return old;
    }

    iterator& operator--() {
      if (_current->_prev == nullptr) {
        throw std::out_of_range(
            "Attempt to decrement a before-the-beginning iterator.");
      }
      _current = _current->_prev;
      return *this;
    }

    iterator operator--(int) {
      iterator old(*this);
      --(*this);
      return old;
    }

    reference operator*() {
      if (_current == nullptr) {
        throw std::out_of_range("Attempt to dereference a nullptr.");
      }
      return _current->_value;
    }

    bool operator==(const iterator& other) {
      return _current == other._current;
    }

    bool operator!=(const iterator& other) {
      return ((*this) == other) ? false : true;
    }

    iterator next() {
      iterator tmp = *this;
      ++tmp;
      return tmp;
    }

    iterator prev() {
      iterator tmp = *this;
      --tmp;
      return tmp;
    }

    void advance(int n) {
      if (n > 0) {
        for (int i = 0; i < n; ++i) {
          ++(*this);
        }
      } else {
        for (int i = 0; i > n; --i) {
          --(*this);
        }
      }
    }

  };  // ListIterator

  class ListConstIterator {
    friend class list;

   private:
    pointer _current;

   public:
    ListConstIterator() : _current(nullptr) {}

    ListConstIterator(pointer node) : ListConstIterator() {
      if (node != nullptr) {
        _current = node;
      }
    }

    ListConstIterator(const const_iterator& it) : ListConstIterator() {
      _current = it._current;
    }
    ListConstIterator(const iterator& it) : ListConstIterator() {
      _current = it._current;
    }

    ListConstIterator(const_iterator&& it) : ListConstIterator() {
      _current = it._current;
      it._current = nullptr;
    }

    ListConstIterator(iterator&& it) : ListConstIterator() {
      _current = it._current;
      it._current = nullptr;
    }

    const_iterator& operator=(const const_iterator& other) {
      _current = other._current;
      return *this;
    }

    const_iterator& operator=(const const_iterator&& other) {
      _current = other._current;
      other._current = nullptr;
      return *this;
    }

    const_iterator& operator++() {
      if (_current->_next == nullptr) {
        throw std::out_of_range(
            "Attempt to increment a past-the-end iterator.");
      }
      _current = _current->_next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old(*this);
      ++(*this);
      return old;
    }

    const_iterator& operator--() {
      if (_current->_prev == nullptr) {
        throw std::out_of_range(
            "Attempt to decrement a before-the-beginning iterator.");
      }
      _current = _current->_prev;

      return *this;
    }

    const_iterator operator--(int) {
      const_iterator old(*this);
      --(*this);
      return old;
    }

    bool operator==(const const_iterator& other) {
      return _current == other._current;
    }

    bool operator!=(const const_iterator& other) {
      return ((*this) == other) ? false : true;
    }

    const_reference operator*() {
      if (_current == nullptr) {
        throw std::out_of_range("Attempt to dereference a nullptr.");
      }
      return _current->_value;
    }

    const_iterator next() {
      const_iterator tmp = *this;
      ++tmp;
      return tmp;
    }

    const_iterator prev() {
      const_iterator tmp = *this;
      --tmp;
      return tmp;
    }

    void advance(int n) {
      if (n > 0) {
        for (int i = 0; i < n; ++i) {
          ++(*this);
        }
      } else {
        for (int i = 0; i > n; --i) {
          --(*this);
        }
      }
    }

  };  // ListConstIterator

  // NODE_STRUCT

 private:
  struct _node {
    value_type _value;
    _node* _next;
    _node* _prev;

    _node() : _value(value_type()), _prev(nullptr), _next(nullptr) {}

    _node(value_type _value, _node* _prev_pointer = nullptr,
          _node* _next_pointer = nullptr) {
      this->_next = _next_pointer;
      this->_prev = _prev_pointer;
      this->_value = _value;
    }

    _node& operator=(const _node& other) {
      this->_value = other._value;
      this->_next = other._next;
      this->_prev = other._prev;
      return *this;
    }

    bool operator==(const _node& other) { return _value == other._value; }

    bool operator!=(const _node& other) { return !(*this == other); }

    ~_node() {}
  };  // struct _node

};  // class list
}  // namespace s21

#endif  // S21_LIST_H_
