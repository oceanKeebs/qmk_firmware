#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "quantum.h"
#include "i2c_master.h"
#include "print.h"

#define EXPANDER_ROWS 5
#define EXPANDER_COLS 22

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

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
    i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

    // Set Pull-up
    i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
    
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
        default :
            // Default for actual pins on the Pro Micro
            setPinOutput(row_pins[row]);
            writePinLow(row_pins[row]);
    }

    // Set Output if Row is on Expander
    if (Expander_Row > 0) {
        i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
        i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
    }
    
}


static void init_pins(void) {
    unselect_rows();

    // Set all rows with pins on Pro Micro as Input
    for (uint8_t x = EXPANDER_COLS; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

void matrix_init_custom(void) {
    // Initialize I2C
    i2c_init();
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
    //dprintf("current row: %d \n", current_row);
    //matrix_io_delay(); Ersetzt durch wait da 30 us nicht reichen
    wait_us(30);

    uint8_t port_expander0_col_buffer[2];
    uint8_t port_expander1_col_buffer[2];
    i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20);
    i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin_state;
        // Select the col pin to read (active low)
        switch (col_index) {
            case 0 :
                pin_state = port_expander0_col_buffer[0] & (1 << 5);
                break;
            case 1 :
                pin_state = port_expander0_col_buffer[0] & (1 << 6);
                break;
            case 2 :
                pin_state = port_expander0_col_buffer[0] & (1 << 7);
                break;
            case 3 :
                pin_state = port_expander0_col_buffer[1] & (1 << 0);
                break;
            case 4 :
                pin_state = port_expander0_col_buffer[1] & (1 << 1);
                break;
            case 5 :
                pin_state = port_expander0_col_buffer[1] & (1 << 2);
                break;
            case 6 :
                pin_state = port_expander0_col_buffer[1] & (1 << 3);
                break;
            case 7 :
                pin_state = port_expander0_col_buffer[1] & (1 << 4);
                break;
            case 8 :
                pin_state = port_expander0_col_buffer[1] & (1 << 5);
                break;
            case 9 :
                pin_state = port_expander0_col_buffer[1] & (1 << 6);
                break;
            case 10 :
                pin_state = port_expander0_col_buffer[1] & (1 << 7);
                break;
            case 11 :
                pin_state = port_expander1_col_buffer[1] & (1 << 7);
                break;
            case 12 :
                pin_state = port_expander1_col_buffer[1] & (1 << 6);
                break;
            case 13 :
                pin_state = port_expander1_col_buffer[1] & (1 << 5);
                break;
            case 14 :
                pin_state = port_expander1_col_buffer[1] & (1 << 4);
                break;
            case 15 :
                pin_state = port_expander1_col_buffer[1] & (1 << 3);
                break;
            case 16 :
                pin_state = port_expander1_col_buffer[1] & (1 << 2);
                break;
            case 17 :
                pin_state = port_expander1_col_buffer[1] & (1 << 1);
                break;
            case 18 :
                pin_state = port_expander1_col_buffer[1] & (1 << 0);
                break;
            case 19 :
                pin_state = port_expander1_col_buffer[0] & (1 << 7);
                break;
            case 20 :
                pin_state = port_expander1_col_buffer[0] & (1 << 6);
                break;
            case 21 :
                pin_state = port_expander1_col_buffer[0] & (1 << 5);
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
