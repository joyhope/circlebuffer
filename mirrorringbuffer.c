/*
 * mirrorringbuffer.c
 *
 *  Created on: 2013-7-17
 */
#include <stdio.h>
#include <stdlib.h>
#include "mirrorringbuffer.h"

void
cbInit(CircularBuffer *cb, int size)
{
  cb->size = size;
  cb->start = 0;
  cb->end = 0;
  cb->s_msb = 0;
  cb->e_msb = 0;
  cb->elems = (ElemType *) calloc(cb->size, sizeof(ElemType));
}

int
cbIsFull(CircularBuffer *cb)
{
  return cb->end == cb->start && cb->e_msb != cb->s_msb;
}

int
cbIsEmpty(CircularBuffer *cb)
{
  return cb->end == cb->start && cb->e_msb == cb->s_msb;
}

void
cbIncr(CircularBuffer *cb, int *p, int *msb)
{
  *p = *p + 1;
  if (*p == cb->size)
  {
      *msb ^= 1;
      *p = 0;
  }
}

void
cbWrite(CircularBuffer *cb, ElemType *elem)
{
  cb->elems[cb->end] = *elem;
  if (cbIsFull(cb)) /* full, overwrite moves start pointer */
    cbIncr(cb, &cb->start, &cb->s_msb);
  cbIncr(cb, &cb->end, &cb->e_msb);
}

void
cbRead(CircularBuffer *cb, ElemType *elem)
{
  *elem = cb->elems[cb->start];
  cbIncr(cb, &cb->start, &cb->s_msb);
}

