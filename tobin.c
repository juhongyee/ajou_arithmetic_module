int toBinaryString(char buf[], int a) 
{
	int i=0;
	for (i=0; i< 32; i++)
	{
		buf[i] = a  & (1<< (31-i)) ? '1' : '0'; 
	}
  	buf[i] = 0;
  	return 1;
}
