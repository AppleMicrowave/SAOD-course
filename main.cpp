#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
using namespace std;

#define N 4000

bool sortdetected, flag;
const int m = 256;

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
Node** index = new Node* [N];

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
	int weight;
	int balance;
};	
Vertex* Root = nullptr;

struct Symbol {
	double probability;
	double cumulative_probability;
	int code_length;
	int code[m];
	char symbol;
};


//List
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

//Queue
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
		cout << "Queue is empty!" << endl;
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

//Sort
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

//Binary Search
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

//Tree
void PrintTree(Vertex* p) {
	if (p != nullptr) {
		PrintTree(p->left);
		cout << p->data->name_info << "\t"
			<< p->data->street << "\t"
			<< p->data->house_num << "\t"
			<< p->data->room_num << "\t"
			<< p->data->date << endl;
		PrintTree(p->next);
		PrintTree(p->right);
	}
}

void SearchTree(Vertex* p, char* data) {
	if (p != nullptr) {
		SearchTree(p->left, data);

		if (strncmp(p->data->name_info, data, 3) == 0) {
			cout <<
				p->data->name_info << "\t" <<
				p->data->street << "\t" <<
				p->data->house_num << "\t" <<
				p->data->room_num << "\t" <<
				p->data->date << endl;
		}

		SearchTree(p->next, data);
		SearchTree(p->right, data);
	}
}

void delete_tree(Vertex*& p) {
	if (p != NULL) {
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

void add_tree(Vertex*& p, Node* data, int w) {
	if (p == nullptr) {
		p = new Vertex;
		p->data = data;
		p->weight = w;
		p->left = nullptr;
		p->right = nullptr;
		p->next = nullptr;
	}
	else if (strncmp(p->data->name_info, data->name_info, 10) < 0) {
		add_tree(p->right, data, w);
		}
	else if (strncmp(p->data->name_info, data->name_info, 10) > 0) {
		add_tree(p->left, data, w);
	}
	else if (strncmp(p->data->name_info, data->name_info, 10) == 0) {
		add_tree(p->next, data, w);
	}
}

//Coding
void insertionSortForCoding(Symbol* symbols, int alphabet_size) {
	int i, j;
	Symbol key;
	for (i = 1; i < alphabet_size; i++) {
		key = symbols[i];
		j = i - 1;
		while (j >= 0 && symbols[j].probability < key.probability) {
			symbols[j + 1] = symbols[j];
			j = j - 1;
		}
		symbols[j + 1] = key;
	}
}

void gilbertMooreCoding(Symbol* symbols, int alphabet_size) {
	double pr = 0;
	for (int i = 0; i < alphabet_size; ++i) {
		symbols[i].cumulative_probability = pr + symbols[i].probability / 2;
		pr += symbols[i].probability;
		symbols[i].code_length = -log2(symbols[i].probability) + 1;
		for (int j = 0; j < symbols[i].code_length; ++j) {
			symbols[i].cumulative_probability *= 2;
			symbols[i].code[j] = (int)symbols[i].cumulative_probability;
			if (symbols[i].cumulative_probability > 1) {
				symbols[i].cumulative_probability -= 1;
			}
		}
	}
}

void calculateEntropyAndAverageCodeLength(Symbol* symbols, int alphabet_size) {
	double entropy = 0;
	double average_code_length = 0;
	for (int i = 0; i < alphabet_size; ++i) {
		entropy -= symbols[i].probability * log2(symbols[i].probability);
		average_code_length += symbols[i].code_length * symbols[i].probability;
	}
	printf("Entropy: %f\n", entropy);
	printf("Average code length: %f\n\n", average_code_length);
}

void codingInteraction() {
	SetConsoleCP(866);
	FILE* file = NULL;
	fopen_s(&file, "base.dat", "rb");
	system("cls");
	if (file == NULL) {
		printf("Cannot open the file!\n");
		system("pause");
		return;
	}
	int frequencies[m] = { 0 };
	int total = 0;
	char ch;
	while (fread(&ch, sizeof(char), 1, file)) {
		frequencies[(unsigned char)ch]++;
		total++;
	}
	fclose(file);
	Symbol symbols[m];
	int alphabet_size = 0;
	for (int i = 0; i < m; ++i) {
		if (frequencies[i] > 0) {
			symbols[alphabet_size].symbol = (char)i;
			symbols[alphabet_size].probability = (double)frequencies[i] / total;
			alphabet_size++;
		}
	}
	insertionSortForCoding(symbols, alphabet_size);
	gilbertMooreCoding(symbols, alphabet_size);

	printf("-A------P---------------L-------Codeword-----Frequency\n");
	for (int i = 0; i < alphabet_size; ++i) {
		printf(" [%c]\t", symbols[i].symbol);
		printf("%f\t", symbols[i].probability);
		printf("%i\t", symbols[i].code_length);
		for (int j = 0; j < symbols[i].code_length; ++j) {
			printf("%d", symbols[i].code[j]);
		}
		printf("\t%d\n", frequencies[(unsigned char)symbols[i].symbol]);
	}
	printf("---------------------------------------------\n");

	calculateEntropyAndAverageCodeLength(symbols, alphabet_size);
}

//Menu
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
	char key[4];

	cout << "Choose the option: " << endl << endl;
	cout << "1 - Show all database." << endl;
	cout << "2 - Show specific page." << endl;
	cout << "3 - Start the sort." << endl;
	cout << "4 - Initialize key search." << endl;
	cout << "5 - Initizlize tree search." << endl;
	cout << "6 - Procedure Coding." << endl;
	cout << "7 - Exit the programm." << endl;
	

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
			
			int intkey = 0;
			int i = 0;
			cout << "Enter the search key.." << endl;
			cin >> key;

			queue_count = 0;
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

			Node* arr = new Node[queue_count];
			Node* current = new Node(*search->head);

			int* Weight = new int[queue_count];

			for (i = 0; i < queue_count; i++) {
				Weight[i] = rand() % 99 + 1;
			}
			i = 0;

			intBubbleSort(Weight, queue_count);

			if (Root != nullptr)
			{
				delete_tree(Root);
				Root = nullptr;
			}

			for (i = 0; i < queue_count; i++)
			{
				arr[i] = *current;
				add_tree(Root, &arr[i], Weight[i]);
				current = current->next;
			}
			flag = true;
			cout << "\tName info\t\t" << "  Street\t\t" << "House\t" << "Room\t" << "  Date" << endl << endl;
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
		}
		system("pause");
		printMenu(list, list_copy);
		break;
	case 5:
		if (flag == true){}
		else { cout << "Do the key search first!\n"; system("pause"); printMenu(list, list_copy); break; }
		system("cls");

		cout << "\n\tName info\t\t" << "  Street\t\t" << "House\t" << "Room\t" << "  Date" << endl << endl;
		PrintTree(Root);

		system("pause");
		system("cls");

		cout << "Enter first 3 letters of surname: ";
		cin >> key;
		SearchTree(Root, key);

		system("pause");
		printMenu(list, list_copy);
		break;
	case 6:
		system("cls");

		codingInteraction();

		system("pause");
		printMenu(list, list_copy);
		break;
	case 7:
		system("cls");

		cout << "Exiting the programm.." << endl;

		break;
	default:

		printMenu(list, list_copy);

		break;
	}
}