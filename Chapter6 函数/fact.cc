int fact(int n)
{
	int result = 1;
	while (n > 0)
		result *= n--;
	return result;
}