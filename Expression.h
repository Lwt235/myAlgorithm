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
    std::map<char, int>Priority = { {':',0},{'+',1},{'-',2},{'*',3},{'/',4},{'^',5},{';',6} };  //���ȼ���ϵ
    class TreeNode {
    public:
        TreeNode* left;
        TreeNode* right;
        char node;
        TreeNode(TreeNode* left, TreeNode* right, char node) :left(left), right(right), node(node) {};
    };  //�����������
    TreeNode* ExpressionTree = nullptr; //�����ı��ʽ��
    std::map<char, int>AssignMap;   //δ֪��ӳ���
    int qpow(int a, int b) {
        if (b == 1) return a;
        else if (b & 1) return a * qpow(a * a, b >> 1);
        else return qpow(a * a, b >> 1);
    }   //������
    bool isOperator(char ch) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') return true;
        else return false;
    }   //�ж��ַ��Ƿ�Ϊ�����
    void PrintInorder(TreeNode* cur, char front) {
        if (!cur) return;
        if (isOperator(cur->node) && (Priority[cur->node] < Priority[front] || (cur->node == '-' && front == '-') || (cur->node == '/' && front == '/'))) std::cout << "(";
        PrintInorder(cur->left, cur->node);
        std::cout << cur->node;
        PrintInorder(cur->right, cur->node);
        if (isOperator(cur->node) && (Priority[cur->node] < Priority[front] || (cur->node == '-' && front == '-') || (cur->node == '/' && front == '/'))) std::cout << ")";
    }   //�ݹ���������ŵ���׺���ʽ
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
    }   //�ݹ������ʽֵ
public:
    TreeNode* getExpressionTree() {
        return ExpressionTree;
    }   //��ȡ���ʽ��
    void setExpressionTree(TreeNode* Tree) {
        ExpressionTree = Tree;
    }   //���ñ��ʽ��
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
    }   //��ȡǰ׺���ʽ
    void WriteExpre() {
        PrintInorder(ExpressionTree, ':');
        std::cout << std::endl;
    }   //��������ŵ���׺���ʽ
    void Assign(char V, int c) {
        AssignMap[V] = c;
    }   //δ֪����ֵ
    double Value() {
        return getValue(ExpressionTree);
    }   //���ʽ��ֵ
    Expression CompoundExpr(char P, Expression B) {
        Expression tmp; tmp.setExpressionTree(new TreeNode(ExpressionTree, B.getExpressionTree(), P));
        tmp.AssignMap = AssignMap;
        for (auto& item : B.AssignMap) tmp.AssignMap[item.first] = item.second;
        return tmp;
    }   //�����������ʽ
};
#endif // !_EXPRESSION_
