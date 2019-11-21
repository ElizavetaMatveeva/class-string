#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <string.h>
using namespace std;

class string_s{
public:
	string_s(const char* s1) ; // Конструктор с параметром
	string_s(); // Конструктор по умолчанию
	string_s(const string_s& a); // Копирующий конструктор для строки-объекта класса
	string_s& strcat_s(const string_s& a); // Функция сцепления строк
	string_s& strcpy_s(const string_s&  a); // Копирование строк из объекта в объект
	int strcmp_s(const string_s&  a); // Сравнение строк
	int strlen_s(); // Вычисление длины строки
	string_s& strstr_s(const string_s& a, const string_s& b); //  Функция поиска подстроки в строке
	void print_s() const; // Функция печати строки
	~string_s() { delete []s; } // Деструктор
private:
	char* s;
	int sz;	
};

string_s::string_s (const char* s1){ // Конструктор с параметром(преобразующий)
	sz=strlen(s1) + 1; // Задаётся размер массива (длина строки+символ конца строки)
	s=new char[sz]; // Создаётся массив нужного размера
	assert(s!=0); // Проверяется, выделилась ли память
	strcpy(s, s1); // Строка копируется в массив класса
}

string_s::string_s(const string_s& a){ // Копирующий конструктор для строки-объекта класса
	sz=a.sz; // Значение размера переносится из одного объекта в другой
	s=new char[sz]; // Создаётся массив нужного размера
	strcpy(s, a.s); // Копируется массив из объекта а в новый объект
}

string_s::string_s() { // Конструктор по умолчанию
	s=new char[1]; 
	s='\0'; 
	sz=0; 
}

string_s& string_s::strcat_s(const string_s& a){ // Функция сцепления строк
	sz+=(a.sz)-1; // Записывается новое значение размера массива
	char* t=new char[sz]; // Создаётся массив размера, необходимого для вмещения двух строк
	strcpy(t, s); // В созданный массив копируется массив объекта
	strcat(t, a.s); // Массив объекта сцепляется с массивом другого объекта
	delete []s; // Освобождается память 
	s=t;
	return *this;
}

string_s& string_s::strcpy_s(const string_s& a){ // Копирование строки в объект
	if (this!=&a){ // Если копируется одна и та же строка, следующие действия не выполняются
		sz=a.sz; // Записывается новое значение размера массива
		char* t=new char[sz]; // Создаётся новый массив нужного размера
		strcpy(t, a.s); // На новое место копируется массив
		delete []s; // Освобождается память 
		s=t;
	}
	return *this;
}

int string_s::strcmp_s(const string_s&  a){ // Сравнение строк
	if (this==&a) 
		return 0;
	else
		return strcmp(s, a.s);
}

int string_s::strlen_s(){ // Вычисление длины строки
	return sz-1;
}

string_s& string_s::strstr_s(const string_s&  a, const string_s& b){ // Функция поиска подстроки в строке
	char* t=strstr(a.s, b.s);  // Ищется подстрока из 2-го объекта
	if (t) { // Если строка была найдена, выполняются следующие действия
       sz=strlen(t)+1; // Изменяется значение размера массива
       char* t1=new char[sz]; // Выделяется память
       strcpy(t1, t);
	   delete []s;
       s=t1;
    }
    else { 
        t=new char[1];
        t[0]='\0';
        sz=1;
        delete []s;
        s=t;
    }
    return *this;
}

void string_s::print_s() const { // Функция печати строки
	cout << s << endl;
}

int main(){ 
	cout<<"Constructor with parameter:"<<endl; // Вызов конструктора с параметром
	string_s a("Hello world!"); 
	a.print_s();
	string_s d("Good morning!");
	d.print_s();
	string_s b; // Вызов конструктора без параметра
	cout<<"Copy constructor:"<<endl;
	string_s c(a); // Вызов копирующего конструктора 
	c.print_s();
	cout<<"StrCat:"<<endl; 
	a.strcat_s(d).print_s(); // Пример работы функции сцепления с объектом
	d.strcat_s("It's cloudly today").print_s(); // Пример работы функции сцепления со строкой-параметром
	cout<<"String Copy:"<<endl; 
	b.strcpy_s(d).print_s(); // Пример работы функции копирования с объектом класса
	a.strcpy_s("Hi, how are you?").print_s(); // Пример работы функции копирования со строкой-параметром
	cout<<a.strlen_s()<<endl; // Функция, определяющая длину строки
	cout<<b.strcmp_s(a)<<endl;  // Сравнение строки-объекта класса и строки-параметра
	string_s n;
	n.strstr_s(a, "how").print_s(); // Поиск подстроки-параметра в строке объекта
	system("pause");
}
