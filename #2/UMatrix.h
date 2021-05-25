#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;			// ������ �������
	int StartIndex;		// ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);					// ����������� �����������
	~TVector();									// ����������
	int GetSize() { return Size; }				// ������ �������
	int GetStartIndex() { return StartIndex; }	// ������ ������� ��������
	ValType& operator[](int pos);				// ������
	bool operator==(const TVector& v) const;	// ���������
	bool operator!=(const TVector& v) const;	// ���������
	TVector& operator=(const TVector& v);		// ������������

	// ��������� ��������
	TVector  operator+(const ValType& val);		// ��������� ������
	TVector  operator-(const ValType& val);		// ������� ������
	TVector  operator*(const ValType& val);		// �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector& v);		// ��������
	TVector  operator-(const TVector& v);		// ���������
	ValType  operator*(const TVector& v);		// ��������� ������������

	// ����-�����
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

template <class ValType> // ����������� �����������
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

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < 0 || pos - StartIndex > Size)
	{
		throw "index out of range";
	}
	else
		return pVector[pos - StartIndex];
}

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;


}

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !(operator==(v));
}

template <class ValType> // ������������
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

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] += val;
	return temp;
}

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] -= val;
	return temp;
}

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> temp(*this);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] *= val;
	return temp;
}

template <class ValType> // ��������
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

template <class ValType> // ���������
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

template <class ValType> // ��������� ������������
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


// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // �����������
	TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const TMatrix& mt) const;      // ���������
	bool operator!=(const TMatrix& mt) const;      // ���������
	TMatrix& operator= (const TMatrix& mt);        // ������������
	TMatrix  operator+ (const TMatrix& mt);        // ��������
	TMatrix  operator- (const TMatrix& mt);        // ���������
	TMatrix  operator* (const TMatrix& mt);		   // �����������

	TMatrix  operator+ (const ValType& num);
	TMatrix  operator- (const ValType& num);
	TMatrix  operator* (const ValType& num);

	// ����/�����
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

	void WriteFile(std::string path)	// ����� � ����
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

	void ReadFile(std::string path, TMatrix& mt)	// ������ � �����
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
	{
		this->pVector[i] = TVector<ValType>(s - i, i);
	}
}

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return !(operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	TVector < TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& mt)
{
	if (this->Size != mt.Size)
		throw "Error size";
	TMatrix <ValType> resault(this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = i; j < this->Size; j++)
		{
			for (int k = i; k < j + 1; k++)
			{
				resault.pVector[i][j] += this->pVector[i][k] * mt.pVector[k][j];
			}
		}
	}
	return resault;
}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::operator*(const ValType& num)
{
	TMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TMatrix::pVector[i] * num;
	return res;
}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::operator+(const ValType& num)
{
	TMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TMatrix::pVector[i] + num;
	return res;
}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::operator-(const ValType& num)
{
	TMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TMatrix::pVector[i] - num;
	return res;
}

// ����� �����������
template <class ValType>
class LowerMatrix : public TVector<TVector<ValType> >
{
public:
	LowerMatrix(int s = 10);
	LowerMatrix(const LowerMatrix& mt);                    // �����������
	LowerMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const LowerMatrix& mt) const;      // ���������
	bool operator!=(const LowerMatrix& mt) const;      // ���������
	LowerMatrix& operator= (const LowerMatrix& mt);        // ������������
	LowerMatrix  operator+ (const LowerMatrix& mt);        // ��������
	LowerMatrix  operator- (const LowerMatrix& mt);        // ���������
	LowerMatrix  operator* (const LowerMatrix& mt);		   // �����������

	LowerMatrix  operator+ (const ValType& num);
	LowerMatrix  operator- (const ValType& num);
	LowerMatrix  operator* (const ValType& num);

	// ����/�����
	friend istream& operator>>(istream& in, LowerMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const LowerMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

	void WriteFile(std::string path)	// ����� � ����
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

	void ReadFile(std::string path, LowerMatrix& mt)	// ������ � �����
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
LowerMatrix<ValType>::LowerMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
	{
		bad_alloc exp;
		throw exp;
	}
	for (int i = 0; i < s; i++)
	{
		this->pVector[i] = TVector<ValType>(i + 1, 0);
	}
}

