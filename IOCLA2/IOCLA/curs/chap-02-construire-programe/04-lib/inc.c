static unsigned int num_items;

void init(void)
{
	num_items = 0;
}
void increment(void)
{
	num_items++;
}

unsigned int read(void)
{
	return num_items;
}
