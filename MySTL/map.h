#ifndef MYTINYSTL_MAP_H_
#define MYTINYSTL_MAP_H_

// 这个头文件包含了两个模板类 map 和 multimap
// map      : 映射，元素具有键值和实值，会根据键值大小自动排序，键值不允许重复
// multimap : 映射，元素具有键值和实值，会根据键值大小自动排序，键值允许重复

// notes:
//
// 异常保证：
// mystl::map<Key, T> / mystl::multimap<Key, T> 满足基本异常保证，对以下等函数做强异常安全保证：
//   * emplace
//   * emplace_hint
//   * insert

#include "rb_tree.h"

#endif