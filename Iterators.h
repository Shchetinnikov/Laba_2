#pragma once

template<class T>
class Sequence;

template<class T>
class ArraySequence;


template<class T>
class IIterator
{
public: // ��������� ������������ ���������
	virtual T GetValue() const = 0;							 // ������ �������� ��������
	virtual IIterator<T>* Next() = 0; //void ��� bool		 //
	virtual bool HasNext() = 0;						         //
	virtual bool HasValue() = 0;
public:  // ��������� ���������������� ���������
	virtual IIterator<T>* Prev() = 0; //void ��� bool
	virtual bool HasPrev() = 0; 
public:
	virtual IIterator<T>* operator++() { return this->Next(); }
	virtual IIterator<T>* operator++(int) {	return this->Next(); }
	virtual IIterator<T>* operator--() { return this->Prev(); }
	virtual IIterator<T>* operator--(int) { return this->Prev(); }
	virtual IIterator<T>* operator+(int shift) 
	{ 
		IIterator<T>* it;
		for (it = this; shift > 0; shift--)
			it = it->Next();
		return it; 
	}
	virtual IIterator<T>* operator-(int shift)
	{ 
		IIterator<T>* it;
		for (it = this; shift > 0; shift--)
			it = it->Prev();
		return it;
	}

};

//   [ 1, 2, 3, 4, 5]
// -1  0  1  2  3  4
//	^					- �������� � ��������� ������ ������� ����� ���������� � ������. �����

//   []				��� ������ � ����� ��������?
// -1 
//	^					


template<class T>
class IIterable
{
public:
	virtual IIterator<T>* GetIterator() = 0;
};


template<class T>
void IteratorUsageSample()
{
	Sequence<T>* seq = new ArraySequence<T>();
	//
	for (auto iterator = seq->GetIterator(); iterator->HasValue(); iterator->Next())
	{

	}
}


template<class T>
class ArraySequenceIterator : public IIterator<T>
{
private:
	ArraySequence<T>* seq;
	int currentIndex;
public:
	ArraySequenceIterator(ArraySequence<T>* seq)
	{
		this->seq = seq;
		this->currentIndex = 0;
	}
public:
	virtual T GetValue() const override { return this->seq->Get(this->currentIndex); }
	virtual IIterator<T>* Next() override
	{
		this->currentIndex++;
		return this;
	}
	virtual bool HasNext() override { return this->currentIndex < this->seq->GetCapacity() - 1; }
	virtual bool HasValue() override { return this->currentIndex < this->seq->GetLength(); }
public:
	virtual IIterator<T>* Prev() override
	{
		this->currentIndex--;
		return this;
	}
	virtual bool HasPrev() override { return this->currentIndex > 0; }
};