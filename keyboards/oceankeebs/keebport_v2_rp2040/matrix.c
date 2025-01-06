#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "quantum.h"
#include "i2c_master.h"
#include "print.h"

#define EXPANDER_ROWS 10
#define EXPANDER_COLS 22

// Option to turn of i2c for debugging
#define USE_I2C true
#define USE_I2C_EXPANDER0 true
#define USE_I2C_EXPANDER1 true
#define USE_I2C_EXPANDER2 true
#define USE_I2C_EXPANDER3 true

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

bool expander0error = false;
bool expander1error = false;
bool expander2error = false;
bool expander3error = false;

#define DEBUGMSG_EVERY_COUNT 30000
uint16_t debugCounter = 0;

static void unselect_rows(void) {
    uint8_t send_data[2] = { 0xFF, 0xFF};

    // i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
    // Registers:
    // 0x00     IODIRA      Input(1)/Output(0)
    // 0x01     IODIRB      Input(1)/Output(0)
    // 0x0C     GPPUA       PullUp
    // 0x0D     GPPUB       PullUp
    // 0x12     GPIOA       Level of IO
    // 0x13     GPIOB       Level of IO

    // Set all I/O to input
    if (USE_I2C_EXPANDER0 && USE_I2C) i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER1 && USE_I2C) i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER2 && USE_I2C) i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER3 && USE_I2C) i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

    // Set Pull-up
    if (USE_I2C_EXPANDER0 && USE_I2C) i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER1 && USE_I2C) i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER2 && USE_I2C) i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    if (USE_I2C_EXPANDER3 && USE_I2C) i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    
    for(uint8_t x = EXPANDER_ROWS; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }

}

static void select_row(uint8_t row) {
    // Set corresponding I/O pin to row to output
    uint8_t send_data[2] = { 0xFF, 0xFF};
    uint8_t Expander_Row = 0;

    // Set send_data to mask pins from Expander
    switch (row) {
        case 0:
            send_data[0] = 0xFE;
            send_data[1] = 0xFF;
            Expander_Row = 1;
            break;
        case 1:
            send_data[0] = 0xFD;
            send_data[1] = 0xFF;
            Expander_Row = 1;
            break;
        case 2:
            send_data[0] = 0xFB;
            send_data[1] = 0xFF;
            Expander_Row = 1;
            break;
        case 3:
            send_data[0] = 0xF7;
            send_data[1] = 0xFF;
            Expander_Row = 1;
            break;
        case 4:
            send_data[0] = 0xEF;
            send_data[1] = 0xFF;
            Expander_Row = 1;
            break;
        case 5:
            send_data[0] = 0xFE;
            send_data[1] = 0xFF;
            Expander_Row = 2;
            break;
        case 6:
            send_data[0] = 0xFD;
            send_data[1] = 0xFF;
            Expander_Row = 2;
            break;
        case 7:
            send_data[0] = 0xFB;
            send_data[1] = 0xFF;
            Expander_Row = 2;
            break;
        case 8:
            send_data[0] = 0xF7;
            send_data[1] = 0xFF;
            Expander_Row = 2;
            break;
        case 9:
            send_data[0] = 0xEF;
            send_data[1] = 0xFF;
            Expander_Row = 2;
            break;
        default :
            // Default for actual pins on the center controller
            setPinOutput(row_pins[row]);
            writePinLow(row_pins[row]);
    }

    // Set Output if Row is on Expander
    if (Expander_Row == 1) {
        if (USE_I2C_EXPANDER0 && USE_I2C) i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
        if (USE_I2C_EXPANDER1 && USE_I2C) i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    }
    else if (Expander_Row == 2) {
        if (USE_I2C_EXPANDER2 && USE_I2C) i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
        if (USE_I2C_EXPANDER3 && USE_I2C) i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    }
    
}

