#include <gtest/gtest.h>
#include <kmeans/collections/list.h>
#include <kmeans/geometry/point.h>

TEST(GenericList, CreateEmptyList)
{
	struct KM_List *list = KM_List_Create();
	ASSERT_EQ(list->size, 0);
	if (list->head != NULL)
		FAIL();
	KM_List_Destroy(list);
}

TEST(GenericList, InsertOneElement)
{
	unsigned int i = 2;
	struct KM_List *list = KM_List_Create();
	KM_List_Add(list, &i);
	ASSERT_EQ(list->size, 1);
	KM_List_Destroy(list);
}

TEST(GenericList, InsertElementAndRetrieveIt)
{
	unsigned int i = 2;
	unsigned int j = 4;
	struct KM_List *list = KM_List_Create();
	KM_List_Add(list, &i);
	KM_List_Add(list, &j);
	ASSERT_EQ(list->size, 2);
	int result = *((int*) KM_List_Remove(list, 1));
	ASSERT_EQ(result, j);
	result = *((int*) KM_List_Remove(list, 0));
	ASSERT_EQ(result, i);
	void * resultPointer = (void*) KM_List_Remove(list, 0);
	if (resultPointer != NULL)
		FAIL();
	KM_List_Destroy(list);
}

TEST(GenericList, RetrieveElement)
{
	unsigned int i = 2;
	unsigned int j = 4;
	struct KM_List *list = KM_List_Create();
	KM_List_Add(list, &i);
	KM_List_Add(list, &j);
	ASSERT_EQ(list->size, 2);
	int result = *((int*) KM_List_Get(list, 1));
	ASSERT_EQ(result, j);
	result = *((int*) KM_List_Get(list, 0));
	ASSERT_EQ(result, i);
	KM_List_Destroy(list);
}

TEST(GenericList, ToArray)
{
	unsigned int *array = NULL;
	unsigned int i = 2;
	unsigned int j = 4;
	struct KM_List *list = KM_List_Create();
	KM_List_Add(list, &i);
	KM_List_Add(list, &j);

	KM_LIST_TOARRAY(list, array, unsigned int);
	ASSERT_FALSE(array == NULL);

	ASSERT_EQ(array[0], i);
	ASSERT_EQ(array[1], j);

	free(array);
}

TEST(GenericList, ToArrayUsingPoints)
{
	double coord1[2] = { 0.3, 2.2 };
	double coord2[2] = { 3.2, 5.7 };
	struct KM_Point *p1 = KM_Point_Create(2, &coord1);
	struct KM_Point *p2 = KM_Point_Create(2, &coord2);
	struct KM_List *list = KM_List_Create();
	KM_List_Add(list, p1);
	KM_List_Add(list, p2);

	struct KM_Point *array = NULL;

	KM_LIST_TOARRAY(list, array, struct KM_Point);

	ASSERT_FALSE(array == NULL);
	ASSERT_EQ(array[0].coord[0], coord1[0]);
	ASSERT_EQ(array[0].coord[1], coord1[1]);
	ASSERT_EQ(array[1].coord[0], coord2[0]);
	ASSERT_EQ(array[1].coord[1], coord2[1]);

	KM_Point_Destroy(p1);
	KM_Point_Destroy(p2);
	KM_List_Destroy(list);
}