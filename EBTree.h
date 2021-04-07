#pragma once
#ifndef _EBTREE_H_
#define _EBTREE_H_

#include <stack>
using std::stack;

#include <string>
using std::string;

#include <algorithm>
using std::max;

struct TreeNode
{
    //function member
    TreeNode(char x, TreeNode* l = nullptr, TreeNode* r = nullptr) : data(x), lChild(l), rChild(r) {}
    ~TreeNode() {}

    //data member
	char data;
	TreeNode* lChild, * rChild;
} ;

//Binary Expression Tree
class BETree
{
public:
    //Constructor and Destructor
    BETree() : root(nullptr) {}
    BETree(const string& infix);
    void reset(const string& infix);
    void destroyTree(TreeNode* t);
    ~BETree() { destroyTree(root); }

    //Output
    void preorder(string& str, TreeNode* t) const;
    void inorder(string& str, TreeNode* t) const;
    void postorder(string& str, TreeNode* t) const;
    void printExpression() const;
    void printExtraInfo() const;
    void printEBTree() const;
    void display(const string& str, const TreeNode* node, bool isLeft) const;

    //Extra
    bool getResult(int& ret) const;
    int getHeight(TreeNode* t) const;
    int getSize(TreeNode* t) const;

    //Assistance
    static string infixToPostfix(const string& infix);
    static int getPriority(const char& ch);
    static int ipow(int base, int exp);

    //Expression Validation
    static bool isExpCorrect(const string& infix);
    static bool isOperator(const char& ch) ;
private:
    TreeNode* root;
};

#endif