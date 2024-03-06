#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

// +------------------------------------------------------------+
// |                                                            |
// |                         LIST TESTS                         |
// |                                                            |
// +------------------------------------------------------------+

// +---------------------LIST_CONSTRUCTORS----------------------+

TEST(list, constructors_1) {
  s21::list<double> l;
  EXPECT_EQ(0, l.size());
  EXPECT_THROW(l.front(), std::out_of_range);
  EXPECT_THROW(l.back(), std::out_of_range);
}

TEST(list, constructors_2) {
  s21::list<double> l;
  EXPECT_EQ(0, l.size());
  EXPECT_THROW(l.front(), std::out_of_range);
  EXPECT_THROW(l.back(), std::out_of_range);
}

TEST(list, constructors_3_with_parameters) {
  s21::list<double> l1(5);
  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l1.front(), 0);
}

TEST(list, constructors_4_initializer_list) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, constructors_5_copy) {
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  s21::list<int> l1(l2);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, constructors_6_move) {
  std::list<int> l1 = {-1, 0, 3, 4, 5};
  s21::list<int> l2 = {-1, 0, 3, 4, 5};
  std::list<int> l1_moved = std::move(l1);
  s21::list<int> l2_moved = std::move(l2);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
  ASSERT_EQ(l1_moved.size(), l2_moved.size());
  auto l1_moved_iter1 = l1_moved.begin();
  auto l2_moved_iter1 = l2_moved.begin();
  while (l1_moved_iter1 != l1_moved.end() && l2_moved_iter1 != l2_moved.end()) {
    EXPECT_EQ(*l1_moved_iter1, *l2_moved_iter1);
    ++l1_moved_iter1;
    ++l2_moved_iter1;
  }
}

// +-----------------------LIST_ELEMENTS------------------------+

TEST(list, elements_1_front) {
  std::list<double> l1 = {1.366, -2, 0};
  s21::list<double> l2 = {1.366, -2, 0};
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(list, elements_2_back) {
  std::list<double> l1 = {1.366, -2, 0};
  s21::list<double> l2 = {1.366, -2, 0};
  EXPECT_EQ(l1.back(), l2.back());
}

// +----------------------LIST_MODIFIERS------------------------+

TEST(list, modifiers_clear_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  l1.clear();
  l2.clear();
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l2.size(), 0);
}

TEST(list, modifiers_empty_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.empty(), l2.empty());
}

