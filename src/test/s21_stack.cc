#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

TEST(stack, constructors_1) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, constructors_initializer_list_1) {
  s21::stack<unsigned int> s1{1, 2, 3, 4};
  ASSERT_EQ(s1.size(), 4u);
  ASSERT_EQ(s1.top(), 4u);
  s21::stack<std::string> s2{"morning", "village", "people"};
  ASSERT_EQ(s2.size(), 3u);
  ASSERT_EQ(s2.top(), "people");
}

TEST(stack, constructors_initializer_list_2) {
  s21::stack<std::pair<std::string, int>> s21_s1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::stack<std::pair<std::string, int>> std_s2;
  std_s2.push({"one", 1});
  std_s2.push({"two", 2});
  std_s2.push({"three", 3});
  EXPECT_EQ(s21_s1.empty(), std_s2.empty());
  EXPECT_EQ(s21_s1.size(), std_s2.size());
  while (!s21_s1.empty()) {
    EXPECT_EQ(s21_s1.top(), std_s2.top());
    s21_s1.pop();
    std_s2.pop();
  }
}

TEST(stack, constructors_initializer_list_3) {
  s21::stack<int> s21_s{};
  ASSERT_TRUE(s21_s.empty());
  ASSERT_EQ(s21_s.size(), 0u);
}

TEST(stack, constructors_2) {
  s21::stack<std::pair<std::string, int>> s21_s;
  std::stack<std::pair<std::string, int>> std_s;
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
  s21_s.push({"one", 1});
  std_s.push({"one", 1});
  EXPECT_FALSE(s21_s.empty());
  EXPECT_FALSE(std_s.empty());
  s21_s.pop();
  std_s.pop();
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
}

TEST(stack, modifiers_size_1) {
  s21::stack<std::pair<std::string, unsigned int>> s21_s;
  std::stack<std::pair<std::string, unsigned int>> std_s;
  EXPECT_EQ(s21_s.size(), 0u);
  EXPECT_EQ(std_s.size(), 0u);
  s21_s.push({"one", 1u});
  std_s.push({"one", 1u});
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.push({"two", 2u});
  std_s.push({"two", 2u});
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.push({"three", 3u});
  std_s.push({"three", 3u});
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.size(), std_s.size());
}

TEST(stack, modifiers_push_pop_1) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 20; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  while (!std_stack.empty()) {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(stack, modifiers_push_pop_2) {
  s21::stack<std::string> s21_s;
  std::stack<std::string> std_s;
  s21_s.push("one");
  std_s.push("one");
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.push("two");
  std_s.push("two");
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
}

TEST(stack, modifiers_push_pop_3) {
  s21::stack<std::pair<std::string, int>> s21_s;
  std::stack<std::pair<std::string, int>> std_s;
  s21_s.push({"one", 1});
  std_s.push({"one", 1});
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.push({"two", 2});
  std_s.push({"two", 2});
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
}

TEST(stack, contructors_copy_1) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 20; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.top(), s21_copy.top());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(stack, contructors_copy_2) {
  s21::stack<std::string> s21_stack_1;
  std::stack<std::string> std_stack_1;
  s21_stack_1.push("one");
  std_stack_1.push("one");
  s21_stack_1.push("two");
  std_stack_1.push("two");
  s21::stack<std::string> s21_stack_2(s21_stack_1);
  std::stack<std::string> std_stack_2(std_stack_1);
  while (!s21_stack_1.empty() && !s21_stack_2.empty()) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(std_stack_1.top(), std_stack_2.top());
    s21_stack_1.pop();
    s21_stack_2.pop();
    std_stack_1.pop();
    std_stack_2.pop();
  }
}

TEST(stack, contructors_copy_3) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::stack<std::pair<std::string, int>> s2(s1);
  std::stack<std::pair<std::string, int>> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(stack, contructors_copy_4) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(stack, contructors_move_1) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;
  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});
  s21::stack<std::pair<std::string, int>> s2(std::move(s1));
  std::stack<std::pair<std::string, int>> s2_stl(std::move(s1_stl));
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
}

TEST(stack, contructors_move_2) {
  s21::stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::stack<std::string> s2(std::move(s1));
  std::stack<std::string> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s2.top() == "two");

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
  EXPECT_TRUE(s2_stl.top() == "two");
}

TEST(stack, modifiers_copy_1) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;
  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }
  s21::stack<int> my_copy_stack;
  std::stack<int> stl_copy_stack;
  my_copy_stack = my_stack;
  stl_copy_stack = stl_stack;
  EXPECT_EQ(my_copy_stack.size(), stl_copy_stack.size());
  while (!my_copy_stack.empty()) {
    EXPECT_EQ(my_copy_stack.top(), stl_copy_stack.top());
    my_copy_stack.pop();
    stl_copy_stack.pop();
  }
  EXPECT_TRUE(my_copy_stack.empty());
  EXPECT_TRUE(stl_copy_stack.empty());
}

