#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;			// размер вектора
	int StartIndex;		// индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);					// конструктор копирования
	~TVector();									// Диструктор
	int GetSize() { return Size; }				// размер вектора
	int GetStartIndex() { return StartIndex; }	// индекс первого элемента
	ValType& operator[](int pos);				// доступ
	bool operator==(const TVector& v) const;	// сравнение
	bool operator!=(const TVector& v) const;	// сравнение
	TVector& operator=(const TVector& v);		// присваивание

	// скалярные операции
	TVector  operator+(const ValType& val);		// прибавить скаляр
	TVector  operator-(const ValType& val);		// вычесть скаляр
	TVector  operator*(const ValType& val);		// умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector& v);		// сложение
	TVector  operator-(const TVector& v);		// вычитание
	ValType  operator*(const TVector& v);		// скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s > MAX_VECTOR_SIZE || s < 0)
	{
		bad_alloc exp;
		throw exp;
	}
	if ((si < 0) || (si > MAX_VECTOR_SIZE))
	{
		throw "Start index is negative";
	}
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;
	for (int i = 0; i < s; i++)
		pVector[i] = 0;
}

template <class ValType> // Конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	copy(v.pVector, v.pVector + Size, pVector);
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
}

template <class ValType> // Доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < 0 || pos - StartIndex > Size)
	{
		throw "index out of range";
	}
	else
		return pVector[pos - StartIndex];
}

template <class ValType> // Сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;


}

template <class ValType> // Сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !(operator==(v));
}

template <class ValType> // Присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			Size = v.Size;
			delete[] pVector;
			pVector = new ValType[Size];
		}
		StartIndex = v.StartIndex;
		copy(v.pVector, v.pVector + Size, pVector);
	}
	return *this;
}

template <class ValType> // Прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] += val;
	return temp;
}

template <class ValType> // Вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] -= val;
	return temp;
}

template <class ValType> // Умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] *= val;
	return temp;
}

template <class ValType> // Сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		TVector<ValType> temp(Size, StartIndex);
		for (int i = 0; i < Size; i++)
			temp.pVector[i] = pVector[i] + v.pVector[i];
		return temp;
	}
	else
	{
		throw "not equal size!";
	}
}

template <class ValType> // Вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		TVector<ValType> temp(Size, StartIndex);
		for (int i = 0; i < Size; i++)
			temp.pVector[i] = pVector[i] - v.pVector[i];
		return temp;
	}
	throw "not equal size!";
}

template <class ValType> // Скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size == v.Size)
	{
		ValType result = 0;
		for (int i = 0; i < Size; i++)
			result += pVector[i] * v.pVector[i];
		return result;
	}
	throw "not equal size!";
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	// Ввод/Вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

	void WriteFile(std::string path)	// Вывод в файл
	{
		std::ofstream file(path, std::ios::trunc);
		if (file.is_open())
		{
			for (int i = 0; i < this->GetSize(); i++)
				file << this->pVector[i] << endl;
		}
		else
		{
			std::cout << "Files is not open!\n";
		}
		file.close();
	}

	void ReadFile(std::string path, TMatrix& mt)	// Чтение с файла
	{
		std::ifstream file(path, std::ios::in);
		if (file.is_open())
		{
			std::string buf;

			int val[250];
			int i_val = 0;
			std::string str;

			while (std::getline(file, buf))
			{
				for (int i = 0; i < buf.size(); i++)
				{
					if (buf[i] == ' ')
					{
						val[i_val] = std::atoi(str.c_str());
						i_val++;
						str.clear();
						continue;
					}
					str += buf[i];
				}
			}
			i_val = 0;
			for (int i = 0; i < 5; i++)
				for (int j = i; j < 5; j++)
				{
					mt.pVector[i][j] = val[i_val];
					i_val++;
				}
		}
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
	{
		bad_alloc exp;
		throw exp;
	}
	for (int i = 0; i < s; i++)
		this->pVector[i] = move(TVector<ValType>(s - i, i));
}

template <class ValType> // Конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // Конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // Сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // Сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return !(operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // Присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	TVector < TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // Сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // Вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

