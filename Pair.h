#pragma once

template<typename TKey, typename TValue>
class Pair
{
private:
	TKey key;
	TValue value;
public:
	// ������������
	Pair(const Pair<TKey, TValue>& pair)
	{
		this->key = pair.key;
		this->value = pair.value;
	}
	Pair(const TKey& key, const TValue& value)
	{
		this->key = key;
		this->value = value;
	}
public:
	// ������������
	TKey GetKey() { return this->key; }
	TValue GetValue() { return this->value; }
public:
	// ������
	void SetValue(const TValue& value)
	{
		this->value = value;
	};
public:
	friend bool operator==(const Pair<TKey, TValue>& pair1, const Pair<TKey, TValue>& pair2)
	{
		if (pair1.GetKey() == pair2.GetKey() && pair1.GetValue() == pair2.GetValue())
			return true;
		return false;
	}
};