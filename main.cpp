#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
using namespace std;

#define N 4000

bool sortdetected;

struct Node
{
	char name_info[32];
	char street[18];
	union {
		short int house_num;
		size_t byte_num[sizeof(house_num)];
	};
	short int room_num;
	char date[10];
	
	Node* next;
};

struct List 
{
	Node* data;
	Node* head;
	Node* tail;
};

struct Queue
{
	Node* data;
	Node* head;
	Node* tail;
};

int queue_count = 0;

struct Vertex 
{
	Vertex* left;
	Vertex* right;
	Vertex* next;
	Node* data;
	int balance;
	int weight;
};


void pushBack(Node*& head, Node* value)
{
	Node* newNode = new Node(*value);
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
		return;
	}

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	temp->next = newNode;
}

void enqueue(Queue*& queue, Node* value) 
{
	Node* newNode = new Node(*value);
	newNode->next = nullptr;

	if (queue->head == nullptr) {
		queue->head = newNode;
		queue->tail = newNode;
	}
	else {
		queue->tail->next = newNode;
		queue->tail = newNode;
	}
}

void popQ(Queue& queue)
{ 
	if (queue.head == nullptr)
	{
		cout << "Очередь пуста" << endl;
		return;
	}

	Node* temp = queue.head;
	queue.head = queue.head->next;
	delete temp;

	if (queue.head == nullptr)
	{
		queue.tail = nullptr;
	}

}

void digitalSort(Node*& head)
{
	Queue Q[256]{};

	for (int i = 0; i < 255; i++) {
		Q[i].tail = Q[i].head = nullptr;
	}
	

	for (int j = 2; j >= 0; j--) {
		for (int i = 0; i < 255; i++) {
			Q[i].tail = Q[i].head = nullptr;
		}
		while (head) {
			int d;
			d = head->name_info[j] + 128;
			Node* p = Q[d].tail;
			if (Q[d].head == nullptr) {
				Q[d].head = head;
			}
			else {
				p->next = head;
			}
			p = Q[d].tail = head;
			head = head->next;
			p->next = nullptr;
		}
		head = nullptr;
		int i;
		for (i = 0; i < 255; i++) {
			if (Q[i].head != nullptr) {
				break;
			}
		}
		head = Q[i].head;
		Node* p = Q[i].tail;
		for (int k = i + 1; k < 255; k++) {
			if (Q[k].head != nullptr) {
				p->next = Q[k].head;
				p = Q[k].tail;
			}
		}
	}
	for (int g = 35; g >= 0; g--) {
		for (int i = 0; i < 255; i++) {
			Q[i].tail = Q[i].head = nullptr;
		}
		while (head) {
			int d;
			d = head->street[g] + 128;
			Node* p = Q[d].tail;
			if (Q[d].head == nullptr) {
				Q[d].head = head;
			}
			else {
				p->next = head;
			}
			p = Q[d].tail = head;
			head = head->next;
			p->next = nullptr;
		}
		head = nullptr;
		int i;
		for (i = 0; i < 255; i++) {
			if (Q[i].head != nullptr) {
				break;
			}
		}
		head = Q[i].head;
		Node* p = Q[i].tail;
		for (int k = i + 1; k < 255; k++) {
			if (Q[k].head != nullptr) {
				p->next = Q[k].head;
				p = Q[k].tail;
			}
		}
	}
	sortdetected = true;
}

void bubbleSort(Node* indArr, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (indArr[j].street > indArr[j + 1].street)
			{
				swap(indArr[j], indArr[j + 1]);
			}
}

void intBubbleSort(int* arr, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
}



