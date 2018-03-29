#ifndef __TCD_H__
#define __TCD_H__

#include "user.h"
#include "common.h"
#include "date.h"
#include <assert.h>


typedef struct TCD* TCD;

int idusercompare(const void* id1, const void* id2);
int idpostcompare(const void* id1, const void* id2);
int datacompare(Date data1, Date data2);
TCD init();
void insereUser();
void inserePost();
void freeTCD();
