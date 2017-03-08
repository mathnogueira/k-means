#include <gtest/gtest.h>
#include <kmeans/collections/list.h>

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