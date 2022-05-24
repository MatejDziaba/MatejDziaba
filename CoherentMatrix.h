#pragma once

#include "matrix.h"
#include <stdexcept>
//#include "../list.h"
#include "../structure_iterator.h"
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

		/// <summary> Vrati index matici v pamati typu int. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// /// <returns> index v matici(v Array<T>*). </returns>
		/// /// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		int mapFunction(int rowIndex, int columnIndex);

		/// <summary> Vrati pravdivostnu hodnotu hodnot dvoch matic. </summary>
		/// <param name="rowSum"> pocet riadkov matice. </param>
		/// <param name="columnSum"> pocet stlpcov matice. </param>
		/// /// <returns> index v matici(v Array<T>*). </returns>
		/// /// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		bool equalsAt(Array<T>* matrix, CoherentMatrix<T>* otherMatrix, int rowSum, int columnSum);

	private:
		/// matica typu T
		Array<T>* matica_;

		size_t rowCount_ = 0;				// pocet riadkov matice
		size_t columnCount_ = 0;			// pocet stlpcov matice
		size_t sizeMatica_ = 0;				//// velkost matice teda pocet prvkov
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
	{
		if (rowCount >= 1 && columnCount >= 1) {
			this->rowCount_ = rowCount;
			this->columnCount_ = columnCount;
			this->sizeMatica_ = this->rowCount_ * this->columnCount_; // velkost matice teda pocet prvkov
			this->matica_ = new Array<T>(this->sizeMatica_);     // naalokujem v pamati za sebou pocet prvkou  napr. 000 000 000 ROW=3, COLUMN=3
		}
		else {
			throw std::logic_error("CoherentMatrix<T>::CoherentMatrix: ROW or COLUMN is lower as 1!");
		}
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) : Matrix<T>()
	{
		this->rowCount_ = other.rowCount_;
		this->columnCount_ = other.columnCount_;
		this->sizeMatica_ = other.size();

		this->matica_ = new Array<T>(*other.matica_);
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete this->matica_;
		this->columnCount_ = 0;
		this->rowCount_ = 0;
		this->sizeMatica_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this->matica_ == nullptr) {
			throw std::logic_error("IncoherentMatrix<T>::assign: Matica neexistuje___this->matica_");
		}

		if (&other != this && this->matica_ != nullptr) {
			CoherentMatrix<T>& otherMatrix = dynamic_cast<CoherentMatrix<T>&>(other);

			if (this->rowCount_ == otherMatrix.rowCount_                   // pocet riadkov, stlpcov sa musi rovnat
				&& this->columnCount_ == otherMatrix.columnCount_)
			{
				delete this->matica_;
				this->matica_ = new Array<T>(*(otherMatrix.matica_));  // cez kopi v Array
			}
			else if (this->rowCount_ != otherMatrix.rowCount_                   // pocet riadkov, stlpcov sa musi rovnat
				&& this->columnCount_ != otherMatrix.columnCount_)
			{
				this->rowCount_ = otherMatrix.rowCount_;
				this->columnCount_ = otherMatrix.columnCount_;
				this->sizeMatica_ = otherMatrix.sizeMatica_;

				delete this->matica_;
				this->matica_ = new Array<T>(*(otherMatrix.matica_));
			}
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this != &other)
		{
			CoherentMatrix<T>* otherMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);

			if (otherMatrix != nullptr)
			{
				if (this->rowCount_ == otherMatrix->rowCount_
					&& this->columnCount_ == otherMatrix->columnCount_)
				{
					return this->equalsAt(this->matica_, otherMatrix, this->rowCount_, this->columnCount_);
				}
				return false;
			}
			return false;
		}

		return true;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return this->sizeMatica_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return this->rowCount_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return this->columnCount_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		return this->matica_->at(this->mapFunction(rowIndex, columnIndex));
	}

	template<typename T>
	inline int CoherentMatrix<T>::mapFunction(int rowIndex, int columnIndex)
	{
		if (rowIndex < 0 && columnIndex < 0) {
			throw std::range_error("CoherentMatrix<T>::mapFunction: ROW < 1 alebo COLUMN < 1");
		}
		else {
			int index = (this->columnCount_ * (rowIndex)) + (columnIndex);
			//Utils::rangeCheckExcept(index, this->matica_->size(), "CoherentMatrix<T>::mapFunction: Invalid index!");
			return index;
		}
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equalsAt(Array<T>* matrix, CoherentMatrix<T>* otherMatrix, int rowSum, int columnSum)
	{
		for (size_t i = 0; i < rowSum; i++)   // riadky
		{
			for (size_t j = 0; j < columnSum; j++)  // stlpce
			{
				if (matrix->at(this->mapFunction(i, j)) != otherMatrix->matica_->at(this->mapFunction(i, j))) {
					return false;
				}
			}
		}
		
		return true;
	}
}
