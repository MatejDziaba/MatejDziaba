#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(K key, bool& found);

	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree():
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(BinarySearchTree<K, T>& other):
		BinarySearchTree()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		//TODO 10: BinarySearchTree
		this->clear();
		delete binaryTree_;
		this->binaryTree_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size()
	{
		//TODO 10: BinarySearchTree
		return this->size_;
		//throw std::runtime_error("BinarySearchTree<K, T>::size: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Structure& BinarySearchTree<K, T>::assign(Structure& other)
	{
		//TODO 10: BinarySearchTree
		// kontrola identidty
		// preorder a inroder Iterator
		// TableItem -> insert
		
		
		if (this != &other) {
			BinarySearchTree<K, T>& otherBinarySearchTree = dynamic_cast<BinarySearchTree<K, T>&>(other);

			this->clear();

			auto iterOtherBegin = new Tree<TableItem<K, T>*>::PreOrderTreeIterator(otherBinarySearchTree.binaryTree_->getRoot());
			auto itherOtherEnd = new Tree<TableItem<K, T>*>::PreOrderTreeIterator(nullptr);

			while (*iterOtherBegin != *itherOtherEnd) {
				TableItem<K, T>* item = *(*iterOtherBegin);
				this->insert(item->getKey(), item->accessData());

				++(*iterOtherBegin);

			}

			delete iterOtherBegin;
			delete itherOtherEnd;
		}
		
		return *this;
		//throw std::runtime_error("BinarySearchTree<K, T>::assign: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equals(dynamic_cast<BinarySearchTree<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& BinarySearchTree<K, T>::find(const K& key)
	{
		//TODO 10: BinarySearchTree
		bool found = false;
		auto node = this->findBSTNode(key, found);
		if (found) {
			return node->accessData()->accessData();
		}
		else {
			throw std::runtime_error("BinarySearchTree<K, T>::find: No data with such key!");
		}
		//throw std::runtime_error("BinarySearchTree<K, T>::find: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data)
	{
		//TODO 10: BinarySearchTree
		TableItem<K, T>* itemData = new TableItem<K, T>(key, data);
		BSTTreeNode* node = new BSTTreeNode(itemData);

		if (!this->tryToInsertNode(node)) {
			delete node;
			delete itemData;
			throw std::logic_error("BinarySearchTree<K, T>::insert: Data with that key lready exists!");
		}
		//throw std::runtime_error("BinarySearchTree<K, T>::insert: Not implemented yet.");
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key)
	{
		//TODO 10: BinarySearchTree

		bool found = false;
		BSTTreeNode* foundNODE = this->findBSTNode(key, found);   //chcem zmazat
		T returnValue = foundNODE->accessData()->accessData();

		if (found) {
			this->extractNode(foundNODE);  // tu sa aktualizuje size_
			if (foundNODE->getParent() == nullptr 
				&& this->size_ == 1) 
			{
				return returnValue;
			}
			delete foundNODE->accessData();
			delete foundNODE;
			return returnValue;
		}
		else {
			throw std::logic_error("BinarySearchTree<K, T>::remove(): Found je false, resp dany Key nemusi existovat");
		}

		//throw std::runtime_error("BinarySearchTree<K, T>::remove: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data)
	{
		//TODO 10: BinarySearchTree
		bool found = false;
		auto node = this->findBSTNode(key, found);
		if (found) {
			data = node->accessData()->accessData();
			return true;
		}
		else {
			return false;
		}
		//throw std::runtime_error("BinarySearchTree<K, T>::tryFind: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key)
	{
		//TODO 10: BinarySearchTree
		bool found = false;
		this->findBSTNode(key, found);
		return found;
		//throw std::runtime_error("BinarySearchTree<K, T>::containsKey: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
		//TODO 10: BinarySearchTree
		for (auto item : *binaryTree_) {
			delete item;
		}
		binaryTree_->clear();   // vymaze sa koren
		this->size_ = 0;
		//throw std::runtime_error("BinarySearchTree<K, T>::clear: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator()
	{
		//TODO 10: BinarySearchTree
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(binaryTree_->getRoot());
		//throw std::runtime_error("BinarySearchTree<K, T>::getBeginIterator: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator()
	{
		//TODO 10: BinarySearchTree
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(nullptr);
		//throw std::runtime_error("BinarySearchTree<K, T>::getEndIterator: Not implemented yet.");
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K,T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(K key, bool& found)
	{
		//TODO 10: BinarySearchTree

		BSTTreeNode* currentNode = dynamic_cast<BSTTreeNode*>(binaryTree_->getRoot());

		if (currentNode == nullptr) {
			found = false;
			return currentNode;
		}
		else {
			while (currentNode->accessData()->getKey() != key) {
				if (currentNode->accessData()->getKey() > key) {
					if (currentNode->hasLeftSon()) {
						currentNode = currentNode->getLeftSon();
					}
					else {
						return currentNode;
					}
					
				}
				else {
					if (currentNode->hasRightSon()) {
						currentNode = currentNode->getRightSon();
					}
					else {
						return currentNode;
					}
					
				}
			}

			found = true;
			return currentNode;
		}
		//throw std::runtime_error("BinarySearchTree<K, T>::findBSTNode: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		//TODO 10: BinarySearchTree
		bool found = false;
		auto parent = this->findBSTNode(node->accessData()->getKey(), found);

		if (!found) {
			if (parent == nullptr) {
				binaryTree_->replaceRoot(node);
			}
			else {
				if (parent->accessData()->getKey() > node->accessData()->getKey()) {
					parent->setLeftSon(node);
				}
				else {
					parent->setRightSon(node);
				}
			}
			size_++;
		}

		return !found;
		//throw std::runtime_error("BinarySearchTree<K, T>::tryToInsertNode: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{
		//TODO 10: BinarySearchTree
		BSTTreeNode* foundNode = node;
		BSTTreeNode* parentNode = foundNode->getParent();

		if (this->size_ == 1
			&& parentNode == nullptr)
		{
			foundNode = nullptr;
			//this->size_--;
		} 
		else if (this->size_ > 1) 
		{

			if (foundNode->isLeaf())					//****** Ak vrchol ma 0 sons ******
			{
				if (parentNode->hasLeftSon()) {
					parentNode->setLeftSon(nullptr);   // nastavenie syna na nullptr
					foundNode = nullptr;              // nastavenie otca na nullptr
				}

				if (parentNode->hasRightSon()) {
					parentNode->setRightSon(nullptr);  // nastavenie syna na nullptr
					foundNode = nullptr;			   // nastavenie otca na nullptr
				}
			} 
			else if (!foundNode->hasLeftSon() && foundNode->hasRightSon()        //****** Ak vrchol ma 1 son *******
				|| foundNode->hasLeftSon() && !foundNode->hasRightSon())
			{
				if (parentNode != nullptr) {
					if (parentNode->hasLeftSon()) {
						if (foundNode == parentNode->getLeftSon()) {    //** AK MAZANY VRCHOL JE LAVYM POTOMKOM SVOJHO OTCA **
							if (foundNode->hasRightSon()) {
								parentNode->setLeftSon(foundNode->getRightSon());
								foundNode->setRightSon(nullptr);
							}
							else if (foundNode->hasLeftSon()) {
								parentNode->setLeftSon(foundNode->getLeftSon());
								foundNode->setLeftSon(nullptr);
							}
						}
					} else if (parentNode->hasRightSon()) 
					{
						if (foundNode == parentNode->getRightSon())   //** AK MAZANY VRCHOL JE PRAVYM POTOMKOM SVOJHO OTCA **
						{
							if (foundNode->hasRightSon()) {
								parentNode->setRightSon(foundNode->getRightSon());
								foundNode->setRightSon(nullptr);
							}
							else if (foundNode->hasLeftSon()) {
								parentNode->setRightSon(foundNode->getLeftSon());
								foundNode->setLeftSon(nullptr);
							}
							
						}
					}

				} else if (parentNode == nullptr) {
					if (foundNode->hasLeftSon()) 
					{
						foundNode = dynamic_cast<BSTTreeNode*>(this->binaryTree_->replaceRoot(foundNode->getLeftSon()));  // tu nastavi root na foundNode.getSon, foundNode je stary root
						foundNode->setLeftSon(nullptr);        // zrusi pointer z stareho rootu(aktualne to je foundNode) na novy root
						node = foundNode;

					} else if (foundNode->hasRightSon()) 
					{
						foundNode = dynamic_cast<BSTTreeNode*>(this->binaryTree_->replaceRoot(foundNode->getRightSon()));  // tu nastavi root na foundNode.getSon, foundNode je stary root
						foundNode->setRightSon(nullptr);        // zrusi pointer z stareho rootu(aktualne to je foundNode) na novy root
						node = foundNode;
					}
				}

				
			}
			else if (foundNode->hasLeftSon() && foundNode->hasRightSon())   //****** Ak vrchol ma 2 sons *******
			{
				// ** HLADAM NODE, KTORY POTOM CHCEM NAHRADIT NA MIESTO MAZANEHO VRCHOLU * 
				BSTTreeNode* najLavy_Node_VPravomPodStrome = foundNode->getRightSon();
				bool najLAVY_Node_NAJDENY = false;
				do
				{
					if (!najLavy_Node_VPravomPodStrome->hasLeftSon())
					{
						if (najLavy_Node_VPravomPodStrome->isLeaf())
						{
							najLAVY_Node_NAJDENY = true;
						}
						else {
							najLavy_Node_VPravomPodStrome = foundNode->getRightSon();
						}
					}
					else if (najLavy_Node_VPravomPodStrome->hasLeftSon()) 
					{
						najLavy_Node_VPravomPodStrome = najLavy_Node_VPravomPodStrome->getLeftSon();
						if (najLavy_Node_VPravomPodStrome->isLeaf())
						{
							najLAVY_Node_NAJDENY = true;
						}
					}

				} while (!najLAVY_Node_NAJDENY);

				// TU UZ JE NAJDENY VRCHOL, CHCEM SA OPYTAT CI JE LAVYM ALEBO PRAVYM A ZRUSIT NA NEHO POINTER
				BSTTreeNode* parent_NajLavyNodeVPravomPodStrome = najLavy_Node_VPravomPodStrome->getParent();
				if (parent_NajLavyNodeVPravomPodStrome->hasLeftSon()) {
					if (parent_NajLavyNodeVPravomPodStrome->getLeftSon() == najLavy_Node_VPravomPodStrome)
					{      // AK JE LAVYM SYNOM SVOJHO OTCA
						parent_NajLavyNodeVPravomPodStrome->setLeftSon(nullptr);                                  // TAK RUSIM UKAZOVATEL NA NODE, KTORY NAHRADIM ZA MAZANY VRCHOL
					}
					else {
						throw std::logic_error("BinarySearchTree<K, T>::extractNode(): Niekde je chyba x01");
					}
				}
				else if (parent_NajLavyNodeVPravomPodStrome->hasRightSon()) {
					if (parent_NajLavyNodeVPravomPodStrome->getRightSon() == najLavy_Node_VPravomPodStrome)
					{      // AK JE PRAVYM SYNOM SVOJHO OTCA, to je, ak hladany Node je LEAF
						parent_NajLavyNodeVPravomPodStrome->setRightSon(nullptr);                                  // TAK RUSIM UKAZOVATEL NA NODE, KTORY NAHRADIM ZA MAZANY VRCHOL
					}
					else {
						throw std::logic_error("BinarySearchTree<K, T>::extractNode(): Niekde je chyba x02");
					}
				}
				
				

				// ** VYKONAM VYMAZANIE POINTEROV NA KONKRETNY SON, NASTAVIM POINTRE NA NOVY NODE, KTORYM NAHRADIM MAZANY *
				BSTTreeNode* pravySonFoundNode = foundNode->getLeftSon();
				BSTTreeNode* lavySonFoundNode = foundNode->getRightSon();
			

				// AK PREDOK MAZANEHO VRCHOLU NIE JE NULLPTR, tak nastavim pointre na nahradzajuci node, vymazanie vrcholov sa vykona v metode setLeftSon, setRightSon
				if (parentNode != nullptr) {
					if (parentNode->hasLeftSon()) {
						if (parentNode->getLeftSon() == foundNode) {
							parentNode->setLeftSon(najLavy_Node_VPravomPodStrome);
						}
					}
					else if (parentNode->hasRightSon()) {
						if (parentNode->getRightSon() == foundNode)
						{
							parentNode->setRightSon(najLavy_Node_VPravomPodStrome);
						}
					}
				}
						
				najLavy_Node_VPravomPodStrome->setLeftSon(lavySonFoundNode);
				foundNode->setLeftSon(nullptr);
				if (najLavy_Node_VPravomPodStrome != pravySonFoundNode) {
					najLavy_Node_VPravomPodStrome->setRightSon(pravySonFoundNode);
					foundNode->setRightSon(nullptr);
				}
				else if (najLavy_Node_VPravomPodStrome == pravySonFoundNode) {
					foundNode->setRightSon(nullptr);
				}
				
				
				
				// vymazanie prvku ak je parentNode == nullptr
				if (parentNode == nullptr) {
					foundNode = dynamic_cast<BSTTreeNode*>(this->binaryTree_->replaceRoot(najLavy_Node_VPravomPodStrome));  // ak mazany prvok je root tak ho replace, a vratim ho na mazanie
					node = foundNode;
				}
					
			}
			this->size_--;
		}


	}

}