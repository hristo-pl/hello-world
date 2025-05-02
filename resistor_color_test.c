#include<stdio.h>
#include<assert.h>
#include "resistor_color.c"

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_black(void) {
    int code = color_code(BLACK);
    assert(code == 0);
}

static void test_white(void) {
    int code = color_code(WHITE);
    assert(code == 9);
}

static void test_orange(void) {
    int code = color_code(ORANGE);
    assert(code == 3);
}

/*
static void test_colors(void)
{
   TEST_IGNORE();
   const resistor_band_t expected[] = { BLACK, BROWN, RED,    ORANGE, YELLOW,
                                        GREEN, BLUE,  VIOLET, GREY,   WHITE };
   const resistor_band_t *actual = colors();
   TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, ARRAY_LENGTH(expected));
}
*/
int main(void)
{
    test_black();
    test_white();
    test_orange();

    resistor_band_t testConst = BLACK;

    printf("\n");
    printf("code of BLACK is %d", color_code(testConst));
    printf("\n%d", testConst);
    printf("\n");
}