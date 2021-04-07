#include "EBTree.h"

BETree::BETree(const string& infix)
{
	reset(infix);
}

void BETree::reset(const string& infix)
{
	if (root)
		destroyTree(root);

	string postfix = infixToPostfix(infix);
	stack<TreeNode*> stk;
	TreeNode* temp1;
	TreeNode* temp2;

	for (auto& i : postfix) {
		if (isOperator(i)) {
			temp1 = stk.top(); stk.pop();
			temp2 = stk.top(); stk.pop();
			TreeNode* t = new TreeNode(i, temp2, temp1);
			stk.push(t);
		}
		else if (isdigit(i)) {
			TreeNode* t = new TreeNode(i);
			stk.push(t);
		}
	}
	root = stk.top();
}

void BETree::destroyTree(TreeNode* t)
{
	if (!t) {
		return;
	}
	destroyTree(t->lChild);
	destroyTree(t->rChild);
	delete t;
}

void BETree::preorder(string& str, TreeNode* t) const
{
	if (!t) {
		return;
	}
	str += t->data;
	preorder(str, t->lChild);
	preorder(str, t->rChild);
}

void BETree::inorder(string& str, TreeNode* t) const
{
	if (!t) {
		return;
	}
	else if (!t->lChild || !t->rChild)
		str += t->data;
	else {
		if (isOperator(t->lChild->data) && (getPriority(t->lChild->data) < getPriority(t->data))) {
			str += "(";
			inorder(str, t->lChild);
			str += ")";
		}
		else
			inorder(str, t->lChild);

		str += t->data;
		
		if (isOperator(t->rChild->data) && (getPriority(t->rChild->data) < getPriority(t->data))) {
			str += "(";
			inorder(str, t->rChild);
			str += ")";
		}
		else 
			inorder(str, t->rChild);
	}
}

void BETree::postorder(string& str, TreeNode* t) const
{
	if (!t) {
		return;
	}
	postorder(str, t->lChild);
	postorder(str, t->rChild);
	str += t->data;
}

void BETree::printExpression() const
{
	printf("\n Prefix : \t[ ");
	string prefix;
	preorder(prefix, root);
	printf("%s", prefix.data());
	printf(" ]");

	printf("\n Infix : \t[ ");
	string infix;
	inorder(infix, root);
	printf("%s", infix.data());
	printf(" ]");

	printf("\n Postfix : \t[ ");
	string postfix;
	postorder(postfix, root);
	printf("%s", postfix.data());
	printf(" ]\n");
}

void BETree::printExtraInfo() const
{
	int ret = 0;
	printf(" Expression Result: \t");
	if (getResult(ret))
		printf("%d\n", ret);

	printf(" EBTree Height: \t%d\n", getHeight(root));
	printf(" EBTree Size: \t\t%d\n", getSize(root));
}

void BETree::printEBTree() const
{
	display("", root, false);
}

void BETree::display(const string& str, const TreeNode* t, bool isLeft) const
{
	if (t)
	{
		printf("%s", str.data());

		isLeft ? printf("|-- ") : printf("\\-- ");

		printf("%c\n", t->data);

		// enter the next tree level - left and right branch
		display(str + (isLeft ? "|   " : "    "), t->lChild, true);
		display(str + (isLeft ? "|   " : "    "), t->rChild, false);
	}
}

bool BETree::getResult(int& ret) const
{
	stack<int> stk;

	string postfix;
	postorder(postfix, root);

	for(auto& i : postfix)
	{
		if (isdigit(i))
		{
			stk.push(i - '0');
		}
		else if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%' || i == '^')
		{
			int num1 = stk.top();
			stk.pop();
			int num2 = stk.top();
			stk.pop();
			int calc = 0;
			switch (i)
			{
			case '+':
				calc = num2 + num1;
				break;
			case '-':
				calc = num2 - num1;
				break;
			case '*':
				calc = num2 * num1;
				break;
			case '/':
				if (num1 == 0)
				{
					printf("Math Error: Can't Divide by Zero\n");
					return false;
				}
				calc = num2 / num1;
				break;
			case '%':
				if (num1 == 0)
				{
					printf("Math Error: Can't Divide by Zero\n");
					return false;
				}
				calc = num2 % num1;
				break;
			case '^':
				calc = ipow(num2, num1);
				break;
			}
			stk.push(calc);
		}
	}
	ret = stk.top();
	return true;
}

int BETree::getHeight(TreeNode* t) const
{
	if (!t)
		return 0;
	else
		return 1 + max(getHeight(t->lChild), getHeight(t->rChild));
}

int BETree::getSize(TreeNode* t) const
{
	if (!t)
		return 0;
	else
		return(1 + getSize(t->lChild) + getSize(t->rChild));
}

string BETree::infixToPostfix(const string& infix)
{
    unsigned int inCnt = 0;
	unsigned int postCnt = 0;
	stack<char> st;
    char* postfix = new char[infix.length() + 10];
	
	char elem;
	while (inCnt < infix.length())
	{
		elem = infix[inCnt];
		if (elem == '(')
		{
			st.push(elem);
			inCnt++;
			continue;
		}
		if (elem == ')')
		{
			while (!st.empty() && st.top() != '(')
			{
				postfix[postCnt++] = st.top();
				st.pop();
			}
			if (!st.empty())
			{
				st.pop();
			}
			inCnt++;
			continue;
		}

		if (!getPriority(elem))
		{
			postfix[postCnt++] = elem;
		}
		else
		{
			if (st.empty())
			{
				st.push(elem);
			}
			else
			{
				while (!st.empty() && st.top() != '(' &&
					getPriority(elem) <= getPriority(st.top()))
				{
					postfix[postCnt++] = st.top();
					st.pop();
				}
				st.push(elem);
			}
		}
		inCnt++;
	}

	while (!st.empty())
	{
		postfix[postCnt++] = st.top();
		st.pop();
	}
	postfix[postCnt] = '\0';
    string ret(postfix);
    return ret;
}

int BETree::getPriority(const char& ch)
{
	switch (ch)
	{
	case '^':
		return 4;
	case '%':
		return 3;
	case '/':
	case '*':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

int BETree::ipow(int base, int exp)
{
	int result = 1;
	for (;;)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}

	return result;
}

bool BETree::isExpCorrect(const string& infix)
{
    for(auto& i : infix){
        if (!isdigit(i) && !isOperator(i))
			return false;
    }
    return true;
}

bool BETree::isOperator(const char& ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')')
		return true;
    return false;
}
