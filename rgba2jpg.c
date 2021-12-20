//gcc -g turborgb2jpg.c  -lturbojpeg -L./
//./a.out

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "turbojpeg.h"

unsigned char *pDest1;
void init(const int width, const int height)
{
  pDest1 = tjAlloc(width * height * 4);
}

void uninit()
{
  tjFree(pDest1);
}

int rgb2jpg(const char *pRgbData, const int width, const int height, int type, char* pDest, unsigned long* pSize)
{
  tjhandle handle = NULL;
  int flags = TJFLAG_NOREALLOC;
  int subsamp = TJSAMP_422;
  int pixelfmt = TJPF_RGBA;
  
  handle = tjInitCompress();
  
  tjCompress2(handle, pRgbData, width, 0, height, pixelfmt, &pDest1, pSize, subsamp, 80, flags);
  tjDestroy(handle);
  memcpy(pDest, pDest1, *pSize);
  
    return 0;
}

int main()
{
  struct timeval begin, end;
  char *pRGB = (char *)malloc(626*375*4);
  char pDest[626*375*4];
  int  size=0;
  FILE *pf = fopen("test.rgb", "rb");
  if(NULL == pf)
  {
    return 0;
  }
  fread(pRGB, 626*375*4, 1, pf);
  
  gettimeofday(&begin, NULL);
  // int ret = rgb2jpg(pRGB, 626, 375, 1, "/tmp/syj/libjpeg-turbo-2.1.0/bint/lib64/jpg.jpg", NULL);
  init(626, 375);
  int ret = rgb2jpg(pRGB, 626, 375, 0, &pDest, &size);
  
  gettimeofday(&end, NULL);
  long long totaltime = (end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec - begin.tv_usec);
  printf("%lld us\n", totaltime);
  printf("size %d \n", size);
  
  FILE *pf1 = fopen("new.jpg", "wb+");
  if(NULL == pf1)
  {
    return 0;
  }
  fwrite(pDest, size, 1, pf1);
  fclose(pf1);
  
  free(pRGB);
  return 0;
}
