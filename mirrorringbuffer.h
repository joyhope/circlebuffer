/*
 * mirrorringbuffer.h
 *
 *  Created on: 2013-7-17
 */

#ifndef MIRRORRINGBUFFER_H_
#define MIRRORRINGBUFFER_H_

typedef char  ElemType[16];

/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         end;    /* index at which to write new element  */
    int         s_msb;
    int         e_msb;
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;


extern void cbInit(CircularBuffer *cb, int size);
extern int cbIsFull(CircularBuffer *cb);
extern int cbIsEmpty(CircularBuffer *cb);
extern void cbIncr(CircularBuffer *cb, int *p, int *msb);
extern void cbWrite(CircularBuffer *cb, ElemType *elem);
extern void cbRead(CircularBuffer *cb, ElemType *elem);

#endif /* MIRRORRINGBUFFER_H_ */
