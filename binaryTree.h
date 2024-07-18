#pragma once
#ifndef _BINARYTREE_
#define _BINARYTREE_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _QUEUE_
#include <queue>
#endif

#ifndef _STACK_
#include <stack>
#endif

template<typename T>
class TreeNode {
public:
	TreeNode* leftChild;
	TreeNode* rightChild;
	T val;
	TreeNode() :leftChild(nullptr), rightChild(nullptr) {};
	TreeNode(TreeNode* leftChild, TreeNode* rightChild) :leftChild(leftChild), rightChild(rightChild) {};
	TreeNode(TreeNode* leftChild, TreeNode* rightChild, T val) :leftChild(leftChild), rightChild(rightChild), val(val) {};
};

template<typename T>
class huffmanTree {
protected:
	class huffmanTreeNode {
	public:
		int frequency;
		huffmanTreeNode* leftChild;
		huffmanTreeNode* rightChild;
		T val;
		huffmanTreeNode() :TreeNode<T>() {};
		huffmanTreeNode(huffmanTreeNode* leftChild, huffmanTreeNode* rightChild, int frequency):leftChild(leftChild), rightChild(rightChild), frequency(frequency) {};
		huffmanTreeNode(huffmanTreeNode* leftChild, huffmanTreeNode* rightChild, int frequency, T val) :leftChild(leftChild), rightChild(rightChild), frequency(frequency), val(val) {};
		bool operator <(huffmanTreeNode& a) const {
			return frequency < a.frequency;
		}
	};
	huffmanTreeNode* huffmanTreeRoot = nullptr;
	void getCode(std::map<T, std::string>& Code, std::string curCode, huffmanTreeNode* curNode) {
		if (!curNode->leftChild && !curNode->rightChild) {
			Code[curNode->val] = curCode;
			return;
		}
		if (curNode->leftChild) getCode(Code, curCode + '0', curNode->leftChild);
		if (curNode->rightChild) getCode(Code, curCode + '1', curNode->rightChild);
	}
	class cmp {
	public:
		bool operator ()(huffmanTreeNode* a, huffmanTreeNode* b) {
			return (*b) < (*a);
		}
	};
public:
	void initHuffmanTree(std::map<T, int>& Datas) {
		std::priority_queue<huffmanTreeNode*, std::vector<huffmanTreeNode*>, cmp>Qu;
		for (auto& item : Datas)
			Qu.push(new huffmanTreeNode(nullptr, nullptr, item.second, item.first));
		while (Qu.size() > 1) {
			huffmanTreeNode* a = Qu.top(); Qu.pop();
			huffmanTreeNode* b = Qu.top(); Qu.pop();
			Qu.push(new huffmanTreeNode(a, b, a->frequency + b->frequency));
		}
		huffmanTreeRoot = Qu.top(); Qu.pop();
		return;
	}
	std::map<T, std::string> getHuffmanCode() {
		if (!huffmanTreeRoot) return {};
		std::map<T, std::string>res;
		getCode(res, "", huffmanTreeRoot);
		return res;
	}
	
};

template<typename T>
class balancedBinaryTree {
protected:
	class balancedTreeNode {
	public:
		balancedTreeNode* leftChild;
		balancedTreeNode* rightChild;
		//balancedTreeNode* father;
		int height;
		T val;
		balancedTreeNode() :leftChild(nullptr), rightChild(nullptr) {};
		balancedTreeNode(balancedTreeNode* leftChild, balancedTreeNode* rightChild, T val, int height) :leftChild(leftChild), rightChild(rightChild), val(val), height(height) {};
	};
	balancedTreeNode* BalancedTree;
	void rightRotate(balancedTreeNode** node) {
		balancedTreeNode* left = (*node)->leftChild, * right = (*node)->rightChild, * cur = *node;
		*node = left;
		cur->leftChild = left->rightChild;
		(*node)->rightChild = cur;
	}//进行右旋

	void leftRotate(balancedTreeNode** node) {
		balancedTreeNode* left = (*node)->leftChild, * right = (*node)->rightChild, * cur = *node;
		*node = right;
		cur->rightChild = right->leftChild;
		(*node)->leftChild = cur;
	}//进行左旋

