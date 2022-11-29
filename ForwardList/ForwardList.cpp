//ForwardList
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data; // Значение элемента
	Element* pNext; //Адрес следующего элемента
	static unsigned int count; //Количество элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0; //Статическую переменную можно пронициализировать только за перделами класса

class ForwardList
{
	Element* Head; //Указатель на начальный элемент списка
	//Голова является точкой входа в список
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0)
	{
		//Конструктор по умолчанию создает пустой список. 
		//Если голова указывает на 0, список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; // из констрактора копирования dspsdftv jgthfnjh ghbcdfbdfybz
		cout << "copycon: \t " << this << endl;

	}
	ForwardList( ForwardList&& other) :ForwardList()
	{
		*this = std::move(other); //Функция std::move() вызывает MoveAssignment
		cout << "Move Constructor" << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	
	// Operatioons
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		//Deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "copyassign: /t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssign:/t" << this << endl;
		return*this;
	}


	// Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Head = new Element(Data, Head);
		//2) Пристыковываем новый элемент к началу списка
	   // New->pNext = Head;
		//3) Переводим Голову на новый элемент: 
		//Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент
		//2) Доходим до последнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//Итератор указывает на последний элемент списка,
		//и к нему можно пристыковать новый элемент
		//3) Пристегиваем к последнему эл списка новый элемент:
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//1) Создаем новый эл:
		//Element* New = new Element(Data);
		//2) Доходим до нужного эл:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)//Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext);
		//3) Включаем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;

		size++;
	}

	//                  Removing elements:
	void pop_front()
	{
		//1) Сохраняем адрес удаляемого элемента:
		Element* erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete erased;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr) return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем последний эл из памяти:
		delete Temp->pNext;
		//3) Зануляем указатель на следующий элемент:
		Temp->pNext = nullptr;
		size--;
	}



	//                     Methods:
	void print()const
	{
		Element* Temp = Head; //Temp - это итератор. 
		//Итератор - Это указатель, при помощи которого можно получить доступ к элементам структуры данных
		cout << "Head:\t" << Head << endl;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // Переходим на следующий элемент
		}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "\nКол-во эл списка:       " << size << endl;
		cout << "Общее кол-во эл списка: " << Element::count << "\n" << endl;
		
	}

	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//1) Доходим до предыдущего элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//3) Зануляем указатель на следующий элемент:
		Element* erased = Temp->pNext;
		// 4) Сохраняем адрес удаляемого элемента на который указывал предыдущий элемент
		Temp->pNext = erased->pNext;
		//5) Освобождаем данные старого элемента
		delete erased;
		size--;
	}

	void cleaner()
	{
		while (size)
		{
			pop_front();
		}
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left; //copy constructor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}



//#define BASE_CHECK
//#define COUNT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	int index;
	int value;
	cout << "Введите индекс значения добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	/* cout << "Введите индекс значения удаляемого элемента: "; cin >> index;
	 list.erase(index);*/
	list.print();
	cout << "\t\t\tЗАПУСК ДЕСТРУКТОРА\n";
	list.cleaner();
	list.print();

#endif // BASE_CHECK

#ifdef // COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();


	list1 = list1;
	ForwardList list3 = list1 + list2;
	list3.print();


#endif // COUNT_CHECK

	ForwardList list = { 3, 5, 8, 13, 21};
	//range-based for (for для диапазона, то есть, для контейнера)
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

}

