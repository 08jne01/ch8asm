#pragma once
template <class T> class Table
{
public:
	Table(int width, int height, int depth):
		m_width(width), m_height(height), m_depth(depth)
	{
		m_array = new T[width * height * depth];
	}
	~Table()
	{
		if (m_array)
			delete m_array;
	}
	inline const T& operator()(int i, int j, int k) const
	{
		return m_array[i + m_width * (j + k * m_depth)];
	}
	inline T& operator()(int i, int j, int k)
	{
		return m_array[i + m_width * (j + k * m_depth)];
	}
private:
	int m_width, m_height, m_depth;
	T* m_array;
};