Queue* BinSearch(Node** head, char* key) 
{
	Node** index = new Node * [N];
	Node* current = *head;
	int indexCount = 0;

	while (current != nullptr && indexCount < N) {
		index[indexCount] = current;
		current = current->next;
		indexCount++;
	}

	int left = 0, right = indexCount - 1, mid;
	Node* temp = nullptr;

	while (left < right) {
		mid = (left + right) / 2;
		temp = index[mid];
		if (strncmp(temp->street, key, 3) < 0) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	if (temp != nullptr) {
		Queue* queue = new Queue;
		queue->head = nullptr;
		queue->tail = nullptr;

		while (temp != nullptr)
		{
			if (strncmp(temp->street, key, 3) == 0)
			{
				enqueue(queue, temp);
				queue_count++;
				temp = temp->next;
			}
			else {
				temp = temp->next;
			}
		}
		return queue;
	}
	return nullptr;
}

void TreeSearch(Vertex* p, char* key) {
	if (p != NULL)
	{
		if (strcmp(p->data->street, key) < 0) 
		{
			TreeSearch(p->left, key);
		}
		else {
			if (strcmp(p->data->street, key) > 0) {
				TreeSearch(p->right, key);
			}
			else {
				cout << "Person if found!: " << " " << p->data->name_info << "  " << p->data->street << "  " << p->data->house_num << "  " << p->data->room_num << "  " << p->data->date << endl;
				TreeSearch(p->next, key);
			}
		}
	}
}

void dop_a1(Vertex*& point, Node* data, int weight) 
{
	if (point == nullptr) {
		point = new Vertex;
		point->left = nullptr;
		point->right = nullptr;
		point->data = data;
		point->next = nullptr;
		point->balance = 0;
		point->weight = weight;
	}
	else if (data->house_num == point->data->house_num) 
	{
		dop_a1(point->next, data, weight);
	}
	else if (data->house_num < point->data->house_num) 
	{
		dop_a1(point->left, data, weight);
	}
	else if (data->house_num > point->data->house_num) 
	{
		dop_a1(point->right, data, weight);
	}
}

void delete_tree(Vertex*& p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

void LRprint(Vertex* x) {
	if (x) {
		LRprint(x->left);
		cout <<
			x->data->name_info << "\t" <<
			x->data->street << "\t" <<
			x->data->house_num << "\t" <<
			x->data->room_num << "\t" <<
			x->data->date << endl;
		LRprint(x->next);
		LRprint(x->right);
	}
}
int size(Vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->left) + size(x->right);
	}
}

int height(Vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->left), height(x->right));
	}
}

int sdp(Vertex* x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->left, l + 1) + sdp(x->right, l + 1);
	}
}

int Max(int x, int y)
{
	if (x > y) return x;
	return y;
}

void printInOrder(Vertex* root) {
	if (root == nullptr) {
		return;
	}

	printInOrder(root->left);
	cout << "Street: " << root->data->street << ", Weight: " << root->weight << endl;
	printInOrder(root->right);
}

void printOptimalSearchTree(Vertex* root) {
	cout << "Optimal Search Tree:" << endl;
	printInOrder(root);
}

void printList(List* list);

void printPage(List* list, int number);

void printMenu(List* list, List* copy);


int main(int argc, char* argv[])
{
	FILE* fp = fopen("base.dat", "rb");
	
	if (fp == nullptr)
	{
		cout << "We've got problems" << endl;
		return -1;
	}
	List* list = new List[N];
	List* list_copy = new List[N];
	
	list->head = nullptr;
	list->tail = nullptr;

	list_copy->head = nullptr;
	list_copy->tail = nullptr;

	for (int i = 0; i < N; i++)
	{
		Node* data = new Node;
		fread(&(data->name_info), sizeof(char), 32, fp);
		fread(&(data->street), sizeof(char), 18, fp);
		fread(&(data->house_num), sizeof(short int), 1, fp);
		fread(&(data->room_num), sizeof(short int), 1, fp);
		fread(&(data->date), sizeof(char), 10, fp);

		pushBack(list->head, data);
		pushBack(list_copy->head, data);
	}
	fclose(fp);
	
	printMenu(list, list_copy);

	return 0;
}



void printList(List* list)
{
	system("cls");
	Node* data = list->head;
	int i = 0, limit = 200, k = 0, pageNumber = 0;
	while (true)
	{
		system("cls");
		int k = 0;
		pageNumber++;
		cout << endl << "\t\t\t\t\tPage #" << pageNumber << endl << endl;
		cout << "#\t" << "\tName info\t\t" << "  Street\t\t" << "House\t" << "Room\t" << "  Date" << endl << endl;
		while (k != limit)
		{
			i++;
			cout << i << "\t" << 
				data->name_info << "\t" << 
				data->street << "\t" << 
				data->house_num << "\t" << 
				data->room_num << "\t" << 
				data->date << endl;
				data = data->next;
			k++;
		}
		if (pageNumber == 200)
		{
			k += 2;
		}
		char page_agreement;
		cout << "\n\n\t\t\t\t   Another page? Y/N\n";
		cin >> page_agreement;
		if (page_agreement == 'n' || page_agreement == 'N')
		{
			system("cls");
			break;
		}
	}
}