TEST(stack, modifiers_copy_2) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});
  s1.push({"three", 3});
  s1_stl.push({"three", 3});

  s21::stack<std::pair<std::string, int>> s2;
  std::stack<std::pair<std::string, int>> s2_stl;

  s2.push({"four", 4});
  s2_stl.push({"four", 4});

  s2 = s1;
  s2_stl = s1_stl;

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(stack, modifiers_move_1) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;
  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }
  s21::stack<int> my_move_stack;
  std::stack<int> stl_move_stack;
  my_move_stack = std::move(my_stack);
  stl_move_stack = std::move(stl_stack);
  EXPECT_EQ(my_move_stack.size(), stl_move_stack.size());
  EXPECT_EQ(my_stack.size(), stl_stack.size());
  while (!my_move_stack.empty()) {
    EXPECT_EQ(my_move_stack.top(), stl_move_stack.top());
    my_move_stack.pop();
    stl_move_stack.pop();
  }
  EXPECT_TRUE(my_stack.empty());
  EXPECT_TRUE(stl_stack.empty());
}

TEST(stack, modifiers_move_2) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;
  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});
  s1.push({"three", 3});
  s1_stl.push({"three", 3});
  s21::stack<std::pair<std::string, int>> s2;
  std::stack<std::pair<std::string, int>> s2_stl;
  s2.push({"four", 4});
  s2_stl.push({"four", 4});
  s2 = std::move(s1);
  s2_stl = std::move(s1_stl);
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 3);
  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 3);
}

TEST(stack, modifiers_copy_3) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy;
  s21::stack<int> s21_copy;
  std_copy = std_stack;
  s21_copy = s21_stack;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(stack, modifiers_insert_many_front_1) {
  s21::stack<unsigned int> my_stack;
  my_stack.insert_many_front(1);
  my_stack.insert_many_front(2);
  my_stack.insert_many_front(3);

  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 3u);

  my_stack.pop();
  EXPECT_EQ(my_stack.size(), 2u);
  EXPECT_EQ(my_stack.top(), 2u);

  my_stack.insert_many_front(4);
  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 4u);
}

TEST(stack, constructor_default) {
  s21::stack<double> stack;
  EXPECT_EQ(stack.size(), 0);
}

TEST(stack, constructor_initializer_list) {
  s21::stack<int> stack1({1, 2, 3, 4, 8});
  std::stack<int> stack2({1, 2, 3, 4, 8});
  EXPECT_EQ(stack1.size(), stack2.size());
  for (std::size_t i = 0; i < stack1.size(); ++i) {
    EXPECT_EQ(stack1.top(), stack2.top());
    stack1.pop();
    stack2.pop();
  }
}

TEST(stack, constructor_copy) {
  s21::stack<int> stack1({1, 2, 3, 4, 8});
  s21::stack<int> stack2(stack1);
  EXPECT_EQ(stack1.size(), stack2.size());
  for (std::size_t i = 0; i < stack1.size(); ++i) {
    EXPECT_EQ(stack1.top(), stack2.top());
    stack1.pop();
    stack2.pop();
  }
}

TEST(stack, constructor_move) {
  s21::stack<int> stack1({1, 2, 3, 4, 8});
  s21::stack<int> stack2({1, 2, 3, 4, 8});
  s21::stack<int> stack3(std::move(stack1));
  EXPECT_EQ(stack3.size(), 5);
  EXPECT_EQ(stack1.size(), 0);
  for (std::size_t i = 0; i < stack3.size(); ++i) {
    EXPECT_EQ(stack3.top(), stack2.top());
    stack3.pop();
    stack2.pop();
  }
}

TEST(stack, operator_equal) {
  s21::stack<double> stack1({-0.75, 7.12, 115.0, -18, 01});
  s21::stack<double> stack2({-0.75, 7.12, 115.0, -18, 01});
  s21::stack<double> stack3;
  stack3 = std::move(stack1);
  EXPECT_EQ(stack3.size(), stack2.size());
  EXPECT_EQ(stack1.size(), 0);
  for (std::size_t i = 0; i < stack3.size(); ++i) {
    EXPECT_EQ(stack3.top(), stack2.top());
    stack3.pop();
    stack2.pop();
  }
}

TEST(stack, top) {
  s21::stack<std::string> stack{"hi", "bye", "ok", "good luck", "shool21"};
  EXPECT_EQ(stack.top(), "shool21");
}

TEST(stack, empty) {
  s21::stack<float> stack;
  EXPECT_EQ(stack.size(), 0);
}

TEST(stack, not_empty) {
  s21::stack<float> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.size(), 5);
}

TEST(stack, size) {
  s21::stack<int> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.size(), 5);
}

TEST(stack, push) {
  s21::stack<std::string> stack({"hi", "hello"});
  EXPECT_EQ(stack.top(), "hello");
  stack.push("school");
  EXPECT_EQ(stack.top(), "school");
}

TEST(stack, pop) {
  s21::stack<int> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.top(), 8);
  stack.pop();
  EXPECT_EQ(stack.top(), 4);
}

TEST(stack, swap) {
  s21::stack<double> stack1({-0.75, 7.12, 115.0, -18, 01});
  s21::stack<double> stack2({1, 2});
  s21::stack<double> stack3({-0.75, 7.12, 115.0, -18, 01});
  stack1.swap(stack2);
  EXPECT_EQ(stack2.size(), stack3.size());
  for (std::size_t i = 0; i < stack3.size(); ++i) {
    EXPECT_EQ(stack3.top(), stack2.top());
    stack3.pop();
    stack2.pop();
  }
}

TEST(stack, insert_many_back) {
  s21::stack<int> stack;
  stack.insert_many_front(1, 2, 3);
  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(stack.size(), 3);
}