TEST(list, modifiers_size_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(list, modifiers_reverse_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  l1.reverse();
  l2.reverse();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_reverse_2) {
  s21::list<int> s21_list_1 = {1, 2, 3, 4};
  s21::list<int> s21_list_2 = {4, 3, 2, 1};
  s21_list_1.reverse();
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, modifiers_sort_1) {
  std::list<int> l1 = {1};
  s21::list<int> l2 = {1};
  l1.sort();
  l2.sort();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_sort_2) {
  std::list<int> l1 = {1, 2};
  s21::list<int> l2 = {2, 1};
  l1.sort();
  l2.sort();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_sort_3) {
  std::list<int> l1 = {-5, 4, 0, 2, 1};
  s21::list<int> l2 = {2, -5, 4, 0, 1};
  l1.sort();
  l2.sort();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_sort_4) {
  std::list<int> stl_list;
  stl_list.push_back(180);
  stl_list.push_back(-247);
  stl_list.push_back(1525);
  stl_list.push_back(-1798);
  stl_list.push_back(118);
  stl_list.push_back(-2111);
  stl_list.push_back(916);
  stl_list.push_back(1044);
  stl_list.push_back(-203);
  stl_list.push_back(198);
  stl_list.push_back(-622);
  stl_list.push_back(1160);
  stl_list.push_back(942);
  stl_list.push_back(-1599);

  s21::list<int> s21_list;
  s21_list.push_back(180);
  s21_list.push_back(-247);
  s21_list.push_back(1525);
  s21_list.push_back(-1798);
  s21_list.push_back(118);
  s21_list.push_back(-2111);
  s21_list.push_back(916);
  s21_list.push_back(1044);
  s21_list.push_back(-203);
  s21_list.push_back(198);
  s21_list.push_back(-622);
  s21_list.push_back(1160);
  s21_list.push_back(942);
  s21_list.push_back(-1599);

  stl_list.sort();
  s21_list.sort();

  auto stl_it = stl_list.begin();
  auto s21_it = s21_list.begin();

  ASSERT_EQ(stl_list.size(), stl_list.size());
  while (stl_it != stl_list.end() && s21_it != s21_list.end()) {
    EXPECT_EQ(*stl_it, *s21_it);
    ++stl_it;
    ++s21_it;
  }
}

TEST(list, modifiers_sort_5) {
  std::list<int> stl_list;
  stl_list.push_back(1127);
  stl_list.push_back(6);
  stl_list.push_back(-124);
  stl_list.push_back(1138);
  stl_list.push_back(1780);
  stl_list.push_back(1529);
  stl_list.push_back(614);
  stl_list.push_back(1412);
  stl_list.push_back(152);
  stl_list.push_back(-835);
  stl_list.push_back(-71);
  stl_list.push_back(1445);
  stl_list.push_back(-1484);
  stl_list.push_back(1974);
  stl_list.push_back(-1526);
  stl_list.push_back(-560);
  stl_list.push_back(-2000);
  stl_list.push_back(340);

  s21::list<int> s21_list;
  s21_list.push_back(1127);
  s21_list.push_back(6);
  s21_list.push_back(-124);
  s21_list.push_back(1138);
  s21_list.push_back(1780);
  s21_list.push_back(1529);
  s21_list.push_back(614);
  s21_list.push_back(1412);
  s21_list.push_back(152);
  s21_list.push_back(-835);
  s21_list.push_back(-71);
  s21_list.push_back(1445);
  s21_list.push_back(-1484);
  s21_list.push_back(1974);
  s21_list.push_back(-1526);
  s21_list.push_back(-560);
  s21_list.push_back(-2000);
  s21_list.push_back(340);

  stl_list.sort();
  s21_list.sort();

  auto stl_it = stl_list.begin();
  auto s21_it = s21_list.begin();

  ASSERT_EQ(stl_list.size(), stl_list.size());
  while (stl_it != stl_list.end() && s21_it != s21_list.end()) {
    EXPECT_EQ(*stl_it, *s21_it);
    ++stl_it;
    ++s21_it;
  }
}

TEST(list, modifiers_sort_6) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {-1, 0, 5, 6};
  a1.merge(a2);
  s21::list<int> b1 = {1, 2, 3};
  s21::list<int> b2 = {-1, 0, 5, 6};
  b1.merge(b2);
  ASSERT_EQ(a1.size(), b1.size());
  ASSERT_EQ(a2.size(), b2.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_sort_7) {
  std::list<int> a1 = {1, 2, 3, 7};
  std::list<int> a2 = {-1, 0, 5, 6};
  a1.merge(a2);
  s21::list<int> b1 = {1, 2, 3, 7};
  s21::list<int> b2 = {-1, 0, 5, 6};
  b1.merge(b2);
  ASSERT_EQ(a1.size(), b1.size());
  ASSERT_EQ(a2.size(), b2.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_swap_1) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  a1.swap(a2);
  s21::list<int> b1 = {1, 2, 3};
  s21::list<int> b2 = {3, 4, 5, 6};
  b1.swap(b2);
  ASSERT_EQ(a1.size(), b1.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_pop_back_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_back();
  l2.pop_back();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_pop_back_2) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};

  while (!l1.empty() && !l2.empty()) {
    l1.pop_back();
    l2.pop_back();
  }

  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_pop_front_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_front();
  l2.pop_front();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_push_back_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_back(11);
  l2.push_back(11);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }

  std::list<int> l3;
  s21::list<int> l4;
  l3.push_back(11);
  l4.push_back(11);
  ASSERT_EQ(l3.size(), l4.size());
  auto l3_iter1 = l3.begin();
  auto l4_iter1 = l4.begin();
  while (l3_iter1 != l3.end() && l4_iter1 != l4.end()) {
    EXPECT_EQ(*l3_iter1, *l4_iter1);
    ++l3_iter1;
    ++l4_iter1;
  }
}

TEST(list, modifiers_push_front_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_front(11);
  l2.push_front(11);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }

  std::list<int> l3;
  s21::list<int> l4;
  l3.push_front(11);
  l4.push_front(11);
  ASSERT_EQ(l3.size(), l4.size());
  auto l3_iter1 = l3.begin();
  auto l4_iter1 = l4.begin();
  while (l3_iter1 != l3.end() && l4_iter1 != l4.end()) {
    EXPECT_EQ(*l3_iter1, *l4_iter1);
    ++l3_iter1;
    ++l4_iter1;
  }
}

