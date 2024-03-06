#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

// CONTENTS

// - MEMBER_TYPE
// - CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS
// - ELEMENT_ACCESS
// - CAPACITY
// - MODIFIERS
// - NODE_STRUCT

namespace s21 {
template <typename T>
class queue {
 private:
  struct _node;

 public:
  // MEMBER_TYPE
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using pointer = struct _node*;

 private:
  pointer _first;
  pointer _last;
  size_type _size;

  // CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS

 public:
  queue() : _first(nullptr), _last(nullptr), _size(0) {}

  queue(std::initializer_list<value_type> const& items) : queue() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  queue(const queue& l) : queue() {
    _node* cur = l._first;
    while (cur != nullptr) {
      push(cur->_value);
      cur = cur->_prev;
    }
  }

  queue(queue&& l) : queue() { *this = std::move(l); }

  queue& operator=(queue&& l) {
    clear();
    _first = l._first;
    _last = l._last;
    _size = l._size;
    l._first = nullptr;
    l._last = nullptr;
    l._size = 0;
    return *this;
  }

  queue& operator=(const queue& l) {
    clear();
    _node* cur = l._first;
    while (cur != nullptr) {
      push(cur->_value);
      cur = cur->_prev;
    }
    return *this;
  }

  ~queue() { clear(); }

  // ELEMENT_ACCESS

  const_reference front() {
    if (size() == 0) {
      throw std::out_of_range("Queue is empty");
    }
    return _first->_value;
  }

  const_reference back() {
    if (size() == 0) {
      throw std::out_of_range("Queue is empty");
    }
    return _last->_value;
  }

  // MODIFIERS

  void clear() {
    while (empty() == false) {
      pop();
    }
  }

  void pop() {
    if (empty() == false) {
      _size--;
      pointer temp = _first;
      _first = _first->_prev;
      delete temp;
      if (_first == nullptr) {
        _last = nullptr;
      }
    }
  }

  void push(value_type value) {
    if (empty() == true) {
      _first = new _node(value);
      _last = _first;
    } else {
      _last->_prev = new _node(value);
      _last = _last->_prev;
    }
    _size++;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(args), ...);
  }

  void swap(queue& other) {
    queue temp = other;
    other = *this;
    *this = temp;
  }

  // CAPACITY

  bool empty() { return _first == nullptr ? true : false; }

  size_type size() { return _size; }

 private:
  struct _node {
    value_type _value;
    _node* _prev;

    _node() : _prev(nullptr), _value(value_type()) {}

    _node(value_type _value, _node* _prev_pointer = nullptr) {
      this->_prev = _prev_pointer;
      this->_value = _value;
    }

    _node& operator=(const _node& other) {
      this->_value = other._value;
      this->_prev = other._prev;
      return *this;
    }

    bool operator==(const _node& other) { return _value == other._value; }

    bool operator!=(const _node& other) { return !(*this == other); }

    void print_node() {
      std::cout << "prev:  ";
      if (_prev != nullptr) {
        std::cout << _prev->_value << "\n";
      } else {
        std::cout << "nullptr\n";
      }
      std::cout << "value: " << _value << "\nnext:  ";
      std::cout << "\n";
    }

    ~_node() {}
  };  // struct _node

};  // class queue
}  // namespace s21

#endif  // S21_QUEUE_H_
