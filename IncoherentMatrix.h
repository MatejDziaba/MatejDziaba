#pragma once

#include "matrix.h"
#include <stdexcept>
//#include "../list.h"
#include "../structure_iterator.h"
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

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

		/// <summary> Vrati pravdivostnu hodnotu hodnot dvoch matic. </summary>
		/// <param name="matrix"> matica typu polePoli Array<Array<T>*>*. </param>
		/// <param name="otherMatrix"> otherMatrix typu IncoherentMatrix<T>*. </param>
		/// <param name="rowSum"> pocet riadkov matice. </param>
		/// <param name="columnSum"> pocet stlpcov matice. </param>
		/// /// <returns> index v matici(v Array<T>*). </returns>
		/// /// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		bool equalsAt(Array<Array<T>*>* matrix, IncoherentMatrix<T>* otherMatrix, int rowSum, int columnSum);

		/// <summary> Skopiruje otherMatrix do atributu matica. </summary>
		/// <param name="otherMatrix"> pre kopirovanie do atributu matica. </param>
		/// /// <returns> nic. </returns>
		void copy(IncoherentMatrix<T>& otherMatrix);

	private:
		/// matica typu T
		Array<Array<T>*>* matica_;

		size_t rowCount_ = 0;				// pocet riadkov matice
		size_t columnCount_ = 0;			// pocet stlpcov matice
		size_t sizeMatica_ = 0;				//// velkost matice teda pocet prvkov

	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
	{
		if (rowCount >= 1 && columnCount >= 1) {
			this->rowCount_ = rowCount;
			this->columnCount_ = columnCount;
			this->sizeMatica_ = this->rowCount_ * this->columnCount_; // velkost matice teda pocet prvkov

			this->matica_ = new Array<Array<T>*>(this->rowCount_);

			for (size_t i = 0; i < this->rowCount_; i++)
			{
				this->matica_->at(i) = new Array<T>(this->columnCount_);
			}

		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
	{
		this->rowCount_ = other.rowCount_;
		this->columnCount_ = other.columnCount_;
		this->sizeMatica_ = other.sizeMatica_;

		this->matica_ = new Array<Array<T>*>(this->rowCount_);
		for (size_t i = 0; i < this->rowCount_; i++)
		{
			this->matica_->at(i) = new Array<T>(this->columnCount_); // na i-tom riadku vytvori Array o velkosti stplcov ak 3*4 tak 4 policka od 0,1,2,3
			for (size_t j = 0; j < this->columnCount_; j++)
			{
				this->matica_->at(i)->at(j) = other.matica_->at(i)->at(j);    // priradi hodnotu
			}
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		//TODO Zadanie 1: InCoherentMatrix

		// vymazem stlpce
		for (size_t i = 0; i < this->rowCount_; i++)
		{
			delete this->matica_->at(i);
		}
		delete this->matica_;
		this->columnCount_ = 0;
		this->rowCount_ = 0;
		this->sizeMatica_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this->matica_ == nullptr) {
			throw std::logic_error("IncoherentMatrix<T>::assign: Matica neexistuje___this->matica_");
		}

		if (&other != this && this->matica_ != nullptr) {
			IncoherentMatrix<T>& otherMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);

			if (this->rowCount_ == otherMatrix.rowCount_                   // pocet riadkov, stlpcov sa musi rovnat
				&& this->columnCount_ == otherMatrix.columnCount_)
			{
				this->copy(otherMatrix);   // skopiruje otherMaticu ddo atributu matica
			}// ak sa matice nerovnaju
			else if (this->rowCount_ != otherMatrix.rowCount_                   // pocet riadkov, stlpcov sa musi rovnat
				&& this->columnCount_ != otherMatrix.columnCount_)
			{
				this->rowCount_ = otherMatrix.rowCount_;
				this->columnCount_ = otherMatrix.columnCount_;
				this->sizeMatica_ = otherMatrix.sizeMatica_;

				for (size_t i = 0; i < this->rowCount_; i++)
				{
					delete this->matica_->at(i);
				}
				delete this->matica_;
				this->matica_ = new Array<Array<T>*>(this->rowCount_);
				for (size_t i = 0; i < this->rowCount_; i++)
				{
					this->matica_->at(i) = new Array<T>(this->columnCount_);
					for (size_t j = 0; j < this->rowCount_; j++) {
						this->matica_->at(i)->at(j) = otherMatrix.matica_->at(i)->at(j);
					}
				}
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		if (this != &other)
		{
			IncoherentMatrix<T>* otherMatrix = dynamic_cast<IncoherentMatrix<T>*>(&other);

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
	inline size_t IncoherentMatrix<T>::size()
	{
		return this->sizeMatica_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return this->rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return this->columnCount_;
	}


	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		int row = rowIndex;
		int column = columnIndex;

		return this->matica_->at(row)->at(column);
	}
	template<typename T>
	inline bool IncoherentMatrix<T>::equalsAt(Array<Array<T>*>* matrix, IncoherentMatrix<T>* otherMatrix, int rowSum, int columnSum)
	{
		for (size_t i = 0; i < rowSum; i++)
		{
			Array<T>* smernik_matica = matrix->at(i);
			Array<T>* smernik_otherMatica = otherMatrix->matica_->at(i);
			for (size_t j = 0; j < columnSum; j++)
			{
				T& referencia_matica = smernik_matica->at(j);
				T& referencia_otherMatica = smernik_otherMatica->at(j);
				if (referencia_matica != referencia_otherMatica) {
					return false;
				}
			}
		}
		return true;
	}

	template<typename T>
	inline void IncoherentMatrix<T>::copy(IncoherentMatrix<T>& otherMatrix)
	{
		for (size_t i = 0; i < this->rowCount_; i++)
		{
			for (size_t j = 0; j < this->columnCount_; j++)
			{
				this->matica_->at(i)->at(j) = otherMatrix.matica_->at(i)->at(j);
			}
		}
	}
}