//-----------------------------
TEST(list, modifiers_insert_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  l1.insert(iter1, 11);
  l2.insert(iter2, 11);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_insert_2) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();
  auto iter2 = ++l2.begin();
  l1.insert(iter1, 11);
  l2.insert(iter2, 11);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_insert_3) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::list<std::string> l2 = {"hello", "world"};
  auto it1 = l1.begin();
  if (it1 != l1.end()) l1.insert(it1, "how");
  auto it2 = l2.begin();
  if (it2 != l2.end()) l2.insert(it2, "how");
  ASSERT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}

TEST(list, modifiers_insert_4) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::list<std::string> l2 = {"hello", "world"};
  auto it1 = l1.begin();
  if (it1 != l1.end()) l1.insert(it1, "how");
  auto it2 = l2.begin();
  if (it2 != l2.end()) l2.insert(it2, "how");
  ASSERT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}

TEST(list, modifiers_insert_5) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::list<std::string> l2 = {"hello", "world"};
  auto it1 = l1.end();
  l1.insert(it1, "how");
  auto it2 = l2.end();
  l2.insert(it2, "how");
  ASSERT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}
//--------------------------------------

TEST(list, modifiers_erase_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();
  auto iter2 = ++l2.begin();
  l1.erase(iter1);
  l2.erase(iter2);

  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_erase_2) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  l1.erase(iter1);
  l2.erase(iter2);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_erase_3) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = --l1.end();
  auto iter2 = --l2.end();
  l1.erase(iter1);
  l2.erase(iter2);
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_splice_1) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  auto iter1 = ++a1.begin();
  a1.splice(iter1, a2);
  s21::list<int> b1 = {1, 2, 3};
  s21::list<int> b2 = {3, 4, 5, 6};
  auto iter2 = ++b1.begin();
  b1.splice(iter2, b2);

  ASSERT_EQ(a1.size(), b1.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_splice_2) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {};
  auto iter1 = ++a1.begin();
  a1.splice(iter1, a2);
  s21::list<int> b1 = {1, 2, 3};
  s21::list<int> b2 = {};
  auto iter2 = ++b1.begin();
  b1.splice(iter2, b2);

  ASSERT_EQ(a1.size(), b1.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_splice_3) {
  std::list<int> a1 = {};
  std::list<int> a2 = {3, 4, 5, 6};
  auto iter1 = a1.begin();
  a1.splice(iter1, a2);
  s21::list<int> b1 = {};
  s21::list<int> b2 = {3, 4, 5, 6};
  auto iter2 = b1.begin();
  b1.splice(iter2, b2);

  ASSERT_EQ(a1.size(), b1.size());
  auto a1_iter1 = a1.begin();
  auto b1_iter1 = b1.begin();
  while (a1_iter1 != a1.end() && b1_iter1 != b1.end()) {
    EXPECT_EQ(*a1_iter1, *b1_iter1);
    ++a1_iter1;
    ++b1_iter1;
  }
}