template <class ValType> // ����������� �����������
LowerMatrix<ValType>::LowerMatrix(const LowerMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
LowerMatrix<ValType>::LowerMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool LowerMatrix<ValType>::operator==(const LowerMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool LowerMatrix<ValType>::operator!=(const LowerMatrix<ValType>& mt) const
{
	return !(operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
LowerMatrix<ValType>& LowerMatrix<ValType>::operator=(const LowerMatrix<ValType>& mt)
{
	TVector < TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
LowerMatrix<ValType> LowerMatrix<ValType>::operator+(const LowerMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
LowerMatrix<ValType> LowerMatrix<ValType>::operator-(const LowerMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

template<class ValType>
inline LowerMatrix<ValType> LowerMatrix<ValType>::operator*(const LowerMatrix& mt)
{
	if (this->Size != mt.Size)
		throw "Error size";
	LowerMatrix <ValType> resault(this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = i; j < this->Size; j++)
		{
			for (int k = i; k < j + 1; k++)
			{
				resault.pVector[i][j] += this->pVector[i][k] * mt.pVector[k][j];
			}
		}
	}
	return resault;
}

template<class ValType>
inline LowerMatrix<ValType> LowerMatrix<ValType>::operator*(const ValType& num)
{
	LowerMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = LowerMatrix::pVector[i] * num;
	return res;
}

template<class ValType>
inline LowerMatrix<ValType> LowerMatrix<ValType>::operator+(const ValType& num)
{
	LowerMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = LowerMatrix::pVector[i] + num;
	return res;
}

template<class ValType>
inline LowerMatrix<ValType> LowerMatrix<ValType>::operator-(const ValType& num)
{
	LowerMatrix res(this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = LowerMatrix::pVector[i] - num;
	return res;
}

// ���������� �������
template <class ValType>
class RazrMatrix : public TVector<TVector<ValType> >
{
private:
	int sR;
public:
	RazrMatrix(int r, int s = 10);
	RazrMatrix(const RazrMatrix& mt);                    // �����������
	RazrMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const RazrMatrix& mt) const;      // ���������
	bool operator!=(const RazrMatrix& mt) const;      // ���������
	RazrMatrix& operator= (const RazrMatrix& mt);        // ������������
	RazrMatrix  operator+ (const RazrMatrix& mt);        // ��������
	RazrMatrix  operator- (const RazrMatrix& mt);        // ���������
	RazrMatrix  operator* (const RazrMatrix& mt);		   // �����������

	RazrMatrix  operator+ (const ValType& num);
	RazrMatrix  operator- (const ValType& num);
	RazrMatrix  operator* (const ValType& num);

	int get_Sr() const { return sR; }

	void input(TVector<ValType> vals, TVector<ValType> colums, TVector<ValType> rows)
	{
		for (int i = 0; i < this->Size; i++)
		{
			this->pVector[0][i] = vals[i];
			this->pVector[1][i] = colums[i];
		}
		this->pVector[2] = rows;
	}
	void print()
	{
		for (int row = 0; row < this->sR; ++row)
		{
			for (int i = this->pVector[2][row]; i < this->pVector[2][row + 1]; ++i)
			{
				cout << this->pVector[0][i] << " ";
			}
			cout << "\n";
		}
	}

	// ����/�����
	friend istream& operator>>(istream& in, RazrMatrix& mt)
	{
		for (int i = 0; i < 3; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const RazrMatrix& mt)
	{
		for (int i = 0; i < 3; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

	void WriteFile(std::string path)	// ����� � ����
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

	void ReadFile(std::string path, RazrMatrix& mt)	// ������ � �����
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
RazrMatrix<ValType>::RazrMatrix(int r, int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
	{
		bad_alloc exp;
		throw exp;
	}
	sR = r;
	this->pVector[0] = TVector<ValType>(s, 0);
	this->pVector[1] = TVector<ValType>(s, 0);
	this->pVector[2] = TVector<ValType>(r, 0);
}

template <class ValType> // ����������� �����������
RazrMatrix<ValType>::RazrMatrix(const RazrMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
RazrMatrix<ValType>::RazrMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool RazrMatrix<ValType>::operator==(const RazrMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool RazrMatrix<ValType>::operator!=(const RazrMatrix<ValType>& mt) const
{
	return !(operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
RazrMatrix<ValType>& RazrMatrix<ValType>::operator=(const RazrMatrix<ValType>& mt)
{
	TVector < TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
RazrMatrix<ValType> RazrMatrix<ValType>::operator+(const RazrMatrix<ValType>& mt)
{
	RazrMatrix<ValType> res(this->sR, this->Size);
	res.pVector[0] = this->pVector[0] + mt.pVector[0];
	res.pVector[1] = this->pVector[1];
	res.pVector[2] = this->pVector[2];

	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
RazrMatrix<ValType> RazrMatrix<ValType>::operator-(const RazrMatrix<ValType>& mt)
{
	RazrMatrix<ValType> res(this->sR, this->Size);
	res.pVector[0] = this->pVector[0] - mt.pVector[0];
	res.pVector[1] = this->pVector[1];
	res.pVector[2] = this->pVector[2];

	return res;
} /*-------------------------------------------------------------------------*/

template<class ValType>
inline RazrMatrix<ValType> RazrMatrix<ValType>::operator*(const RazrMatrix& mt)
{
	if (this->Size != mt.Size)
		throw "Error size";
	RazrMatrix <ValType> resault(this->sR,this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = 0; j < this->Size; j++)
		{
			resault.pVector[0][i] += this->pVector[0][i] * mt.pVector[0][j];
		} 
	}
	resault.pVector[1] = this->pVector[1];
	resault.pVector[2] = this->pVector[2];
	return resault;
}

template<class ValType>
inline RazrMatrix<ValType> RazrMatrix<ValType>::operator*(const ValType& num)
{
	RazrMatrix <ValType> resault(this->sR, this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		resault.pVector[0][i] = this->pVector[0][i] * num;
	}
	resault.pVector[1] = this->pVector[1];
	resault.pVector[2] = this->pVector[2];
	return resault;
}

template<class ValType>
inline RazrMatrix<ValType> RazrMatrix<ValType>::operator+(const ValType& num)
{
	RazrMatrix <ValType> resault(this->sR, this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		resault.pVector[0][i] = this->pVector[0][i] + num;
	}
	resault.pVector[1] = this->pVector[1];
	resault.pVector[2] = this->pVector[2];
	return resault;
}

template<class ValType>
inline RazrMatrix<ValType> RazrMatrix<ValType>::operator-(const ValType& num)
{
	RazrMatrix <ValType> resault(this->sR, this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		resault.pVector[0][i] = this->pVector[0][i] - num;
	}
	resault.pVector[1] = this->pVector[1];
	resault.pVector[2] = this->pVector[2];
	return resault;
}

//Tape Matrix
template <class ValType>
class TapeMatrix : public TVector<TVector<ValType> >
{
private:
	int sizeTape;	// ������ �����
public:
	TapeMatrix(int sT_, int s = 10);
	TapeMatrix(const TapeMatrix& mt);                    // �����������
	TapeMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const TapeMatrix& mt) const;      // ���������
	bool operator!=(const TapeMatrix& mt) const;      // ���������
	TapeMatrix& operator= (const TapeMatrix& mt);        // ������������
	TapeMatrix  operator+ (const TapeMatrix& mt);        // ��������
	TapeMatrix  operator- (const TapeMatrix& mt);        // ���������
	TapeMatrix  operator* (const TapeMatrix& mt);		   // �����������

	TapeMatrix  operator+ (const ValType& num);
	TapeMatrix  operator- (const ValType& num);
	TapeMatrix  operator* (const ValType& num);

	// ����/�����
	friend istream& operator>>(istream& in, TapeMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TapeMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

	void WriteFile(std::string path)	// ����� � ����
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

	void ReadFile(std::string path, TapeMatrix& mt)	// ������ � �����
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
TapeMatrix<ValType>::TapeMatrix(int sT_, int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
	{
		bad_alloc exp;
		throw exp;
	}
	for (int i = 0; i < s; i++)
	{
		if (i - 1 < 0)
		{
			if (i + 1 < s)
			{
				this->pVector[i] = TVector<ValType>(sT_ - 1, i);
			}
			else
			{
				this->pVector[i] = TVector<ValType>(sT_ - 2, i);
			}
		}
		else
		{
			if (i + 1 < s)
			{
				this->pVector[i] = TVector<ValType>(sT_, i - 1);
			}
			else
			{
				this->pVector[i] = TVector<ValType>(sT_ - 1, i - 1);
			}

			//this->pVector[i] = TVector<ValType>(s, 0);
		}
		sizeTape = sT_;
	}
}

template <class ValType> // ����������� �����������
TapeMatrix<ValType>::TapeMatrix(const TapeMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TapeMatrix<ValType>::TapeMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TapeMatrix<ValType>::operator==(const TapeMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TapeMatrix<ValType>::operator!=(const TapeMatrix<ValType>& mt) const
{
	return !(operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TapeMatrix<ValType>& TapeMatrix<ValType>::operator=(const TapeMatrix<ValType>& mt)
{
	TVector < TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TapeMatrix<ValType> TapeMatrix<ValType>::operator+(const TapeMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TapeMatrix<ValType> TapeMatrix<ValType>::operator-(const TapeMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

template<class ValType>
inline TapeMatrix<ValType> TapeMatrix<ValType>::operator*(const TapeMatrix& mt)
{
	if (this->Size != mt.Size)
		throw "Error size";
	TapeMatrix <ValType> resault(this->sizeTape, this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = i; j < this->Size; j++)
		{
			for (int k = i; k < j + 1; k++)
			{
				resault.pVector[i][j] += this->pVector[i][k] * mt.pVector[k][j];
			}
		}
	}
	return resault;
}

template<class ValType>
inline TapeMatrix<ValType> TapeMatrix<ValType>::operator*(const ValType& num)
{
	TapeMatrix res(this->sizeTape, this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TapeMatrix::pVector[i] * num;
	return res;
}

template<class ValType>
inline TapeMatrix<ValType> TapeMatrix<ValType>::operator+(const ValType& num)
{
	TapeMatrix res(this->sizeTape, this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TapeMatrix::pVector[i] + num;
	return res;
}

template<class ValType>
inline TapeMatrix<ValType> TapeMatrix<ValType>::operator-(const ValType& num)
{
	TapeMatrix res(this->sizeTape, this->Size);
	for (int i = 0; i < this->Size; i++)
		res.pVector[i] = TapeMatrix::pVector[i] - num;
	return res;
}