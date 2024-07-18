#pragma once

#ifndef _MYSORT_
#define _MYSORT

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _ITERATOR_
#include <iterator>
#endif

#ifndef _FUNCTIONAL_
#include <functional>
#endif

template <typename Iterator>
Iterator binarySearchInsertPosition(Iterator first, Iterator last, typename std::iterator_traits<Iterator>::value_type value) {
	Iterator low = first;
	Iterator high = last;
	while (low < high) {
		Iterator mid = low + (high - low) / 2;
		if (*mid < value) low = mid + 1;
		else high = mid;
	}
	return high;
}

template <typename Iterator>
void bubbleSort(Iterator arrBegin, Iterator arrEnd) {
	static_assert(std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, "Iterator must be a random access iterator");
	bool change = true;
	for (Iterator i = arrBegin; i != arrEnd && change; i++) {
		change = false;
		for (Iterator j = arrBegin; j + (i - arrBegin) + 1 != arrEnd; j++) {
			if (*(j+1) < *(j)) {
				typename std::iterator_traits<Iterator>::value_type temp = *(j + 1);
				*(j + 1) = *(j);
				*(j) = temp;
				change = true;
			}
		}
	}
} //√∞≈›≈≈–Ú

template <typename Iterator>
void insertSort(Iterator arrBegin, Iterator arrEnd) {
	static_assert(std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value,"Iterator must be a random access iterator");
	for (Iterator i = arrBegin + 1; i != arrEnd; i++) {
		typename std::iterator_traits<Iterator>::value_type temp = *i;
		Iterator j = binarySearchInsertPosition(arrBegin, i, temp);
		for (Iterator k = i; k != j; k--) *(k) = *(k - 1);
		*j = temp;
	}
} //’€∞Î≤Â»Î≈≈–Ú

template <typename Iterator> 
void shellSort(Iterator arrBegin, Iterator arrEnd, std::vector<int>delta = {}) {
	static_assert(std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, "Iterator must be a random access iterator");
	std::function<void(Iterator, Iterator, int)>shellInsert;
	shellInsert = [&](Iterator arrBegin, Iterator arrEnd, int dk) {
		for (Iterator i = arrBegin + dk; i != arrEnd; i++) {
			typename std::iterator_traits<Iterator>::value_type temp = *i;
			Iterator j = i - dk;
			for (; j - arrBegin >= 0 && temp < *j; j -= dk) {
				*(j + dk) = *j;
				if (j - arrBegin < dk) break;
			}
			if (temp < *j && j - arrBegin < dk) *j = temp;
			else *(j + dk) = temp;
		}
	};	//÷¥––“ª¥Œ‘ˆ¡øŒ™dkµƒœ£∂˚≈≈–Ú
	if (delta.empty()) {
		int dk = (arrEnd - arrBegin) >> 1;
		while (dk) {
			delta.emplace_back(dk);
			dk >>= 1;
		}
	}
	for (int i = 0; i < delta.size(); i++) shellInsert(arrBegin, arrEnd, delta[i]);
} //œ£∂˚≈≈–Ú 

template <typename Iterator>
void quickSort(Iterator arrBegin, Iterator arrEnd) {
	static_assert(std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, "Iterator must be a random access iterator");
	std::function<Iterator(Iterator Left, Iterator Right)>Partition;
	Partition = [&](Iterator Left, Iterator Right) {
		typename std::iterator_traits<Iterator>::value_type Pivot = *Left;
		while (Left < Right) {
			while (Left < Right && *Right >= Pivot) --Right;
			if (Left == Right) break;
			*(Left++) = *Right;
			while (Left < Right && *Left <= Pivot) ++Left;
			if (Left == Right) break;
			*(Right--) = *Left;
		}
		*Left = Pivot;
		return Left;
	};
	std::function<void(Iterator, Iterator)>qDFS;
	qDFS = [&](Iterator arrBegin, Iterator arrEnd) {
		Iterator pivotLocation = Partition(arrBegin, arrEnd);
		if (pivotLocation - arrBegin > 1) qDFS(arrBegin, pivotLocation - 1);
		if (arrEnd - pivotLocation > 1) qDFS(pivotLocation + 1, arrEnd);
	};
	qDFS(arrBegin, arrEnd - 1);
}//øÏÀŸ≈≈–Ú

template <typename Iterator>
void selectSort(Iterator arrBegin, Iterator arrEnd) {
	static_assert(std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, "Iterator must be a random access iterator");
	for (Iterator i = arrBegin; i != arrEnd; i++) {
		Iterator minId = i;
		for (Iterator j = i + 1; j != arrEnd; j++)
			if (*j < *minId) minId = j;
		if (minId != i) {
			typename std::iterator_traits<Iterator>::value_type tmp = *i;
			*i = *minId;
			*minId = tmp;
		}
	}
} //—°‘Ò≈≈–Ú

template <typename Iterator>
void mergeSort(Iterator arrBegin, Iterator arrEnd) {
	std::function<void(Iterator, Iterator, Iterator)>Merge;
	Merge = [&](Iterator Left, Iterator Mid, Iterator Right) {
		Iterator aCur = Left, bCur = Mid + 1;
		std::vector<typename std::iterator_traits<Iterator>::value_type>temp(Right - Left + 1);
		for (int i = 0; i < Right - Left + 1; i++) {
			if (bCur == Right + 1 || ((aCur != Mid + 1) && *aCur < *bCur)) temp[i] = *(aCur++);
			else temp[i] = *(bCur++);
		}
		for (Iterator i = Left; i <= Right; i++) *i = temp[i - Left];
	};
	std::function<void(Iterator, Iterator)>mDFS;
	mDFS = [&](Iterator Left, Iterator Right) {
		if (Left == Right) return;
		else {
			mDFS(Left, Left + (Right - Left) / 2);
			mDFS(Left + (Right - Left) / 2 + 1, Right);
			Merge(Left, Left + (Right - Left) / 2, Right);
		}
	};
	mDFS(arrBegin, arrEnd - 1);
} //πÈ≤¢≈≈–Ú

template <typename Iterator>
void heapSort(Iterator arrBegin, Iterator arrEnd) {
	std::function<void(Iterator, Iterator, Iterator, Iterator)>heapAdjust;
	heapAdjust = [&](Iterator arrBegin, Iterator arrEnd, Iterator s, Iterator m) {
		for (Iterator i = arrBegin + 2 * (s - arrBegin + 1) - 1; i <= m; i += i - arrBegin + 1) {
			if (i < m && *i < *(i + 1)) i++;
			if (*i < *s) break;
			typename std::iterator_traits<Iterator>::value_type temp = *s;
			*s = *i;
			*i = temp;
			s = i;
			if (m - i < i - arrBegin) break;
		}
	};
	for (Iterator i = arrBegin + (arrEnd - arrBegin) / 2 - 1; i - arrBegin >= 0; i--) {
		heapAdjust(arrBegin, arrEnd - 1, i, arrEnd - 1);
		if (i == arrBegin) break;
	}
	for (Iterator i = arrEnd - 1; i - arrBegin > 0; i--) {
		typename std::iterator_traits<Iterator>::value_type temp = *arrBegin;
		*arrBegin = *i;
		*i = temp;
		heapAdjust(arrBegin, arrEnd - 1, arrBegin, i - 1);
	}
} //∂—≈≈–Ú

#endif // !_MYSORT_