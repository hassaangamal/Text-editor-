#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;



struct node {
	string data;
	struct node* next;
};

class linked_list
{
private:
	node* head;
	node* tail;
	int numOfLines = 0;
	int next = 1;

public:
	int line = 0;
	std::ofstream outfile;
	linked_list() {
		int yourNum = -1;
		head = NULL;
		tail = NULL;
		int prevPagePrinted = 1;
		while (yourNum != 0) {
			cout << "====Mini Text Editor====\n" << endl;
			cout << "Please choose what you want to" << endl;
			cout << "1. Insert text into Line N" << endl;
			cout << "2. Delete line N" << endl;
			cout << "3. Move line N into line M" << endl;
			cout << "4. Update text in Line N" << endl;
			cout << "5. Get line text" << endl;
			cout << "6. Save into a .txt file" << endl;
			cout << "7. Print all" << endl;
			cout << "8. Open a .txt file" << endl;
			cout << "9. Find text" << endl;
			cout << "10. Find and replace" << endl;
			cin >> yourNum;
			if (yourNum == 1)			//Insert your  line, any line
			{
				string yourNum_2;
				cout << "Please choose what you want to \na. Insert text into Line N" << endl;
				cout << "b. Append text";
				while (yourNum_2 != "a" && yourNum_2 != "b")
				{
					cout << "please enter correct letter: ";
					cin >> yourNum_2;
				}
				if (yourNum_2 == "a")
				{
					int lineGiven;
					string dataGiven;
					cout << "Enter line you want the text to be placed into : ";
					cin >> lineGiven;
					cout << "Enter text : ";
					cin.ignore(1);
					getline(cin, dataGiven);
					if (lineGiven == 1)
					{
						addToHead(dataGiven);
					}
					else if (lineGiven > numOfLines)
					{
						insertFurtherAway(dataGiven, lineGiven);
					}
					else if (lineGiven < numOfLines || lineGiven == numOfLines)
					{
						insertTextBetweenLines(dataGiven, lineGiven);
					}
				}
				else if (yourNum_2 == "b") {
					string dataGiven;
					cout << "Enter text : ";
					cin.ignore(1);
					getline(cin, dataGiven);
					addToTail(dataGiven);
				}

			}
			else if (yourNum == 2)		//Delete any line you want
			{
				int lineGiven;
				cout << "Enter the line you want to delete : ";
				cin >> lineGiven;
				deleteLine(lineGiven);
			}
			else if (yourNum == 3)		//Interchanging two lines
			{
				int lineGiven1;
				int lineGiven2;
				cout << "Enter line 1 you want to swap : ";
				cin >> lineGiven1;
				cout << "Enter line 2 you want to swap : ";
				cin >> lineGiven2;
				moveTwoLines(lineGiven1, lineGiven2);
			}
			else if (yourNum == 4)
			{
				int lineGiven;
				string dataGiven;
				cout << "Enter line you want to change the content of : ";
				cin >> lineGiven;
				if (lineGiven > numOfLines)
				{
					cout << "The line you entered exceeds the existing number of lines..." << endl;
				}
				else {
					cout << "Enter the new text : ";
					cin >> dataGiven;
					updateTextInLine(dataGiven, lineGiven);
				}
			}
			else if (yourNum == 5)
			{
				cout << "Enter the line you want to get text :";
				cin >> line;
				getLine();

				sleep_until(system_clock::now() + 3s);
			}
			else if (yourNum == 6)		//Saving the list into a txt file
			{
				saveAll();
			}
			else if (yourNum == 7) {
				printall();
				sleep_until(system_clock::now() + 3s);
			}
			else if (yourNum == 8)
			{
				openFile();
			}
			else if (yourNum == 9)
			{
				string text;
				cout << "enter your text :" << endl;
				cin >> text;
				findAndReturnLine(text);

			}
			else if (yourNum == 10)
			{
				char replace[500], found[500];
				cin.ignore(1);
				cout << "\nEnter the word to be Found\n";
				cin.getline(found, 1000);
				cout << "\nReplace with \n";
				cin.getline(replace, 1000);
				findAndReplace(found, replace);

			}

		}
	}
	void addToHead(string dataGiven) {		//this function will add to Head
		if (head == NULL)
		{
			node* temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node* temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			temp->next = head;
			head = temp;
			numOfLines++;
		}
	}

