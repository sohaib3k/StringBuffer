#include <iostream>
class StringBuffer {

	//private:
public:
	char* _strbuf;                                   //buffer to store the original string
	int _length;                                       //length of the string
	StringBuffer* next;
	StringBuffer* prev;


public:
	
	StringBuffer();  //default constructor
	StringBuffer(char*, int);   //constructor to convert a char* to StringBuffer
	char charAt(int) const;   //returns the character at the passed index
	int length() const;                            //returns the length of the buffer
	void reserve(int);                             //allocates memory for the string, according to the passed character length
	void append(char);                          //appends a single character at the end
	void StringBuffer::deletebuf();
	StringBuffer* StringBuffer::smartCopy(char*, int);
	void print() { // only for testing purposes

		for (int i = 0; i < _length; i++) {
			std::cout << _strbuf[i];
		}
		std::cout << std::endl;
		std::cout << "Length: " << _length << std::endl;
	}




	StringBuffer& operator=(StringBuffer&b)
	{
		this->_strbuf = b._strbuf;
		this->_length = b._length;
		this->next = this;
		this->prev = this;

		//Implementing doubly linked list for reference linkage
		(const_cast<StringBuffer*>(&b))->next = this;

		this->prev = (const_cast<StringBuffer*>(&b));

	}


	StringBuffer(const StringBuffer&b){
		this->_strbuf = b._strbuf;
		this->next = this;
		this->prev = this;
		this->_length = b._length;
		//Implementing doubly linked list for reference linkage
		(const_cast<StringBuffer*>(&b))->next = this;

		this->prev = (const_cast<StringBuffer*>(&b));



	}

	~StringBuffer() { //destructor; would delete the allocated buffer
		if (this->prev){
			this->prev->next = this->prev;
		}
		if (this->next){
			this->next->prev = this->next;
		}
		if (this->next == this && this->prev == this){
			delete this->_strbuf;
		}
	}
};






StringBuffer::StringBuffer() {
	_strbuf = new char();
	_length = 0;
	next = this;
	prev = this;
}

StringBuffer::StringBuffer(char* newString, int length) { //constructor to convert a char* to 
	this->_strbuf = new char[length];
	for (int i = 0; i < length; i++){
		this->_strbuf[i] = newString[i];
	}
	this->_length = length;
	next = this;
	prev = this;
}

char StringBuffer::charAt(int index) const { //returns the character at the passed index


	if (_length == 0 || index >= _length || index < 0) {
		std::cout << "Invalid index accessed." << std::endl;
		return ' ';

	}
	else
		return _strbuf[index];

}

int StringBuffer::length() const { //returns the length of the buffer
	return _length;
}

void StringBuffer::reserve(int length) { //allocates memory for the string, according to the passed character length

	char* mystring = new char[length];

	delete[] _strbuf;
	_strbuf = new char[length];
	_length = length;
	for (int i = 0; i < _length; i++)
	{
		_strbuf[i] = mystring[i];
	}
	delete[] mystring;

}
StringBuffer* StringBuffer::smartCopy(char* newString, int length) {
	StringBuffer *temp = new StringBuffer();
	temp->_length = length;
	int it = 0;
	temp->reserve(length);
	for (int i = 0; i < temp->_length; i++)
	{
		temp->_strbuf[i] = newString[i];
	}
	temp->next = temp;
	temp->prev = temp;
	return temp;
}

void StringBuffer::append(char newChar) { //appends a single character at the end


	if (this->next == this && this->prev == this){

		char* mystring = new char[_length + 1];
		for (int i = 0; i < _length; i++)
		{
			mystring[i] = _strbuf[i];
		}
		mystring[_length] = newChar;
		deletebuf();
		_strbuf = new char[_length + 1];
		_length++;
		for (int i = 0; i < _length; i++)
		{
			_strbuf[i] = mystring[i];
		}
		delete[] mystring;

	}
	else{

		if (this->prev){
			this->prev->next = this->prev;
		}
		if (this->next){
			this->next->prev = this->next;
		}

		StringBuffer *temp = smartCopy(this->_strbuf, this->_length);

		char* mystring = new char[temp->_length + 1];
		for (int i = 0; i < temp->_length; i++)
		{
			mystring[i] = temp->_strbuf[i];
		}
		mystring[temp->_length] = newChar;
		delete[] temp->_strbuf;
		temp->_strbuf = new char[temp->_length + 1];
		temp->_length++;
		for (int i = 0; i < temp->_length; i++)
		{
			temp->_strbuf[i] = mystring[i];
		}
		delete[] mystring;

		this->next = this;
		this->prev = this;
		this->_strbuf = temp->_strbuf;
		this->_length = temp->_length;
	}

}