	void calcHeight(balancedTreeNode** node) {
		(*node)->height = 1;
		if ((*node)->leftChild) (*node)->height = std::max((*node)->height, (*node)->leftChild->height + 1);
		if ((*node)->rightChild) (*node)->height = std::max((*node)->height, (*node)->rightChild->height + 1);
	}
public:
	balancedBinaryTree() :BalancedTree(nullptr) {};
	bool exist(T element) {
		balancedTreeNode* cur = BalancedTree;
		while (cur && cur->val != element) {
			if (cur->val < element) cur = cur->rightChild;
			else cur = cur->leftChild;
		}
		if (!cur) return false;
		else return true;
	}
	void insert(T element) {
		if (!BalancedTree) {
			BalancedTree = new balancedTreeNode(nullptr, nullptr, element, 1);
			return;
		}	//树是空的
		std::stack<balancedTreeNode**>St;
		balancedTreeNode** cur = &BalancedTree; 
		St.push(cur);
		while (*cur && (*cur)->val != element) {
			if ((*cur)->val < element)	cur = &((*cur)->rightChild);
			else cur = &((*cur)->leftChild);
			St.push(cur);
		}
		if (*cur) return; 
		St.pop(); cur = St.top();
		if ((*cur)->val < element) (*cur)->rightChild = new balancedTreeNode(nullptr, nullptr, element, 1);
		else (*cur)->leftChild = new balancedTreeNode(nullptr, nullptr, element, 1);

		while (!St.empty()) {
			cur = St.top(); St.pop();
			int leftHeight = (*cur)->leftChild ? (*cur)->leftChild->height : 0;
			int rightHeight = (*cur)->rightChild ? (*cur)->rightChild->height : 0;
			if ((*cur)->leftChild) (*cur)->height = std::max((*cur)->height, (*cur)->leftChild->height + 1);
			if ((*cur)->rightChild) (*cur)->height = std::max((*cur)->height, (*cur)->rightChild->height + 1);
			if (std::abs(leftHeight - rightHeight) > 1) {
				if (element < (*cur)->val && (*cur)->leftChild && element < (*cur)->leftChild->val) {
					rightRotate(cur);
					calcHeight(&((*cur)->rightChild));
					calcHeight(cur);
				}
				else if (element < (*cur)->val && (*cur)->leftChild && element > (*cur)->leftChild->val) {
					leftRotate(&((*cur)->leftChild));
					rightRotate(cur);
					calcHeight(&((*cur)->leftChild));
					calcHeight(&((*cur)->rightChild));
					calcHeight(cur);
				}
				else if (element > (*cur)->val && (*cur)->rightChild && element > (*cur)->rightChild->val) {
					leftRotate(cur);
					calcHeight(&((*cur)->leftChild));
					calcHeight(cur);
				}
				else if (element > (*cur)->val && (*cur)->rightChild && element < (*cur)->rightChild->val) {
					rightRotate(&((*cur)->rightChild));
					leftRotate(cur);
					calcHeight(&((*cur)->leftChild));
					calcHeight(&((*cur)->rightChild));
					calcHeight(cur);
				}
			}
		}
	}
};

//主席树——静态区间第k小
class persistentSegmentTrees {
private:
#define N 200005
#define lc(x) tr[x].ch[0]
#define rc(x) tr[x].ch[1]
	int root[N] = { 0 }, idx = 0;
	struct node
	{
		int ch[2];
		int s; //节点值域中有多少个数
	}tr[N * 22];
	void build(int& x, int l, int r) {
		x = ++idx;
		if (l == r) return;
		int m = l + r >> 1;
		build(lc(x), l, m);
		build(rc(x), m + 1, r);
	}
	void insert(int x, int& y, int l, int r, int v) {
		y = ++idx; tr[y] = tr[x]; tr[y].s++;
		if (l == r) return;
		int m = l + r >> 1;
		if (v <= m) insert(lc(x), lc(y), l, m, v);
		else insert(rc(x), rc(y), m + 1, r, v);
	}
	int query(int x, int y, int l, int r, int k) {
		if (l == r) return l;
		int m = l + r >> 1;
		int s = tr[lc(y)].s - tr[lc(x)].s;
		if (k <= s) return query(lc(x), lc(y), l, m, k);
		else return query(rc(x), rc(y), m + 1, r, k - s);
	}
};

#endif // !_BINARYTREE_
