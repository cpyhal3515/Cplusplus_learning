#ifndef SECTION1_H
#define SECTION1_H

template<typename I, typename T>
I Find(I b, I e, const T& v)
{
	for (; b != e; ++b)
	{
		if (*b == v)
		{
			return b;
		}
	}
	return e;
}


template<typename T, std::size_t N>
void print(const T (&arr)[N])
{
	for (const auto& elem : arr)
	{
		std::cout << elem;
	}
	std::cout << std::endl;
}


#endif //SECTION1_H