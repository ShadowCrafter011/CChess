#include "test_list.h"
#include "list.h"

MunitResult test_list(const MunitParameter params[], void *data)
{
    (void) params;
    (void) data;

    List list;
    init_list(&list);

    munit_assert_not_null(list.values);

    for (int i = 0; i < 320; i++)
    {
        add_item(&list, i);
    }

    munit_assert_int(list.length, ==, 320);
    munit_assert_int(list.size, ==, 400);

    for (int i = 0; i < 320; i++)
    {
        munit_assert_int(i, ==, list.values[i]);
    }

    free_list(&list);

    return MUNIT_OK;
}
