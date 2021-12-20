#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turbojpeg.h"

int yuv2jpg(const unsigned char *pYuvData, const int width, const int height,unsigned char* pDest, unsigned long* pSize)
{
  tjhandle handle = NULL;
  int pad = 4;
  int flags = TJFLAG_NOREALLOC;
  int subsamp = TJSAMP_420;

  handle = tjInitCompress();

  tjCompressFromYUV(handle, pYuvData, width, pad, height, subsamp, &pDest, pSize,80, flags );

  tjDestroy(handle);

  return 0;
}

int main()
{
  unsigned char *pYUV = (unsigned char *)malloc(256*256*3/2);
  unsigned char *pDest= (unsigned char *)malloc(256*256*3/2);
  unsigned long  size=0;
  FILE *pf = fopen("F:\\yuv2jpg\\yuv2jpg\\test.yuv", "rb");
  if(NULL == pf)
  {
    return 0;
  }
  fread(pYUV, 256*256*3/2, 1, pf);
  fclose(pf);

  yuv2jpg(pYUV, 256, 256, pDest, &size);

  FILE *pf1 = fopen("new.jpg", "wb+");
  if(NULL == pf1)
  {
    return 0;
  }
  fwrite(pDest, size, 1, pf1);
  fclose(pf1);

  free(pYUV);
  free(pDest);

  return 0;
}