static void init_pins(void) {
    unselect_rows();

    // Set all rows with pins on center controller as Input
    for (uint8_t x = EXPANDER_COLS; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

void matrix_init_custom(void) {
    // Initialize I2C
    
    if (USE_I2C) i2c_init();
    dprint("i2c_init done");

    // Initialize key pins
    init_pins();
    dprint("pins_init done");
    wait_ms(50);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    uint8_t port_expander0_col_buffer[2];
    uint8_t port_expander1_col_buffer[2];
    uint8_t port_expander2_col_buffer[2];
    uint8_t port_expander3_col_buffer[2];

    if (USE_I2C_EXPANDER0 && USE_I2C) {
        if (i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20) == 0) expander0error = false;
        else expander0error = true;
    }
    else {
        expander0error = true;
        port_expander0_col_buffer[0] = 0;
        port_expander0_col_buffer[1] = 0;
    }

    if (USE_I2C_EXPANDER1 && USE_I2C) {
        if (i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20) == 0) expander1error = false;
        else expander1error = true;
        }
    else {
        expander1error = true;
        port_expander1_col_buffer[0] = 0;
        port_expander1_col_buffer[1] = 0;
    }

    if (USE_I2C_EXPANDER2 && USE_I2C) {
        if (i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20) == 0) expander2error = false;
        else expander2error = true;
        }
    else {
        expander2error = true;
        port_expander2_col_buffer[0] = 0;
        port_expander2_col_buffer[1] = 0;
    }

    if (USE_I2C_EXPANDER3 && USE_I2C) {
        if (i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20) == 0) expander3error = false;
        else expander3error = true;
        }
    else {
        expander3error = true;
        port_expander3_col_buffer[0] = 0;
        port_expander3_col_buffer[1] = 0;
    }

    if (debugCounter == DEBUGMSG_EVERY_COUNT) {
        debugCounter = 0;
        dprintf("expander0error: %i  expander1error: %i  expander2error: %i  expander3error: %i\n", expander0error, expander1error, expander2error, expander3error);
    }
    else debugCounter++;

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin_state;
        // Select the col pin to read (active low)
        switch (col_index) {
            case 0 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[0] & (1 << 5);
                else if (expander2error) pin_state = port_expander0_col_buffer[0] & (1 << 5);
                else pin_state = port_expander0_col_buffer[0] & (1 << 5) && port_expander2_col_buffer[0] & (1 << 5);
                break;
            case 1 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[0] & (1 << 6);
                else if (expander2error) pin_state = port_expander0_col_buffer[0] & (1 << 6);
                else pin_state = port_expander0_col_buffer[0] & (1 << 6) && port_expander2_col_buffer[0] & (1 << 6);
                break;
            case 2 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[0] & (1 << 7);
                else if (expander2error) pin_state = port_expander0_col_buffer[0] & (1 << 7);
                else pin_state = port_expander0_col_buffer[0] & (1 << 7) && port_expander2_col_buffer[0] & (1 << 7);
                break;
            case 3 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 0);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 0);
                else pin_state = port_expander0_col_buffer[1] & (1 << 0) && port_expander2_col_buffer[1] & (1 << 0);
                break;
            case 4 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 1);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 1);
                else pin_state = port_expander0_col_buffer[1] & (1 << 1) && port_expander2_col_buffer[1] & (1 << 1);
                break;
            case 5 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 2);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 2);
                else pin_state = port_expander0_col_buffer[1] & (1 << 2) && port_expander2_col_buffer[1] & (1 << 2);
                break;
            case 6 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 3);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 3);
                else pin_state = port_expander0_col_buffer[1] & (1 << 3) && port_expander2_col_buffer[1] & (1 << 3);
                break;
            case 7 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 4);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 4);
                else pin_state = port_expander0_col_buffer[1] & (1 << 4) && port_expander2_col_buffer[1] & (1 << 4);
                break;
            case 8 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 5);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 5);
                else pin_state = port_expander0_col_buffer[1] & (1 << 5) && port_expander2_col_buffer[1] & (1 << 5);
                break;
            case 9 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 6);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 6);
                else pin_state = port_expander0_col_buffer[1] & (1 << 6) && port_expander2_col_buffer[1] & (1 << 6);
                break;
            case 10 :
                if (expander0error && expander2error) pin_state = 1;
                else if (expander0error) pin_state = port_expander2_col_buffer[1] & (1 << 7);
                else if (expander2error) pin_state = port_expander0_col_buffer[1] & (1 << 7);
                else pin_state = port_expander0_col_buffer[1] & (1 << 7) && port_expander2_col_buffer[1] & (1 << 7);
                break;
            case 11 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 7);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 7);
                else pin_state = port_expander1_col_buffer[1] & (1 << 7) && port_expander3_col_buffer[1] & (1 << 7);
                break;
            case 12 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 6);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 6);
                else pin_state = port_expander1_col_buffer[1] & (1 << 6) && port_expander3_col_buffer[1] & (1 << 6);
                break;
            case 13 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 5);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 5);
                else pin_state = port_expander1_col_buffer[1] & (1 << 5) && port_expander3_col_buffer[1] & (1 << 5);
                break;
            case 14 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 4);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 4);
                else pin_state = port_expander1_col_buffer[1] & (1 << 4) && port_expander3_col_buffer[1] & (1 << 4);
                break;
            case 15 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 3);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 3);
                else pin_state = port_expander1_col_buffer[1] & (1 << 3) && port_expander3_col_buffer[1] & (1 << 3);
                break;
            case 16 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 2);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 2);
                else pin_state = port_expander1_col_buffer[1] & (1 << 2) && port_expander3_col_buffer[1] & (1 << 2);
                break;
            case 17 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 1);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 1);
                else pin_state = port_expander1_col_buffer[1] & (1 << 1) && port_expander3_col_buffer[1] & (1 << 1);
                break;
            case 18 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[1] & (1 << 0);
                else if (expander3error) pin_state = port_expander1_col_buffer[1] & (1 << 0);
                else pin_state = port_expander1_col_buffer[1] & (1 << 0) && port_expander3_col_buffer[1] & (1 << 0);
                break;
            case 19 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[0] & (1 << 7);
                else if (expander3error) pin_state = port_expander1_col_buffer[0] & (1 << 7);
                else pin_state = port_expander1_col_buffer[0] & (1 << 7) && port_expander3_col_buffer[0] & (1 << 7);
                break;
            case 20 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[0] & (1 << 6);
                else if (expander3error) pin_state = port_expander1_col_buffer[0] & (1 << 6);
                else pin_state = port_expander1_col_buffer[0] & (1 << 6) && port_expander3_col_buffer[0] & (1 << 6);
                break;
            case 21 :
                if (expander1error && expander3error) pin_state = 1;
                else if (expander1error) pin_state = port_expander3_col_buffer[0] & (1 << 5);
                else if (expander3error) pin_state = port_expander1_col_buffer[0] & (1 << 5);
                else pin_state = port_expander1_col_buffer[0] & (1 << 5) && port_expander3_col_buffer[0] & (1 << 5);
                break;
            default :
                pin_state = readPin(col_pins[col_index]);
        }

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_rows();
    // dprintf("current_matrix of current row: %d \n", current_matrix[current_row]);

    return (last_row_value != current_matrix[current_row]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_has_changed |= read_cols_on_row(current_matrix, current_row);
    }

    return matrix_has_changed;
}
