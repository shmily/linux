
void BuildGoodSuffixShift(const char *pattern, int plen, int *shift)
{
  shift[plen-1] = 1;
  char end_val = pattern[plen-1];
  char const* p_prev;
  char const* p_next;
  char const* p_temp;
  char const* p_now = pattern + plen - 2;

  int isgoodsuffixfind = 0;

  for(int i=plen-2; i>=0; --i; --p_now){
    
    p_temp = pattern + plen - 1;
    isgoodsuffixfind = 0;

    while(1){
      
    }
  }
}