	void addToTail(string dataGiven) {		//an extra function used to add a node to tail
		if (head == NULL)					//no node, empty linked list
		{
			node* temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node* temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
	}
	void deleteTail() {						//function used  to delete a Node from tail
		node* temp = head;
		if (head == NULL)
		{
			cout << "Nothing to be deleted." << endl;
		}
		else if (head == tail)
		{
			temp = head;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else
		{
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
		}
	}
	void deleteHead() {						//function used to delete the very first element, and update the head
		node* temp = head;
		node* nextNode = head->next;
		head = nextNode;
		delete(temp);
		numOfLines--;
	}

	void insertTextBetweenLines(string dataGiven, int lineGiven) {		//this function will insert text in the given line, and will push all the other lines
		if (lineGiven == 0)
		{
			cout << "There's no line 0, did you mean 1 !" << endl;
		}
		else if (lineGiven == 1)
		{
			if (head == NULL)					//no node, empty linked list
			{
				node* temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				head = temp;
				tail = head;
				numOfLines++;
			}
			else 								//one or more than one node
			{
				node* temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				temp->next = head;
				head = temp;
				numOfLines++;
			}
		}
		else {
			node* prevNode = head;
			node* nextNode = head;
			node* temp = new node();
			temp->data = dataGiven;
			temp->next = NULL;
			int iterator = 2;
			while (iterator < lineGiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			prevNode->next = temp;
			temp->next = nextNode;
			numOfLines++;
		}
	}
	void updateTextInLine(string dataGiven, int lineGiven) {		//this function will overwrite anything written in the given line
		if (lineGiven == 0)
		{
			cout << "There's no line 0!" << endl;
		}
		else if (numOfLines >= lineGiven)
		{
			node* temp = head;
			int goToLine = 1;
			while (goToLine < lineGiven)
			{
				temp = temp->next;
				goToLine++;
			}
			temp->data = dataGiven;

		}
	}
	void deleteLine(int lineGiven) {
		if (head == NULL)
		{
			cout << "There is no line to be deleted" << endl;
		}
		else if (head == tail) {
			node* temp = head;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else if (lineGiven == 0) {
			cout << "There's no line 0, did you mean line 1" << endl;
		}
		else if (lineGiven == 1) {
			deleteHead();

		}
		else if (lineGiven == numOfLines) {
			deleteTail();

		}
		else if (lineGiven > numOfLines)
		{
			cout << "Entered line is larger than existing lines..." << endl;
		}
		else if (lineGiven < numOfLines)
		{

			node* prevNode = head;
			node* nextNode = head;
			node* temp = head;
			int iterator = 2;
			while (iterator < lineGiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			temp = nextNode;
			nextNode = nextNode->next;
			prevNode->next = nextNode;
			delete(temp);
			numOfLines--;

		}
	}

	void insertFurtherAway(string dataGiven, int lineGiven) {		//will print /n lines if given line is larger than numOfLines
		if (head == NULL)
		{
			while (numOfLines < lineGiven - 1)
			{
				addToTail("\n");
			}
			addToTail(dataGiven);
		}
		else {
			while (numOfLines < lineGiven - 1)
			{
				addToTail("\n");
			}
			addToTail(dataGiven);
		}
	}
	void moveTwoLines(int nLineGiven, int mLineGiven) {		//function used to Move line N into line M
		if (nLineGiven == 1)
		{
			string headText = head->data;
			deleteHead();
			insertTextBetweenLines(headText, mLineGiven);
		}
		else
		{
			node* temp = head;
			int iterator = 1;
			while (iterator < nLineGiven)
			{
				temp = temp->next;
				iterator++;
			}
			string dataSaved = temp->data;
			deleteLine(nLineGiven);
			insertTextBetweenLines(dataSaved, mLineGiven);
		}
	}
	void openFile() {					//function used to open a file from the same folder this cpp file is in
		string fileName;
		cout << "Enter the file name : ";
		cin >> fileName;
		fileName += ".txt";
		ifstream myfile;
		myfile.open(fileName);
		string s;
		while (!myfile.is_open())
		{
			cout << "Error while opening the file\nPlease try again..\n";
			cout << "Enter the name of an existing file in the application folder the extension: ";
			cin >> fileName;
			myfile.open(fileName);
		}
		cout << "File opened successfully\n";
		while (getline(myfile, s))
		{
			addToTail(s);
		}
		myfile.close();
	}
	void printall() {						//function used to print the whole linked list
		node* temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		int choice;
		if (head == NULL)
		{
			cout << "no elements here !!" << endl;
		}
		else {
			while (temp != NULL)
			{
				if (linePrinted == 1)
				{
					cout << "-------------------Page " << "1" << "-------------------\n";
				}
				else if ((linePrinted - 1) % 10 == 0)
				{
					cout << "-------------------Page " << pagePrinted << "-------------------\n";
					pagePrinted++;

				}
				cout << linePrinted << ") " << temp->data << endl;
				temp = temp->next;
				linePrinted++;
			}
		}
	}
	void getLine() {						//function used to print specifec line
		node* temp = head;
		int linePrinted = 1;
		if (head == NULL || numOfLines < line)
		{
			cout << "No elements here." << endl;
		}
		else {
			while (temp != NULL)
			{
				if (linePrinted == line)
				{
					cout << linePrinted << ") " << temp->data << endl;

				}

				temp = temp->next;

				linePrinted++;
			}
		}
	}

	void saveAll() {
		node* temp = head;
		string fileName;
		cout << "Enter the file name : ";
		cin >> fileName;
		fileName += ".txt";
		outfile.open(fileName, ios::trunc);
		while (temp != NULL)
		{
			outfile << temp->data;
			outfile << "\n";
			temp = temp->next;
		}
		outfile.close();
	}
	void findAndReturnLine(string datagiven) {						//function used to find a string in linked list
															//and return specific line in linked list
		node* temp = head;
		int linePrinted = 1;
		bool flag = false;

		if (head == NULL)
		{
			cout << "no elements here !!" << endl;
		}
		else {
			while (temp != NULL)
			{
				auto found = temp->data.find(datagiven);

				if (found != string::npos)
				{
					cout << "we found your text in :" << endl;
					cout << linePrinted << ") " << endl;
					flag = true;
					break;

				}

				temp = temp->next;
				linePrinted++;
			}
			if (flag != true) {
				cout << "sorry we can't found your text." << endl;
			}
		}
	}

	void findAndReplace(string search, string replace)		//function used to find a string in linked list
									//and replace it in linked list
	{
		node* temp = head;
		if (head == NULL)
		{
			cout << "no elements here !!" << endl;
		}
		else {
			while (temp != NULL) {

				int found = temp->data.find(search);

				while (found != string::npos) {

						temp->data.replace(found, search.size(), replace);
						found = temp->data.find(search, found + replace.size());
				}
				temp = temp->next;
			}
		}
	}



};

int main(int argc, char const* argv[])
{
	linked_list ourList;
	return 0;
}
