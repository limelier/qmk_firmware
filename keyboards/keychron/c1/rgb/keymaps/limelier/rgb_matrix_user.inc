RGB_MATRIX_EFFECT(trans_flag)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool trans_flag(effect_params_t* params) {
    // first i in row, 0 to 5, plus an upper bound for the last row
    const uint8_t ROW_START_I[7] = {0, 16, 33, 50, 63, 76, 87};

    // set an entire row to a HSV value
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

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS