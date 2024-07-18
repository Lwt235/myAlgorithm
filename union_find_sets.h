#pragma once
#ifndef _UNION_FIND_SETS_
#define _UNION_FIND_SETS_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _UNORDERED_MAP_
#include <unordered_map>
#endif

template <typename T>
class union_find_sets {
private:
    std::vector<T>items;
    std::unordered_map<T, T>fa;
    std::unordered_map<T, int>size;
public:
    T Find(T element) {
        if (!fa.count(element)) return -1;
        return fa[element] == element ? element : fa[element] = Find(fa[element]);  //Â·¾¶Ñ¹Ëõ
        // return fa[element] == element ? element : Find(fa[element]);
    }
    void Union(const T element1, const T element2) {
        T x = Find(element1), y = Find(element2);
        if (x == -1 || y == -1) return;
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        fa[y] = x;
        size[x] += size[y]; size.erase(y);
    }
    bool sameSet(const T element1, const T element2) {
        T x = Find(element1), y = Find(element2);
        if (x == -1 || y == -1) return false;
        else return x == y;
    }
    int countRoot() {
        return size.size();
    }
    int getSize(const T element) {
        T x = Find(element);
        if (x == -1) return 0;
        return size[Find(element)];
    }
    void init(const std::vector<T>& elements) {
        items = elements;
        for (int i = 0; i < elements.size(); i++) {
            fa[elements[i]] = elements[i];
            size[elements[i]] = 1;
        }
    }
    union_find_sets() {};
    union_find_sets(const std::vector<T>& elements) :items(elements) {
        for (int i = 0; i < elements.size(); i++) {
            fa[elements[i]] = elements[i];
            size[elements[i]] = 1;
        }
    }
};

template<>
class union_find_sets<int> {
private:
    std::vector<int>items;
    std::unordered_map<int, int>fa;
    std::unordered_map<int, int>size;
public:
    int Find(int element) {
        if (!fa.count(element)) return -1;
        return fa[element] == element ? element : fa[element] = Find(fa[element]);  //Â·¾¶Ñ¹Ëõ
        // return fa[element] == element ? element : Find(fa[element]);
    }
    void Union(const int element1, const int element2) {
        int x = Find(element1), y = Find(element2);
        if (x == -1 || y == -1) return;
        if (x == y) return;
        if (size[x] < size[y]) std::swap(x, y);
        fa[y] = x;
        size[x] += size[y]; size.erase(y);
    }
    bool sameSet(const int element1, const int element2) {
        int x = Find(element1), y = Find(element2);
        if (x == -1 || y == -1) return false;
        else return x == y;
    }
    int countRoot() {
        return size.size();
    }
    int getSize(const int element) {
        int x = Find(element);
        if (x == -1) return 0;
        return size[Find(element)];
    }
    void init(const std::vector<int>& elements) {
        items = elements;
        for (int i = 0; i < elements.size(); i++) {
            fa[elements[i]] = elements[i];
            size[elements[i]] = 1;
        }
    }
    union_find_sets() {};
    union_find_sets(int length) {
        for (int i = 1; i <= length; i++) {
            fa[i] = i;
            size[i] = 1;
        }
    }
    union_find_sets(const std::vector<int>& elements) :items(elements) {
        for (int i = 0; i < elements.size(); i++) {
            fa[elements[i]] = elements[i];
            size[elements[i]] = 1;
        }
    }
};
#endif // !UNION_FIND_SETS

