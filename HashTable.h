#pragma once

#include "IHashTable.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Pair.h"


template<class TKey, class TValue>
class HashTable : IHashTable<TKey, TValue>
{
private:
	struct Record
	{
		TKey key;
		TValue data;
		bool status;
	};
private:
	ArraySequence<Record*>* data;
	int capacity;
	int count;
protected:
	// Хеш-функция
	int GetHashCode(const TKey key, const int step = 0) const
	{
		int hash_1 = key % capacity;
		int hash_2 = 1 + key % (capacity - 1);
		return (hash_1 + step * hash_2) % capacity;
	}
public:
	HashTable(const int capacity);
	HashTable(const HashTable& hash_table);
public:
	virtual int GetCount() const override;
	virtual int GetCapacity() const override;
	virtual TValue Get(TKey key) const override;
	virtual bool Find(TKey key) const override;
public:
	virtual bool Add(TKey key, TValue value) override;
	virtual bool Remove(TKey key) override;
	virtual void Resize() override {};
	virtual void Rehash() override;
public:
	~HashTable()
	{
		delete data;
	}
};


template<class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(const int capacity) : count(0)
{
	int digit = capacity;
	
	if (digit > 1)
	{
		while(digit % 2 == 0 && digit != 1)
		{
			digit /= 2;
		}
	}
	else
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	if(digit != 1)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->capacity = capacity;
	this->data = new ArraySequence<Record*>(capacity);
}


template<class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(const HashTable& hash_table)
{
	int digit = hash_table.capacity;
	
	if (digit > 1)
	{
		while (digit % 2 == 0 && digit != 1)
		{
			digit /= 2;
		}
	}
	else
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	if (digit != 1)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	
	this->count = hash_table.count;
	this->capacity = hash_table.capacity;
	this->data = new ArraySequence<Record*>(*hash_table.data);
}



template<class TKey, class TValue>
int HashTable<TKey, TValue>::GetCount() const 
{ 
	return this->count; 
};


template<class TKey, class TValue>
int HashTable<TKey, TValue>::GetCapacity() const 
{ 
	return this->capacity; 
};


template<class TKey, class TValue>
TValue HashTable<TKey, TValue>::Get(TKey key) const
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 1; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i);
	}
	if (i >= this->data->GetLength() || !this->data->HasValue(index))
	{
		throw NoneValue("***ValueError: there is not value of argument in the hash table***", __FILE__, __LINE__);
	}
	else
		return record->data;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Find(TKey key) const
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 1; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i);
	}

	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (i < this->data->GetLength())
		{
			for (index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
			{
				record = this->data->Get(index);
				if (record->key == key)
					break;
			};
			if (i < this->data->GetLength() && this->data->HasValue(index))
				return true;
		}
	}
	else
		return true;

	return false;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Add(TKey key, TValue value)
{
	int index = this->GetHashCode(key);
	Record* new_record = new Record({ key, value, true });
	Record* record;
	int i;

	for (i = 1; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i);
	}

	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (i < this->data->GetLength())
		{
			this->count++;
			this->data->Set(index, new_record);
			return true;
		}	
		else
		{
			for (int index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
			{ };
			if(index < this->data->GetLength() && !this->data->HasValue(index))
			{ 
				this->count++;
				this->data->Set(index, new_record);
				return true;
			}
		}
	}
	else
		return false;

	return false;
	/*
		Resize
	*/
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Remove(TKey key)
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 1; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i);
	}

	if (i < this->data->GetLength() && this->data->HasValue(index))
	{
		record->status = false;
		this->Rehash();
		return true;
	}

	return false;

	/*
		Resize
	*/
}


template<class TKey, class TValue>
void HashTable<TKey, TValue>::Rehash()
{
	this->count = 0;

	ArraySequence<Record*>* new_data = new ArraySequence<Record*>(capacity);
	Record* record;
	Record* new_record = nullptr;
	int index;
	int key;

	for (int i = 0; i < this->data->GetLength(); i++)
	{
		if (this->data->HasValue(i) && this->data->Get(i)->status)
		{
			record = this->data->Get(i);
			key = record->key;
			index = this->GetHashCode(key);
			int i;

			for (i = 1; i < new_data->GetLength() && new_data->HasValue(index); i++)
			{
				new_record = new_data->Get(index);
				if (new_record->key == key)
					break;

				index = this->GetHashCode(key, i);
			}

			if (!(i < new_data->GetLength() && new_data->HasValue(index)))
			{
				if (i < new_data->GetLength())
				{
					this->count++;
					new_data->Set(index, record);
				}
				else
				{
					for (index = 0; index < new_data->GetLength() && new_data->HasValue(index); index++)
					{ };
					if (index < new_data->GetLength() && !new_data->HasValue(index))
					{
						this->count++;
						new_data->Set(index, new_record);
					}
				}
			}

		}
	}
	delete this->data;
	this->data = new_data;
}