TEST(list, modifiers_unique_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  l1.unique();
  l2.unique();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_unique_2) {
  std::list<int> l1 = {1, 2, 66, 1, 66};
  s21::list<int> l2 = {1, 2, 66, 1, 66};
  l1.unique();
  l2.unique();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_unique_3) {
  std::list<int> l1 = {1, 2, 2, 66, 66};
  s21::list<int> l2 = {1, 2, 2, 66, 66};
  l1.unique();
  l2.unique();
  ASSERT_EQ(l1.size(), l2.size());
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

// +----------------------LIST_ITERATORS------------------------+

TEST(list, iterators_begin_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  while (iter1 != l1.end() && iter2 != l2.end()) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(list, iterators_end_1) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.end();
  iter1--;
  auto iter2 = l2.end();
  iter2--;
  while (iter1 != l1.begin() && iter2 != l2.begin()) {
    EXPECT_EQ(*iter1, *iter2);
    --iter1;
    --iter2;
  }
}

TEST(list, iterators_operator_equals_1) {
  std::list<int> l1 = {1, 2, 3, 4, 3, 5, 2};
  s21::list<int> l2 = {1, 2, 3, 4, 3, 5, 2};

  auto l1_iter1 = l1.end();
  --l1_iter1;
  auto l1_iter2 = l1.begin();
  while (l1_iter1 != l1_iter2) {
    --l1_iter1;
    ++l1_iter2;
  }

  auto l2_iter1 = l2.end();
  --l2_iter1;
  auto l2_iter2 = l2.begin();
  while (l2_iter1 != l2_iter2) {
    --l2_iter1;
    ++l2_iter2;
  }

  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_constructor_copy_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};

  auto l1_iter1 = l1.begin();
  ++l1_iter1;
  auto l2_iter1 = l2.begin();
  ++l2_iter1;

  auto l1_iter2 = l1_iter1;
  auto l2_iter2 = l2_iter1;

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_constructor_move_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};

  auto l1_iter1 = l1.begin();
  ++l1_iter1;
  auto l2_iter1 = l2.begin();
  ++l2_iter1;

  auto l1_iter2 = std::move(l1_iter1);
  auto l2_iter2 = std::move(l2_iter1);

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_changing_list_values_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};

  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();

  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    *l1_iter1 = 0;
    *l2_iter1 = 0;
    ++l1_iter1;
    ++l2_iter1;
  }

  auto l1_iter2 = l1.begin();
  auto l2_iter2 = l2.begin();

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_next_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};

  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();

  auto l1_iter2 = std::next(l1_iter1);
  auto l2_iter2 = l2_iter1.next();

  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_prev_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto l1_iter1 = l1.begin();
  ++l1_iter1;
  ++l1_iter1;
  auto l2_iter1 = l2.begin();
  ++l2_iter1;
  ++l2_iter1;
  auto l1_iter2 = std::prev(l1_iter1);
  auto l2_iter2 = l2_iter1.prev();
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }

  while (l1_iter2 != l1.end() && l2_iter2 != l2.end()) {
    EXPECT_EQ(*l1_iter2, *l2_iter2);
    ++l1_iter2;
    ++l2_iter2;
  }
}

TEST(list, iterators_advance_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::list<int> l2 = {1, 2, 3, 4, 5};
  auto l1_iter1 = l1.begin();
  auto l2_iter1 = l2.begin();
  std::advance(l1_iter1, 3);
  l2_iter1.advance(3);
  while (l1_iter1 != l1.end() && l2_iter1 != l2.end()) {
    EXPECT_EQ(*l1_iter1, *l2_iter1);
    ++l1_iter1;
    ++l2_iter1;
  }
}

TEST(list, modifiers_insert_many_back_1) {
  s21::list<int> list;
  list.insert_many_back(1);
  list.insert_many_back(2);
  list.insert_many_back(3);
  ASSERT_EQ(list.size(), 3U);
  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(list, modifiers_insert_many_front_1) {
  s21::list<int> list;
  list.insert_many_front(1);
  list.insert_many_front(2);
  list.insert_many_front(3);
  ASSERT_EQ(list.size(), 3U);
  auto iter = list.begin();
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 1);
}

