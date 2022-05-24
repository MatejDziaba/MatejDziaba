#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>
#include <iostream>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		/// <summary> Konstruktor s danou velkostou n. </summary>
		PriorityQueueTwoLists(T size);

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vrati velkost kapacity v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size_short_list_getCapacity();

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size_short_list_getCurrentCapacity();

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size_long_list();

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		void setCapacityShortList(bool& capacity_success);

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		PriorityQueueLinkedList<T>* longList_;

		bool full_shortList_;
		size_t min_priority_shortList_ = 0;
		size_t min_priority_longList_ = 0;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new PriorityQueueLinkedList<T>())
	{
	}

	template<typename T>
	inline PriorityQueueTwoLists<T>::PriorityQueueTwoLists(T size) :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>(size)),
		longList_(new PriorityQueueLinkedList<T>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		//TODO 06: PriorityQueueTwoLists
		this->clear();
		this->full_shortList_ = nullptr;
		this->min_priority_shortList_ = 0;
		this->min_priority_longList_ = 0;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		//TODO 06: PriorityQueueTwoLists
		PriorityQueueTwoLists<T>* otherTwoLists = dynamic_cast<PriorityQueueTwoLists<T>*>(&other);
		if (otherTwoLists == nullptr) {
			throw std::logic_error("PriorityQueueTwoLists<T>::assign : other je nullptr");
		}
		this->shortList_->assign(*(otherTwoLists->shortList_));  // vykonava sa clear()
		this->longList_->assign(*(otherTwoLists->longList_));   // vykonava sa clear()

		this->full_shortList_ = otherTwoLists->full_shortList_;
		this->min_priority_shortList_ = otherTwoLists->min_priority_shortList_;
		this->min_priority_longList_ = otherTwoLists->min_priority_longList_;

		return *this;
		//throw std::runtime_error("PriorityQueueTwoLists<T>::assign: Not implemented yet.");
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		//TODO 06: PriorityQueueTwoLists
		size_t cur_size = this->shortList_->getCurCapacity() + this->size_long_list();
		return cur_size;
		//throw std::runtime_error("PriorityQueueTwoLists<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::size_short_list_getCapacity()
	{
		return this->shortList_->getCapacity();
	}

	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::size_short_list_getCurrentCapacity()
	{
		return this->shortList_->getCurCapacity();
	}

	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::size_long_list()
	{
		return this->longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		//TODO 06: PriorityQueueTwoLists
		this->shortList_->clear();
		delete this->shortList_;

		this->longList_->clear();
		delete this->longList_;

		this->shortList_ = nullptr;
		this->longList_ = nullptr;
		//throw std::runtime_error("PriorityQueueTwoLists<T>::clear: Not implemented yet.");
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{

		//TODO 06: PriorityQueueTwoLists
		if (this->shortList_->getCurCapacity() < this->shortList_->getCapacity())
		{
			if (this->min_priority_shortList_ < priority) {
				this->min_priority_shortList_ = priority;
			}
			this->shortList_->push(priority, data);

		}
		else if (this->shortList_->getCurCapacity() == this->shortList_->getCapacity()
			&& this->min_priority_shortList_ > priority)
		{
			this->min_priority_shortList_ = priority;
			this->full_shortList_ = true;
			this->shortList_->pushAndRemove(priority, data);
		}
		else if (this->shortList_->getCurCapacity() == this->shortList_->getCapacity()
			&& this->min_priority_shortList_ < priority)
		{
			if (this->min_priority_longList_ > priority) {
				this->min_priority_longList_ = priority;
			}
			this->full_shortList_ = true;
			this->longList_->push(priority, data);
		}
		
		//throw std::runtime_error("PriorityQueueTwoLists<T>::push: Not implemented yet.");
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		//TODO 06: PriorityQueueTwoLists
		
			
		if (this->shortList_->size() > 0) 
		{
			T returnValue = this->shortList_->pop();

			if (this->shortList_->size() == 0
				&& this->longList_->size() > 0)
			{
				bool capacity_success = false;
				setCapacityShortList(capacity_success);
				
				if (capacity_success == true || capacity_success == false)
				{
					PriorityQueueLinkedList<T>* otherLongList = new PriorityQueueLinkedList<T>();
					otherLongList->assign(*(this->longList_));
					if (otherLongList == nullptr) {
						throw std::logic_error("PriorityQueueTwoLists<T>::pop(): otherLongList je null");
					}
					size_t pocetPrvkovLongList = this->longList_->size();
					//T returnValue = this->shortList_->pop();

					for (size_t i = 0; i < pocetPrvkovLongList; i++)
					{
						if (this->longList_->size() == 0
							|| this->shortList_->size() == this->shortList_->getCapacity())
						{
							delete this->longList_;
							this->longList_ = otherLongList;
							return returnValue;
						}

						int priority = otherLongList->peekPriority();
						T data = otherLongList->pop();

						this->shortList_->push(priority, data);   // v push sa kontroluje a ide to pushAndRemove()
					}
					//his->longList_->assign(*otherLongList);
					delete this->longList_;
					this->longList_ = otherLongList;
					return returnValue;
				}
				else if (capacity_success == false) {
					throw std::logic_error("PriorityQueueTwoLists<T>::pop: capacity_success je false, nepreslo nastavenie kacapity short listu");
				}

			}
			
			return returnValue;
		}
		else {
			throw std::logic_error("PriorityQueueTwoLists<T>::pop: Dvojzoznam je prazdny.");
		}
		
		//throw std::runtime_error("PriorityQueueTwoLists<T>::pop: Not implemented yet.");
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::setCapacityShortList(bool& capacity_success)
	{
		size_t capacity = round(sqrt(this->longList_->size()));

		if (capacity > 4) {
			capacity_success = this->shortList_->trySetCapacity(capacity);
		}
		else {
			capacity_success = this->shortList_->trySetCapacity(4);
		}

	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		//TODO 06: PriorityQueueTwoLists
		if (this->shortList_->size() > 0) {
			return this->shortList_->peek();
		}
		else {
			throw std::logic_error("PriorityQueueTwoLists<T>::peek(): Zoznam je prazdny");
		}

		//throw std::runtime_error("PriorityQueueTwoLists<T>::peek: Not implemented yet.");
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		//TODO 06: PriorityQueueTwoLists
		if (this->shortList_->size() > 0) {
			return this->shortList_->peekPriority();
		}
		else {
			throw std::logic_error("PriorityQueueTwoLists<T>::peekPriority(): Zoznam je prazdny");
		}
		//throw std::runtime_error("PriorityQueueTwoLists<T>::peekPriority: Not implemented yet.");
	}
}