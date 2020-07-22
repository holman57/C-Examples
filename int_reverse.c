int reverse(int x)
{
  long int r = 0;
  for (;x != 0;)
  {
    r = r * 10 + (long)(x) % 10;
    x /= 10;
  }
  int i_max = (int)(~(uint)(0) >> (uint)(1));
  int i_min = -i_max - 1;
  if (r > i_max || r < i_min)
  {
    return 0;
  }
  return (int)(r);
}