#pragma once

#include "../list/array_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Utriedena sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SortedSequenceTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		SortedSequenceTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> SortedSequenceTable, z ktorej sa prevezmu vlastnosti. </param>
		SortedSequenceTable(SortedSequenceTable<K, T>& other);

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

	protected:
		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		TableItem<K, T>* findTableItem(const K& key) override;

		//SequenceTable<K, T> assignSequenceTable(SequenceTable<K, T>& other);

	private:
		/// <summary> Najde index prvku s danym klucom. Kontroluje rozsah [indexStart, indexEnd). Pracuje na principe bisekcie. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "indexStart"> Pociatocny index prehladavanej sekvencie. </param>
		/// <param name = "indexEnd"> Koncovy index prehladavanej sekvencie. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Index prvku s danym klucom. Ak sa kluc v tabulke nenachadza, vrati index, kde by sa mal prvok s takym klucom nachadzat. </returns>
		int indexOfKey(K key, int indexStart, int indexEnd, bool& found);
	};

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable() :
		SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable(SortedSequenceTable<K, T>& other) :
		SortedSequenceTable()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline bool SortedSequenceTable<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equals(dynamic_cast<SortedSequenceTable<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void SortedSequenceTable<K, T>::insert(const K& key, const T& data)
	{
		//TODO 08: SortedSequenceTable

		bool found = false;
		int index = this->indexOfKey(key, 0, this->size() - 1, found);

		if (!found) {
			SequenceTable<K, T>::list_->insert(new TableItem<K, T>(key, data), index);
		}
		else {
			throw std::logic_error("SequenceTable<K, T>::insert : Data with thath key aleready exists!");
		}
		//throw std::runtime_error("SortedSequenceTable<K, T>::insert: Not implemented yet.");
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SortedSequenceTable<K, T>::findTableItem(const K& key)
	{
		//TODO 08: SortedSequenceTable

		bool found = false;
		int index = this->indexOfKey(key, 0, this->size() - 1, found);

		return found ? SequenceTable<K, T>::list_->at(index) : nullptr;
		//throw std::runtime_error("SortedSequenceTable<K, T>::findTableItem: Not implemented yet.");
	}


	template<typename K, typename T>
	inline int SortedSequenceTable<K, T>::indexOfKey(K key, int indexStart, int indexEnd, bool& found)
	{
		//TODO 08: SortedSequenceTable
		//ked neexituje kluc  tabulke tak porovnajte kluc na indexe
		// kluc z parametra k^t
		// k^i > K^P vrat index
		// k^p > k^i vrat index + 1
		if (indexEnd == -1) {
			found = false;
			return 0;
		}


		int indexMiddle = (indexStart + indexEnd) / 2;
		K keyMiddle = SequenceTable<K, T>::list_->at(indexMiddle)->getKey();

		if (keyMiddle == key) {
			found = true;
			return indexMiddle;
		}
		else {
			if (indexStart == indexEnd) {
				found = false;
				return key < keyMiddle ? indexMiddle : indexMiddle + 1;
			}
			else {
				if (key < keyMiddle) {
					found = false;
					return indexOfKey(key, indexStart, indexMiddle, found);
				}
				else {
					return indexOfKey(key, indexMiddle + 1, indexEnd, found);
				}
			}
		}
		//throw std::runtime_error("SortedSequenceTable<K, T>::indexOfKey: Not implemented yet.");
	}
}