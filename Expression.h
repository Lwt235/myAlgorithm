#pragma once
#ifndef _EXPRESSION_
#define _EXPRESSION

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STACK_
#include <stack>
#endif

#ifndef _CSTRING_
#include <cstring>
#endif

class Expression {
    std::map<char, int>Priority = { {':',0},{'+',1},{'-',2},{'*',3},{'/',4},{'^',5},{';',6} };  //优先级关系
    class TreeNode {
    public:
        TreeNode* left;
        TreeNode* right;
        char node;
        TreeNode(TreeNode* left, TreeNode* right, char node) :left(left), right(right), node(node) {};
    };  //二叉链表存树
    TreeNode* ExpressionTree = nullptr; //构建的表达式树
    std::map<char, int>AssignMap;   //未知数映射表
    int qpow(int a, int b) {
        if (b == 1) return a;
        else if (b & 1) return a * qpow(a * a, b >> 1);
        else return qpow(a * a, b >> 1);
    }   //快速幂
    bool isOperator(char ch) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') return true;
        else return false;
    }   //判断字符是否为运算符
    void PrintInorder(TreeNode* cur, char front) {
        if (!cur) return;
        if (isOperator(cur->node) && (Priority[cur->node] < Priority[front] || (cur->node == '-' && front == '-') || (cur->node == '/' && front == '/'))) std::cout << "(";
        PrintInorder(cur->left, cur->node);
        std::cout << cur->node;
        PrintInorder(cur->right, cur->node);
        if (isOperator(cur->node) && (Priority[cur->node] < Priority[front] || (cur->node == '-' && front == '-') || (cur->node == '/' && front == '/'))) std::cout << ")";
    }   //递归输出带括号的中缀表达式
    double getValue(TreeNode* cur) {
        if (cur->node >= '0' && cur->node <= '9') return (cur->node) ^ 48;
        else if (cur->node >= 'a' && cur->node <= 'z') return AssignMap[cur->node];
        else {
            switch (cur->node)
            {
            case '+':
                return getValue(cur->left) + getValue(cur->right);
            case '-':
                return getValue(cur->left) - getValue(cur->right);
            case '*':
                return getValue(cur->left) * getValue(cur->right);
            case '/':
                return getValue(cur->left) / getValue(cur->right);
            case '^':
                return qpow(getValue(cur->left), getValue(cur->right));
            }
            return 0;
        }
    }   //递归计算表达式值
public:
    TreeNode* getExpressionTree() {
        return ExpressionTree;
    }   //获取表达式树
    void setExpressionTree(TreeNode* Tree) {
        ExpressionTree = Tree;
    }   //设置表达式树
    void ReadExpre(std::string E) {
        std::stack<TreeNode*>Object;
        ExpressionTree = nullptr;
        for (int i = E.length() - 1; i >= 0; i--) {
            if (E[i] == '+' || E[i] == '-' || E[i] == '*' || E[i] == '/' || E[i] == '^') {
                TreeNode* A = Object.top(); Object.pop();
                TreeNode* B = Object.top(); Object.pop();
                Object.emplace(new TreeNode(A, B, E[i]));
            }
            else {
                if (E[i] >= 'a' && E[i] <= 'z') AssignMap[E[i]] = 0;
                Object.emplace(new TreeNode(nullptr, nullptr, E[i]));
            }
        }
        ExpressionTree = Object.top();
    }   //读取前缀表达式
    void WriteExpre() {
        PrintInorder(ExpressionTree, ':');
        std::cout << std::endl;
    }   //输出带括号的中缀表达式
    void Assign(char V, int c) {
        AssignMap[V] = c;
    }   //未知数赋值
    double Value() {
        return getValue(ExpressionTree);
    }   //表达式求值
    Expression CompoundExpr(char P, Expression B) {
        Expression tmp; tmp.setExpressionTree(new TreeNode(ExpressionTree, B.getExpressionTree(), P));
        tmp.AssignMap = AssignMap;
        for (auto& item : B.AssignMap) tmp.AssignMap[item.first] = item.second;
        return tmp;
    }   //复合两个表达式
};
#endif // !_EXPRESSION_
