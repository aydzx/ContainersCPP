#ifndef S21_STACK_H_
#define S21_STACK_H_

// CONTENTS

// - MEMBER_TYPE
// - CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS
// - ELEMENT_ACCESS
// - CAPACITY
// - MODIFIERS
// - NODE_STRUCT

namespace s21 {
template <typename T>
class stack {
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
  pointer _top;
  size_type _size;

  // CONSTRUCTORS_DESTRUCTORS_AND_OPERATORS

 public:
  stack() : _top(nullptr), _size(0) {}

  stack(std::initializer_list<value_type> const& items) : stack() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  stack(const stack& s) : stack() { *this = s; }

  stack(stack&& s) : stack() { *this = std::move(s); }

  stack& operator=(stack&& s) {
    clear();
    _top = s._top;
    _size = s._size;
    s._top = nullptr;
    s._size = 0;
    return *this;
  }

  stack& operator=(const stack& s) {
    clear();
    _node* cur = s._top;
    stack temp;
    while (cur != nullptr) {
      temp.push(cur->_value);
      cur = cur->_prev;
    }
    while (temp.empty() == false) {
      push(temp.top());
      temp.pop();
    }
    return *this;
  }

  ~stack() { clear(); }

  // ELEMENT_ACCESS

  const_reference top() {
    if (size() == 0) {
      throw std::out_of_range("Stack is empty");
    }
    return _top->_value;
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
      pointer temp = _top;
      _top = _top->_prev;
      delete temp;
    }
  }

  void push(value_type value) {
    if (empty() == true) {
      _top = new _node(value);
    } else {
      _top = new _node(value, _top);
    }
    _size++;
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    stack<value_type> temp = stack();
    (temp.push(args), ...);
    while (temp.empty() == false) {
      push(temp.top());
      temp.pop();
    }
  }

  void swap(stack& other) {
    stack temp = other;
    other = *this;
    *this = temp;
  }

  // CAPACITY

  bool empty() { return _top == nullptr ? true : false; }

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

};  // class stack
}  // namespace s21

#endif  // S21_STACK_H_
