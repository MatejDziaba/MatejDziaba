#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"
#include "linked_list.h"

namespace structures
{
    // implementacne tipy: 
    //  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
    //    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
    //    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
    //    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
    //    zvysok nechat na predka.
    //  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
    //    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
    //  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
    //    takze ich nebudete musiet implementovat.

     /// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class DoubleLinkedListItem : public LinkedListItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getPrevious();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setPrevious(DoubleLinkedListItem<T>* previous);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* previous_;
    };

    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class DoubleLinkedList : public LinkedList<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        DoubleLinkedListItem<T>* getItemAtIndex(int index);
    };

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() : 
        LinkedList<T>()
    {
        //TODO Zadanie 2: DoubleLinkedList
        //throw std::runtime_error("DoubleLinkedList<T>::DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        this->assign(other);
        //throw std::runtime_error("DoubleLinkedList<T>::DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        //TODO Zadanie 2: DoubleLinkedList
        LinkedList<T>::clear();
        //throw std::runtime_error("DoubleLinkedList<T>::~DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::size();
        //throw std::runtime_error("DoubleLinkedList<T>::size: Not implemented yet.");
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        if (&other != this) {
            DoubleLinkedList<T>& otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>&>(other);
            LinkedList<T>::clear();
            for (T data : otherDoubleLinkedList)
            {
                this->add(data);
            }
        }
        return *this;
        //throw std::runtime_error("DoubleLinkedList<T>::assign: Not implemented yet.");
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::equals(dynamic_cast<DoubleLinkedList<T>&>(other));
        //throw std::runtime_error("DoubleLinkedList<T>::equals: Not implemented yet.");
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::at(index);
        //throw std::runtime_error("DoubleLinkedList<T>::at: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        DoubleLinkedListItem<T>* newLLI = new DoubleLinkedListItem<T>(data);
        DoubleLinkedListItem<T>* prevLLI = dynamic_cast<DoubleLinkedListItem<T>*>(last_);
        
        if (size_ == 0) {
            first_ = newLLI;
            last_ = newLLI;
        }
        else if (size_ > 0 || prevLLI != nullptr) {
            last_->setNext(newLLI);
            prevLLI = dynamic_cast<DoubleLinkedListItem<T>*>(last_);
            last_ = newLLI;
            dynamic_cast<DoubleLinkedListItem<T>*>(last_)->setPrevious(prevLLI);
        }

        size_++;
        //throw std::runtime_error("DoubleLinkedList<T>::add: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        if (index == size_) {
            this->add(data);
        }
        else {
           // Utils::rangeCheckExcept(index, size_, "Invalid index");
            DoubleLinkedListItem<T>* newLLI = new DoubleLinkedListItem<T>(data);

            if (index == 0) {
                newLLI->setNext(first_);
                dynamic_cast<DoubleLinkedListItem<T>*>(first_)->setPrevious(newLLI);
                first_ = newLLI;
            }
            else {
                DoubleLinkedListItem<T>* prevLLI = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* curLLI = getItemAtIndex(index);
                curLLI->setPrevious(newLLI);
                newLLI->setNext(curLLI);
                newLLI->setPrevious(prevLLI);
                prevLLI->setNext(newLLI);
            }
            size_++;
        }
        //throw std::runtime_error("DoubleLinkedList<T>::insert: Not implemented yet.");
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        int index = getIndexOf(data);
        if (index == -1)
        {
            return false;
        }
        else {
            this->removeAt(index);
            return true;
        }
        //throw std::runtime_error("DoubleLinkedList<T>::tryRemove: Not implemented yet.");
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        DoubleLinkedListItem<T>* delItem = dynamic_cast<DoubleLinkedListItem<T>*>(first_);
       

        if (size_ == 1) {
            delItem = dynamic_cast<DoubleLinkedListItem<T>*>(first_);
            first_ = nullptr;
            last_ = nullptr;

        }
        else {
           // Utils::rangeCheckExcept(index, size_, "Invalid index");
            if (index == 0) {
                delItem = dynamic_cast<DoubleLinkedListItem<T>*>(first_);
                first_ = first_->getNext();
            }
            else {
                DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* nextLLI = dynamic_cast<DoubleLinkedListItem<T>*>(prevItem->getNext()->getNext());

                delItem = dynamic_cast<DoubleLinkedListItem<T>*>(getItemAtIndex(index));         // to je sucasny prvok, ktory chcem mazat

               /* if (delItem == nullptr) {
                    return 0;
                }*/

                if (delItem->getNext() == nullptr) {
                    last_ = prevItem;
                } 
                else if (delItem->getNext() != nullptr) {
                    prevItem->setNext(delItem->getNext()); // to je nasledujuci prvok
                    nextLLI->setPrevious(prevItem); // smernik na predchadzajuci prvok
                }

                
            }
        }
        size_--;
        T result = delItem->accessData();
        delete delItem;
        return result;
        //throw std::runtime_error("DoubleLinkedList<T>::removeAt: Not implemented yet.");
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::getIndexOf(data);
    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        //TODO Zadanie 2: DoubleLinkedList
        LinkedList<T>::clear();
        //throw std::runtime_error("DoubleLinkedList<T>::clear: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::getBeginIterator();
        //throw std::runtime_error("DoubleLinkedList<T>::getBeginIterator: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        return LinkedList<T>::getEndIterator();
        //throw std::runtime_error("DoubleLinkedList<T>::getEndIterator: Not implemented yet.");
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        if (index == this->size_ - 1)
        {
            return dynamic_cast<DoubleLinkedListItem<T>*>(last_);
        }

        LinkedListItem<T>* current = first_;
        for (size_t i = 0; i < index; i++)
        {
            current = current->getNext();
        }
        return dynamic_cast<DoubleLinkedListItem<T>*>(current);
        
    }


    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        LinkedListItem<T>(data),
        previous_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        LinkedListItem<T>(other),
        previous_(other.previous_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        LinkedListItem<T>::~LinkedListItem();
        previous_ = nullptr;
    }


    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
    {
        return previous_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
    {
        previous_ = previous;
    }


}