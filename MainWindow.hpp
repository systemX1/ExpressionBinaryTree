#include "MainWindow.h"

void MainWindow::init()
{
	string input;

	while (true) {
		printLine();
		printf("\t\t0 - Construct EBTree\tq - quit\n\
		1 - Print EBTree\t2 - Print Expression\n\
		t - Run Test1\t\ttt - Run Test2\n\
		3 - Print Extra Result\th - Help\n");

		cin >> input;
		if (input == "t") {
			(this->*afp[5])();
		}
		else if (input == "tt") {
			(this->*afp[6])();
		}
		else if (input == "h") {
			(this->*afp[7])();
		}
		else if (input == "q") {
			break;
		}
		else if (isStringDignal(input))
			(this->*afp[stoi(input)])(); //stoi, string to int
		else
			printf("Invalid input\n");			
	}
	printf("\n");
	system("pause");
}

void MainWindow::test0()
{
	printLine();
	printf("Enter infix expression\n");
	string infix;
	cin >> infix;
	if (!BETree::isExpCorrect(infix)) {
		printf("Expression can only contain  [ 0-9 , ( , ) , + , - , * , / , %% , ^ ] \n");
		return;
	}
	betree.reset(infix);
	return;
}

void MainWindow::test1()
{
	printLine();
	betree.printEBTree();
	return;
}

void MainWindow::test2()
{
	printLine();
	printf("Expression:\n");
	betree.printExpression();
	return;
}

void MainWindow::test3()
{
	printLine();
	betree.printExtraInfo();
	return;
}

void MainWindow::test4()
{
	printLine();
	return;
}

void MainWindow::test5()
{
	printLine();
	string infix = "1-(2-3)/(4*(5+6))";
	printf("Original infix: \t%s\n", infix.data());
	betree.reset(infix);
	betree.printEBTree();
	betree.printExpression();
	betree.printExtraInfo();
	return;
}

void MainWindow::test6()
{
	printLine();
	string infix = "((1+2)^3)+5%2";
	printf("Original infix: \t%s\n", infix.data());
	betree.reset(infix);
	betree.printEBTree();
	betree.printExpression();
	betree.printExtraInfo();
	return;
}

void MainWindow::test7()
{
	printLine();
	printf("Data Structures and Algorithms  Expression Binary Tree\n");
	return;
}

void MainWindow::printLine()
{
	printf("__________________________________________________________________\n");
}

bool MainWindow::isStringDignal(const string& s)
{
	for (auto& i : s) {
		if (!isdigit(i))
			return false;
	}
	return true;
}
