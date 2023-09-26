RGB_MATRIX_EFFECT(trans_flag)
RGB_MATRIX_EFFECT(vert_hue_gradient)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
// first i in row, 0 to 5, plus an upper bound for the last row
const uint8_t ROW_START_I[7] = {0, 16, 33, 50, 63, 76, 87};
const uint8_t ROWS = 6;

/// transgender flag on 6 rows
static bool trans_flag(effect_params_t* params) {
    void set_row(HSV hsv, uint8_t row_idx) {
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

        for (uint8_t i = ROW_START_I[row_idx]; i < ROW_START_I[row_idx + 1]; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t val = rgb_matrix_config.hsv.v;
    HSV cyan = {HSV_CYAN}; cyan.v = val;
    HSV pink = {HSV_PINK}; pink.v = val;
    HSV white = {HSV_WHITE}; white.v = val;

    set_row(cyan, 0);
    set_row(pink, 1);
    set_row(white, 2);
    set_row(white, 3);
    set_row(pink, 4);
    set_row(cyan, 5);

    return rgb_matrix_check_finished_leds(led_max);
}

// patched version of GRADIENT_UP_DOWN with 6 lines instead of 5
bool vert_hue_gradient(effect_params_t* params) {
    void set_row(HSV hsv, uint8_t row_idx) {
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

        for (uint8_t i = ROW_START_I[row_idx]; i < ROW_START_I[row_idx + 1]; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);
    for (uint8_t i = 0; i < ROWS; i++) {
        hsv.h = rgb_matrix_config.hsv.h + scale * i;
        set_row(hsv, i);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
