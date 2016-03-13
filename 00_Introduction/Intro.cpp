#include<iostream>
#include<string>
#include<vector>

using namespace std;

// Chapter 0 Introduction
class Widget{
	int size;
public:
	Widget(){ // Default constructor
		size = 1; 
	};
	Widget(const Widget& rhs){ // Copy constructor
		size = rhs.size;
	};
	Widget& operator=(const Widget& rhs){ // Copy assingnment operator
		size = rhs.size;
		return *this;
	};
};

// Chapter 3 Use const whenever possible
class TextBlock{
public:
	TextBlock(const char* str):text(string(str))
	{
		lengthIsValid = false;
	};
	const char& operator[](size_t position) const // returns ref so that tb[0]='a' work; Note the const and non-const versions
	{ 
		return text[position];
	};
	char& operator[](size_t position) // Non-const version
	{ 
		//return text[position];
		return const_cast<char&>(
			(static_cast<const TextBlock&>(*this))
				[position]);
	};
	size_t length() const // mutable textLength is needed to change its value via a const length() fn
	{
		if(!lengthIsValid)
		{
			textLength = text.length();
			lengthIsValid = true;
		}
		return textLength;
	};
private:
	string text;
	mutable size_t textLength; // Since mutable even const member functions can change this field
	mutable bool lengthIsValid;
};




// Chapter 5 Constructors, Destructors, Assignment Operators
template<typename T> 
class NamedObject{
public:
	NamedObject(const char* name, const T& value):nameValue(name), objectValue(value){};
	NamedObject(const string& name, const T& value):nameValue(name), objectValue(value){};
private:
	string nameValue;
	T objectValue;
};

int main()
{
// Chapter 0 Introduction
	Widget w1;
	Widget w2(w1);
	Widget w3 = w2;
	w1 = w2;

// Chapter 1 Prefer consts, enums, inlines, #defines
	char* authorName = "Scott Meyers";
	// authorName[1] = 'a'; Error

// Chapter 3 Use const whenver possible
	char greeting[] = "Hello";
	char* p1 = greeting;
	const char* p2 = greeting;
	char* const p3 = greeting;
	const char* const p4 = greeting;
	char greeting2[] = "My!";
	p2 = greeting2; // Error for p3 and p4
	greeting[1] = 'a'; // Hello -> Hallo

	vector<int> vec(5,10);
	const vector<int>::iterator iter = vec.begin(); // iterator is constant
	*iter = 9;
	// ++iter; Error
	vector<int>::const_iterator cIter = vec.begin(); // data is constant
	//*cIter = 10 Error
	++cIter;

	TextBlock tb("Hello");
	cout << tb[0];
	tb[0] = 'x';
	int l = tb.length();

	const TextBlock ctb("Hello");
	cout << ctb[0];
	// ctb[0] = 'x'; Error: textblock cannot be modified



// Chapter 5 Constructors, Destructors, Assignment Operators
	string str = "Smallest Prime Number";
	char ch[] = "hello";
	string st = string(ch);
	NamedObject<int> no1("Smallest", 2);


}