#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define PATH_FILE "sample.dat"

#ifndef DATATYPE
#define DATATYPE

//#define SCANFORMAT "%f"
//#define PRNFORMAT "%10.6f"

#define SCANFORMAT "%d"
#define PRNFORMAT " %2d"
typedef int EType;
#endif

#ifndef DATASET
#define DATASET
typedef struct
{
	int rows;
	int cols;
	int length;
	EType *elem;

} DataSet;
#endif

static DataSet *ReadData(const char *fileName);
static void DestroyData(DataSet *dataSet);
static void PrintData(DataSet *dataSet);
int compare(const void *arg1, const void *arg2);

/*
int main(int argc, char *argv[])
{
	DataSet *setData = NULL;


	setData = ReadData(PATH_FILE);
	PrintData(setData);
	printf("\n");

	DestroyData(setData);
	return 0;
}
*/


static DataSet *ReadData(const char *fileName)
{
	DataSet *out = NULL; // Return
	FILE *inFile = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int rows = 0, cols = 0;
	int col = 0, length = 0;

	if (!(inFile = fopen(fileName, "r")))
	{
		abort();
	}

	out = (DataSet *)malloc(sizeof(DataSet));
	if (!out)
	{
		abort();
	}
	memset(out, 0x00, sizeof(DataSet));
	fscanf_s(inFile, "%d%d%d", &rows, &cols, &length);

	out->rows = rows;
	out->cols = cols;
	out->length = length;

	printf("%d %d %d\n", rows, cols, length);
	printf("\n");

	out->elem = (EType  *)malloc(length * sizeof(EType));
	if (!out->elem)
	{
		abort();
	}
	memset(out->elem, 0x00, (length * sizeof(EType)));

	begin = out->elem;
	end = out->elem + length;

	while (fscanf(inFile, SCANFORMAT, begin++) != EOF)
	{
		if (begin == end)
			break;
	}

	fclose(inFile);

	return out;
}

void DestroyData(DataSet *dataSet)
{
	if (!dataSet)
		return;

	if (!dataSet->elem)
		goto DESTROY;

	free(dataSet->elem);
	dataSet->elem = NULL;

DESTROY:
	free(dataSet);
	dataSet = NULL;
}

static void PrintData(DataSet *dataSet)
{
	DataSet *setData = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int rows = 0, cols = 0;
	int col = 0;
	int length = 0;

	setData = dataSet;
	if (!setData) return;

	rows = setData->rows;
	cols = setData->cols;
	length = setData->length;

	begin = setData->elem;
	if (!begin) return;

	end = begin + length;

	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)
		{
			col = 0;
			printf("\n");
		}
		printf(PRNFORMAT, *begin); printf(" ");
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////

#ifndef HISTOGRAM
#define HISTOGRAM
typedef struct
{
	int length;
	int *elem;

}Histogram;

#endif

static Histogram *CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel);
static void DestroyHistogram(Histogram *histogram);
static void PrintHistogram(Histogram *histogram, const int minLevel, int maxLevel, const int intervalLevel);

static void SortQuick(EType *dataSet, const int posposleft, const int posposright);
static void Swap(EType *src, EType *dst);


int main(int argc, char *argv[])
{
	DataSet *setData = NULL;
	Histogram *histogram = NULL;

	setData = ReadData(PATH_FILE);
	PrintData(setData);
	printf("\n");

	histogram = CreateHistogram(setData, 40, 80 ,5);
	if(!histogram)
	{
		abort();
	}

	PrintHistogram(histogram, 40, 80, 5);
	printf("\n");

	//DestroyHistogram(histogram);
	DestroyData(setData);
	
	return 0;
}

static Histogram *CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel)
{
	FILE *inFile;
	Histogram *newHisto = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	newHisto = (Histogram *)malloc(sizeof(Histogram));
	if (!newHisto)
	{
		abort();
	}
	memset(newHisto, 0x00, sizeof(Histogram));

	newHisto->length=dataSet->length;

	newHisto->elem = (EType  *)malloc(newHisto->length * sizeof(EType));
	if (!newHisto->elem)
	{
		abort();
	}
	memset(newHisto->elem, 0x00, (newHisto->length * sizeof(EType)));

	begin = newHisto->elem;
	end = newHisto->elem + newHisto->length;

	while (dataSet->elem != EOF)
	{
		if (begin == end)
			break;
		newHisto->elem=dataSet->elem;
		begin++;
	}


	qsort((void *)newHisto->elem, (size_t)newHisto->length, sizeof(EType), compare);//퀵정렬을 해야함

	return newHisto;

}

static void DestroyHistogram(Histogram *histogram)
{

}

static void PrintHistogram(Histogram *histogram, const int minLevel, int maxLevel, const int intervalLevel)
{
	Histogram *setHisto = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int col=0;
	int length = 0;

	setHisto = histogram;
	if (!setHisto) return;

	length = setHisto->length;

	begin = setHisto->elem;
	if (!begin) return;

	end = begin + length;

	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= 10)
		{
			col = 0;
			printf("\n");
		}
		printf(PRNFORMAT, *begin); printf(" ");
	}
	printf("\n");

	printf("\t Leve | Freq' \n");
	printf("------------------------------------------------");
	//for(int 
}

////

static void SortQuick(EType *dataSet, const int posleft, const int posright)
{

 
 }

int compare(void *arg1, void *arg2)
{
	if( *(EType*)arg1 > *(EType*)arg2) return 1;
	else if( *(EType*)arg1 == *(EType*)arg2) return 0;
	else return -1;
}

static void Swap(EType *src, EType *dst)
{
	EType *middle;
	middle = dst;

	if(src<=dst)
		return;
	else {
		dst=src;
		src = middle;
	}
}