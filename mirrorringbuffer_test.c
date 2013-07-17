/*
 * mirrorringbuffer_test.c
 *
 *  Created on: 2013-7-17
 */

#include <stdio.h>
#include <assert.h>

#include "mirrorringbuffer.h"


#define BUFFER_SIZE     8

int main(int arc, char** argv)
{
  CircularBuffer ringbuffer;
  ElemType mocUp;
  int rc, i;

  cbInit(&ringbuffer, BUFFER_SIZE);

  rc= cbIsEmpty(&ringbuffer);
  assert(rc==1);
  printf("cbIsEmpty empty passed\n");
  rc= cbIsFull(&ringbuffer);
  assert(rc==0);
  printf("cbIsFull not full passed\n");

  mocUp.id=0;
  cbWrite(&ringbuffer,  &mocUp);

  rc= cbIsEmpty(&ringbuffer);
  assert(rc==0);

  for(i=1;i<3;i++)
  {
      mocUp.id=i;
      cbWrite(&ringbuffer,  &mocUp);
  };

  rc= cbIsEmpty(&ringbuffer);
  assert(rc==0);
  printf("cbIsEmpty not empty passed\n");
  rc= cbIsFull(&ringbuffer);
  assert(rc==0);


  for(i=3;i<BUFFER_SIZE;i++)
  {
      mocUp.id=i;
      cbWrite(&ringbuffer,  &mocUp);
  };
  rc= cbIsEmpty(&ringbuffer);
  assert(rc==0);
  rc= cbIsFull(&ringbuffer);
  assert(rc==1);
  printf("cbIsFull full passed\n");
  printf("cbIsFull write passed\n");

  cbRead(&ringbuffer, &mocUp);
  rc= cbIsFull(&ringbuffer);
  assert(rc==0);
  assert(mocUp.id==0);
  printf("cbIsFull read passed\n");

  return 0;
}