TEST(list, modifiers_insert_many_back_2) {
  s21::list<int> list;
  list.insert_many_back(1);
  list.insert_many_back(2);
  list.insert_many_back(3);
  ASSERT_EQ(list.size(), 3U);
  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(list, modifiers_insert_many_1) {
  s21::list<int> list = {1, 2, 3};
  auto iter = list.begin();
  ++iter;
  auto it = list.insert_many(iter, 4);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(list, modifiers_operator_equals_1) {
  std::list<int> a1 = {};
  std::list<int> a2 = {};
  std::list<int> a3 = {3, 4, 5, 6};
  std::list<int> a4 = {3, 4, 5, 6};

  s21::list<int> b1{};
  s21::list<int> b2{};
  s21::list<int> b3{3, 4, 5, 6};
  std::list<int> b4{3, 4, 5, 6};
  EXPECT_EQ(a1 == a2, b1 == b2);
  EXPECT_EQ(a1 == a3, b1 == b3);

  EXPECT_EQ(a1 != a2, b1 != b2);
  EXPECT_EQ(a1 != a3, b1 != b3);
}

TEST(list, constructor_size) {
  s21::list<int> list(10);
  std::list<int> list2(10);
  EXPECT_EQ(list.size(), list2.size());
}

TEST(list, constructor_initializer_list) {
  s21::list<int> list1({1, 2, 3, 4, 8});
  std::list<int> list2({1, 2, 3, 4, 8});
  EXPECT_EQ(list1.size(), list2.size());
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list1.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, constructor_copy) {
  s21::list<int> list1({1, 2, 3, 4, 8});
  s21::list<int> list2(list1);
  EXPECT_EQ(list1.size(), list2.size());
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list1.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, constructor_move) {
  s21::list<int> list1({1, 2, 3, 4, 8});
  s21::list<int> list2({1, 2, 3, 4, 8});
  s21::list<int> list3(std::move(list1));
  EXPECT_EQ(list3.size(), 5);
  EXPECT_EQ(list1.size(), 0);
  auto it3 = list1.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list1.size(); ++i) {
    EXPECT_EQ(*it3, *it2);
    ++it3;
    ++it2;
  }
}

TEST(list, operator_equal) {
  s21::list<double> list1({-0.75, 7.12, 115.0, -18, 01});
  s21::list<double> list2({-0.75, 7.12, 115.0, -18, 01});
  s21::list<double> list3;
  list3 = std::move(list1);
  EXPECT_EQ(list3.size(), list2.size());
  EXPECT_EQ(list1.size(), 0);
  auto it3 = list1.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list1.size(); ++i) {
    EXPECT_EQ(*it3, *it2);
    ++it3;
    ++it2;
  }
}

TEST(list, clear) {
  s21::list<std::string> list{"hi", "hello",     "bye",
                              "ok", "good luck", "shool21"};
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

TEST(list, clear_empty) {
  s21::list<std::string> list;
  list.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.empty(), true);
}

TEST(list, erase) {
  s21::list<float> list{4.22, 1.91, 7.4};
  list.erase(list.begin());
  const float f = 1.91;
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), f);
}

TEST(list, push_back) {
  s21::list<float> list{4.22, 1.91, 7.4};
  list.push_back(3.14);
  const float f = 3.14;
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.back(), f);
}

TEST(list, push_back_2) {
  s21::list<float> list;
  list.push_back(3.14);
  const float f = 3.14;
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.back(), f);
}

TEST(list, push_front) {
  s21::list<float> list{4.22, 1.91, 7.4};
  list.push_front(3.14);
  const float f = 3.14;
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), f);
}

TEST(list, push_front_2) {
  s21::list<float> list;
  list.push_front(3.14);
  const float f = 3.14;
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), f);
}

TEST(list, insert) {
  s21::list<int> list{1, 2, 3};
  auto it = ++list.begin();
  list.insert(it, 555);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(*(--it), 555);
}

TEST(list, insert_end) {
  s21::list<int> list{1, 2, 3};
  auto it = list.end();
  list.insert(it, 555);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(*(--it), 555);
}

TEST(list, front) {
  s21::list<int> list{1, 2, 3};
  EXPECT_EQ(list.front(), 1);
}

TEST(list, back) {
  s21::list<int> list{1, 2, 3};
  EXPECT_EQ(list.back(), 3);
}

TEST(list, pop_front) {
  s21::list<double> list{84.14, 52.99, -19.3};
  list.pop_front();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 52.99);
}

TEST(list, pop_back) {
  s21::list<std::string> list{"hi", "hello", "bye"};
  list.pop_back();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.back(), "hello");
}

TEST(list, swap) {
  s21::list<double> list{84.14, 52.99, -19.3};
  s21::list<double> list2{84.14, 52.99, -19.3};
  s21::list<double> l;
  l.swap(list);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(l.size(), list2.size());
  auto it = l.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, swap_2) {
  s21::list<double> list{55., 0.11};
  s21::list<double> list2{84.14, 52.99, -19.3};
  s21::list<double> list3{84.14, 52.99, -19.3};
  list.swap(list2);
  EXPECT_EQ(list.size(), list3.size());
  EXPECT_EQ(list2.size(), 2);
  auto it = list.begin();
  auto it3 = list3.begin();
  for (std::size_t i = 0; i < list.size(); ++i) {
    EXPECT_EQ(*it, *it3);
    ++it;
    ++it3;
  }
}

