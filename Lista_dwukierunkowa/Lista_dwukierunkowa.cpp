#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
// m - iloœæ liczb w liœcie
// n - wybrany element z listy
// k - o ile miejsc ma zostaæ przesuniêty
// kier - kierunek w którym przesuwamy ( p - w prawo) jeœli inne niz p to w lewo
using namespace std;

struct Node
{
	Node* prev;
	Node* next;
	int data;

	Node()              // konstruktor domyœlny
	{
		prev = nullptr;
		next = nullptr;

	}
	Node(Node*prev, Node*next, int data)
	{
		this->prev = prev;
		this->next = next;
		this->data = data;
	}

};

struct List
{
	private :
		Node* head, *tail;
		int size;
	public:
		List()                  // konstruktor domyœlny
		{
			head = nullptr;
			tail = nullptr;
			size = 0;
		}

		void insert();
		void move(int position,char direction,int shift);
		void print();
};

void List::insert()
{
	int value = 0;
	Node*temp;
	if (head == nullptr)
	{
		value = rand();
		head = new Node(nullptr, nullptr, value);
		head->next = head;
		tail = head;
	}
	else
	{
		temp = head;
		value = rand();
		while (temp->next != head)
			temp = temp->next;
		temp->next = new Node(temp, head, value);
		tail = temp->next;
		head->prev = tail;
	}
	size++;
}

void List::move(int position, char direction, int shift)
{
	if ((shift% size)==0) return;	//cykl - lista nie ulega zmianie

	Node*temp,*temp2,*temp3,*par;
	if (direction == 'p')
	{
		temp = head;
		for (int i = 1; i < position; i++)
			temp = temp->next;
		par = temp->prev;
		par->next = temp->next;
		temp->next->prev = par;
		if (temp == head)
			head = temp->next;
		else if (temp == tail)
			tail = par;
		temp2 = temp;
		temp3 = head;
		if ((shift + position) == size)
		{
			tail->next = temp2;
			temp2->next = head;
			head->prev = temp2;
			return;
		}
		for (int i = 1; i < (position + shift)%size; i++)
		{
			temp3 = temp3->next;

		}

		par = temp3->prev;
		temp2->prev = par;
		temp2->next = temp3;
		par->next = temp2;
		if (temp3 == head)
			head = temp2;
	}
	else
	{
		temp = tail;
		for (int i = position; i > 1; i--)
			temp = temp->prev;
		par = temp->prev;
		par->next = temp->next;
		temp->next->prev = par;
		if (temp == head)
			head = temp->next;
		else if (temp == tail)
			tail = par;

		temp2 = temp;
		temp3 = tail;
		if ((shift + position) == size)
		{
			temp2->next = head;
			head = temp2;
			tail->next = temp2;
			head->prev = tail;
			return;
		}

		for (int i = 2; i < (position + shift) % size; i++)
		{
			temp3 = temp3->prev;

		}
		if (temp3 == tail)
		{
			tail->next = temp2;
			temp2->prev = tail;
			tail = temp2;
			tail->next = head;
			return;
		}
		if (temp3 == head)
		{
			temp2->next = head;
			head->prev = temp2;
			head = temp2;
			temp2->prev = tail;
			tail->next = head;
			return;
		}

		par = temp3->prev;
		temp2->prev = par;
		temp2->next = temp3;
		par->next = temp2;

	}


}

void List::print()
{
	Node*temp = head;
	do
	{
		cout << temp->data << " ";
		temp = temp->next;
	} while (temp != head);
}

int main()
{
	int m, n, k;
	char kier;
	srand(time(NULL));
	List*list = new List;
	cout << "m= ";
	cin >> m;
	cout << endl<<"n= ";
	cin >> n;
	for (int i = 0; i < m; i++)
		list->insert();
	list->print();
	cout << endl;
	cout << "k=";
	cin >> k;
	cout << endl << "kier=";
	cin >> kier;
	list->move(n, kier, k);
	cout << endl;
	list->print();
	cout << endl;
	system("pause");
	return 0;
}