void printPage(List* list, int number)
{
	system("cls");
	Node* data = list->head;
	int i, limit = 20, k = 0;

	for (i = 0; i < 20 * (number-1); i++)
	{
		data = data->next;
	}
	i = 20 * (number - 1);

	cout << endl << "\t\t\t\t\tPage #" << number << endl << endl;
	cout << "#\t" << "\tName info\t\t" << "  Street\t\t" << "House\t" << "Room\t" << "  Date" << endl << endl;

	while (true)
	{
		while (k != limit)
		{
			i++;
			cout << i << "\t" << 
				data->name_info << "\t" << 
				data->street << "\t" << 
				data->house_num << "\t" << 
				data->room_num << "\t" << 
				data->date << endl;
			data = data->next;
			k++;
		}
		cout << endl;
		system("pause");
		break;
	}
}

void printMenu(List* list, List* list_copy)
{
	system("cls");

	int answer, choice;
	

	cout << "Choose the option: " << endl << endl;
	cout << "1 - Show all database." << endl;
	cout << "2 - Show specific page." << endl;
	cout << "3 - Start the sort." << endl;
	cout << "4 - Initialize key search" << endl;
	cout << "5 - Exit the programm." << endl;
	

	cin >> answer;

	switch (answer)
	{
	case 1:
	{
		system("cls");
		choice = 0;
		cout << "Choose which list you want to see: " << endl;
		cout << "1 - Default list" << endl << "2 - Sorted list" << endl;
		cin >> choice;
		if (choice == 1)
		{
			printList(list);
			printMenu(list, list_copy);
			break;
		}
		else if (choice == 2)
		{
			if (sortdetected == true)
			{
				printList(list_copy);
				printMenu(list, list_copy);
				break;
			}
			else
			{
				digitalSort(list_copy->head);
				printList(list_copy);
				printMenu(list, list_copy);
				break;
			}
		}
		printList(list);
		printMenu(list, list_copy);
		break;
	}
		
	case 2:
		system("cls");
	{
		int number = 0;

		cout << "Type number of page: ";
		cin >> number;
		if (number <= 0 || number >= 201)
		{
			cout << "Error! Where is no page with this number." << endl;
			system("pause");
			printMenu(list, list_copy);
			break;
		}
		choice = 0;
		cout << "Choose which list you want to see: " << endl;
		cout << "1 - Default list" << endl << "2 - Sorted list" << endl;
		cin >> choice;
		if (choice == 1)
		{
			printPage(list, number);
			printMenu(list, list_copy);
			break;
		}
		else if (choice == 2)
		{
			if (sortdetected == 1)
			{
				printPage(list_copy, number);
				printMenu(list, list_copy);
				break;
			}
			else
			{
				digitalSort(list_copy->head);
				printPage(list_copy, number);
				printMenu(list, list_copy);
				break;
			}
		}
	}
		break;
	case 3:
		system("cls");
		cout << "Starting sort.." << endl;
		if (sortdetected == true)
		{
			cout << "You can't sort list twice!" << endl;
			system("pause");
			printMenu(list, list_copy);
			break;
		}
		else {
			digitalSort(list_copy->head);
			cout << "Sort complete!" << endl;

			system("pause");
			printMenu(list, list_copy);
			break;
		}	
	case 4:
		system("cls");
		{
			char key[4];
			cout << "Enter the search key.." << endl;
			cin >> key;

			Queue* search = new Queue;
			search->head = nullptr;
			search->tail = nullptr;
 			search = BinSearch(&list_copy->head, key);
			if (search->head == nullptr)
			{
				cout << "There's nothin to look at!" << endl;
				system("pause");
				printMenu(list, list_copy);
				break;
			}
			Node** IAFT = new Node*[queue_count];
			for (int i = 0; i < queue_count; i++)
			{
				IAFT[i] = new Node;
			}
			Node* current = new Node(*search->head);
			Vertex* Root = nullptr;
			int index = 0;

			int* arr_random = new int[queue_count];
			for (int i = 0; i < queue_count; i++) {
				arr_random[i] = rand() % 100;
			}

			while (current != nullptr && index < queue_count)
			{
				IAFT[index] = current;
				dop_a1(Root, IAFT[index], arr_random[index]);
				current = current->next;
				index++;
			}

			
			intBubbleSort(arr_random, queue_count);

			while (search->head != nullptr)
			{
				cout <<
					search->head->name_info << "\t" <<
					search->head->street << "\t" <<
					search->head->house_num << "\t" <<
					search->head->room_num << "\t" <<
					search->head->date << endl;
				popQ(*search);
			}
			system("pause");
			system("cls");
			LRprint(Root);
		}
		system("pause");
		printMenu(list, list_copy);
		break;
		

	case 5:
		system("cls");

		cout << "Exiting the programm.." << endl;

		break;
	default:

		printMenu(list, list_copy);

		break;
	}
}