TEST(list, reverse) {
  s21::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> list2{1, 2, 3, 4, 5};
  list.reverse();
  list2.reverse();
  auto it = list.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, merge) {
  s21::list<int> list{1, 21, 31};
  s21::list<int> list2{-9, 8, 45};
  s21::list<int> list3{-9, 1, 8, 21, 31, 45};
  list.merge(list2);
  EXPECT_EQ(list.size(), list3.size());
  auto it = list.begin();
  auto it3 = list3.begin();
  for (std::size_t i = 0; i < list.size(); ++i) {
    EXPECT_EQ(*it, *it3);
    ++it;
    ++it3;
  }
}

TEST(list, merge_itself) {
  s21::list<int> list{1, 2, 3};
  s21::list<int> list2{1, 2, 3};
  list.merge(list);
  EXPECT_EQ(list.size(), list2.size());
  auto it = list.begin();
  auto it2 = list2.begin();
  for (std::size_t i = 0; i < list.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, splice) {
  s21::list<int> l1{1, 1, 1, 1};
  s21::list<int> l2{55, 56};
  s21::list<int> l3{1, 55, 56, 1, 1, 1};
  l1.splice(++l1.begin(), l2);
  EXPECT_EQ(l1.size(), l3.size());
  EXPECT_EQ(l2.size(), 0);
  auto it = l1.begin();
  auto it3 = l3.begin();
  for (std::size_t i = 0; i < l1.size(); ++i) {
    EXPECT_EQ(*it, *it3);
    ++it;
    ++it3;
  }
}

TEST(list, unique) {
  s21::list<int> l{1, 1, 2, 3, 2, 5, 5, 5, 9, 9};
  s21::list<int> l2{1, 1, 2, 3, 2, 5, 5, 5, 9, 9};
  l.unique();
  l2.unique();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, unique_2) {
  s21::list<int> l{1, 1, 1, 1, 1, 1};
  s21::list<int> l2{1, 1, 1, 1, 1, 1};
  l.unique();
  l2.unique();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, unique_3) {
  s21::list<int> l{1, 1, 1, 1, 5, 5, 5, 5};
  s21::list<int> l2{1, 1, 1, 1, 5, 5, 5, 5};
  l.unique();
  l2.unique();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, sort) {
  s21::list<int> l{65, -1, 5, 182, 0, -71};
  std::list<int> l2{65, -1, 5, 182, 0, -71};
  l.sort();
  l2.sort();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, sort_2) {
  s21::list<std::string> l{"hi", "hello", "bye", "ok", "school", "good luck"};
  std::list<std::string> l2{"hi", "hello", "bye", "ok", "school", "good luck"};
  l.sort();
  l2.sort();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, sort_3) {
  s21::list<double> l;
  std::list<double> l2;
  l.sort();
  l2.sort();
  EXPECT_EQ(l.size(), l2.size());
  auto it = l.begin();
  auto it2 = l2.begin();
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it, *it2);
    ++it;
    ++it2;
  }
}

TEST(list, insert_many) {
  s21::list<int> l{1, 2, 3};
  s21::list<int> l2{1, 2, 999, 999, 3};
  auto it = l.begin();
  ++it;
  ++it;
  l.insert_many(it, 999, 999);
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, insert_many_2) {
  s21::list<int> l;
  s21::list<int> l2{999, 999};
  auto it = l.begin();
  l.insert_many(it, 999, 999);
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, insert_many_back) {
  s21::list<std::string> l{"hi", "hello", "bye"};
  s21::list<std::string> l2{"hi", "hello", "bye", "ok", "school", "good luck"};
  l.insert_many_back("ok", "school", "good luck");
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, insert_many_back_2) {
  s21::list<std::string> l;
  s21::list<std::string> l2{"ok", "school", "good luck"};
  l.insert_many_back("ok", "school", "good luck");
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, insert_many_front) {
  s21::list<std::string> l{"hi", "hello", "bye"};
  s21::list<std::string> l2{"ok", "school", "good luck", "hi", "hello", "bye"};
  l.insert_many_front("ok", "school", "good luck");
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(list, insert_many_front_2) {
  s21::list<std::string> l;
  s21::list<std::string> l2{"good luck", "school", "ok"};
  l.insert_many_front("good luck", "school", "ok");
  auto it1 = l.begin();
  auto it2 = l2.begin();
  EXPECT_EQ(l.size(), l2.size());
  for (std::size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}