// #include "resistor_color.c"

typedef enum {
    BLACK, //0
    BROWN, //1
    RED, //2
    ORANGE, //3
    YELLOW, //4
    GREEN, //5
    BLUE, //6
    VIOLET, //7
    GREY, //8
    WHITE //9
} resistor_band_t;

int color_code(resistor_band_t color);

// Function to return the color code
//int color_code(enum resistor_band_t color);

// Function to return an array of all colors
// const resistor_band_t* colors(void);
