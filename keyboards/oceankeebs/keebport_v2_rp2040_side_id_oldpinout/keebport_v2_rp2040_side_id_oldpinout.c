#include "quantum.h"
#include "i2c_master.h"
#include "wait.h"
#include "side_id.h"

// The first four layers gets a name for readability, which is then used in the OLED below.
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST
};

uint8_t expander0_ID = 0;
uint8_t expander1_ID = 0;
uint8_t expander2_ID = 0;
uint8_t expander3_ID = 0;

void keyboard_pre_init_kb(void) {
  i2c_init();

  uint8_t send_data[2] = {0xFF, 0xFF};
  
  uint8_t port_expander0_col_buffer[2];
  uint8_t port_expander1_col_buffer[2];
  uint8_t port_expander2_col_buffer[2];
  uint8_t port_expander3_col_buffer[2];

  bool expander0error = false;
  bool expander1error = false;
  bool expander2error = false;
  bool expander3error = false;

  uint8_t expander0_ID_scan = 0;
  uint8_t expander1_ID_scan = 0;
  uint8_t expander2_ID_scan = 0;
  uint8_t expander3_ID_scan = 0;

  //select row 0/5
  send_data[0] = 0xFE;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

  wait_us(30);

  if (i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20) == 0) expander0error = false;
  else expander0error = true;
  if (i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20) == 0) expander1error = false;
  else expander1error = true;
  if (i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20) == 0) expander2error = false;
  else expander2error = true;
  if (i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20) == 0) expander3error = false;
  else expander3error = true;
  
  if(!expander0error) expander0_ID_scan += !((port_expander0_col_buffer[0] & (1 << 5)) >> 5);
  if(!expander1error) expander1_ID_scan += !((port_expander1_col_buffer[0] & (1 << 5)) >> 5);
  if(!expander2error) expander2_ID_scan += !((port_expander2_col_buffer[0] & (1 << 5)) >> 5);
  if(!expander3error) expander3_ID_scan += !((port_expander3_col_buffer[0] & (1 << 5)) >> 5);

  //unselect rows (set to input and set pull-up)
  send_data[0] = 0xFF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);

  //select row 1/6
  send_data[0] = 0xFD;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

  wait_us(30);

  if(!expander0error) i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20);
  if(!expander1error) i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20);
  if(!expander2error) i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20);
  if(!expander3error) i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20);
  
  if(!expander0error) expander0_ID_scan += !((port_expander0_col_buffer[0] & (1 << 5)) >> 5) * 2;
  if(!expander1error) expander1_ID_scan += !((port_expander1_col_buffer[0] & (1 << 5)) >> 5) * 2;
  if(!expander2error) expander2_ID_scan += !((port_expander2_col_buffer[0] & (1 << 5)) >> 5) * 2;
  if(!expander3error) expander3_ID_scan += !((port_expander3_col_buffer[0] & (1 << 5)) >> 5) * 2;

  //unselect rows (set to input and set pull-up)
  send_data[0] = 0xFF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);

  //select row 2/7
  send_data[0] = 0xFB;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

  wait_us(30);

  if(!expander0error) i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20);
  if(!expander1error) i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20);
  if(!expander2error) i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20);
  if(!expander3error) i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20);
  
  if(!expander0error) expander0_ID_scan += !((port_expander0_col_buffer[0] & (1 << 5)) >> 5) * 4;
  if(!expander1error) expander1_ID_scan += !((port_expander1_col_buffer[0] & (1 << 5)) >> 5) * 4;
  if(!expander2error) expander2_ID_scan += !((port_expander2_col_buffer[0] & (1 << 5)) >> 5) * 4;
  if(!expander3error) expander3_ID_scan += !((port_expander3_col_buffer[0] & (1 << 5)) >> 5) * 4;

  //unselect rows (set to input and set pull-up)
  send_data[0] = 0xFF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);

  //select row 3/8
  send_data[0] = 0xF7;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

  wait_us(30);

  if(!expander0error) i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20);
  if(!expander1error) i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20);
  if(!expander2error) i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20);
  if(!expander3error) i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20);
  
  if(!expander0error) expander0_ID_scan += !((port_expander0_col_buffer[0] & (1 << 5)) >> 5) * 8;
  if(!expander1error) expander1_ID_scan += !((port_expander1_col_buffer[0] & (1 << 5)) >> 5) * 8;
  if(!expander2error) expander2_ID_scan += !((port_expander2_col_buffer[0] & (1 << 5)) >> 5) * 8;
  if(!expander3error) expander3_ID_scan += !((port_expander3_col_buffer[0] & (1 << 5)) >> 5) * 8;

  //unselect rows (set to input and set pull-up)
  send_data[0] = 0xFF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);

  //select row 4/9
  send_data[0] = 0xEF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);

  wait_us(30);

  if(!expander0error) i2c_readReg((PORT_EXPANDER0_ADDRESS << 1), 0x12, &port_expander0_col_buffer[0], 2, 20);
  if(!expander1error) i2c_readReg((PORT_EXPANDER1_ADDRESS << 1), 0x12, &port_expander1_col_buffer[0], 2, 20);
  if(!expander2error) i2c_readReg((PORT_EXPANDER2_ADDRESS << 1), 0x12, &port_expander2_col_buffer[0], 2, 20);
  if(!expander3error) i2c_readReg((PORT_EXPANDER3_ADDRESS << 1), 0x12, &port_expander3_col_buffer[0], 2, 20);
  
  if(!expander0error) expander0_ID_scan += !((port_expander0_col_buffer[0] & (1 << 5)) >> 5) * 16;
  if(!expander1error) expander1_ID_scan += !((port_expander1_col_buffer[0] & (1 << 5)) >> 5) * 16;
  if(!expander2error) expander2_ID_scan += !((port_expander2_col_buffer[0] & (1 << 5)) >> 5) * 16;
  if(!expander3error) expander3_ID_scan += !((port_expander3_col_buffer[0] & (1 << 5)) >> 5) * 16;

  //unselect rows (set to input and set pull-up)
  send_data[0] = 0xFF;
  send_data[1] = 0xFF;
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x00, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER0_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER1_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER2_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);
  i2c_writeReg((PORT_EXPANDER3_ADDRESS << 1), 0x0C, &send_data[0], 2, 20);

  expander0_ID = expander0_ID_scan;
  expander1_ID = expander1_ID_scan;
  expander2_ID = expander2_ID_scan;
  expander3_ID = expander3_ID_scan;
}

#ifdef OLED_ENABLE

#include "progmem.h"
#include "lighthouse_frames.c"
#include "steamboat_frames.c"

#define ANIM_FRAMES 8
#define ANIM_USED   2 //Available: 1: lighthouse (16 frames), 2: steamboat (8 frames). Set ANIM_FRAMES accordingly

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint32_t anim_frame_duration = 200;
uint8_t current_anim_frame = 0;
uint8_t zone1active = 0;
uint8_t zone2active = 0;
uint8_t zone3active = 0;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void animation_phase(uint8_t modifiers) {
  current_anim_frame = (current_anim_frame + 1) % ANIM_FRAMES;

  if(ANIM_USED == 1) {
    oled_write_raw_P(lighthouse[current_anim_frame], sizeof(lighthouse[current_anim_frame]));
  }
  else if(ANIM_USED == 2){
    if(current_anim_frame == 0) {
      zone1active = modifiers & MOD_MASK_CTRL;
      zone2active = modifiers & MOD_MASK_SHIFT;
      zone3active = 0;
    }

    oled_set_cursor(0, 0);

    if(zone1active) {
      oled_write_raw_P(zone1activeFrames[current_anim_frame], sizeof(zone1activeFrames[current_anim_frame]));
      }
    else {
      oled_write_raw_P(zone1inactiveFrames[current_anim_frame], sizeof(zone1inactiveFrames[current_anim_frame]));
    }

    oled_set_cursor(0, 3);

    if(zone2active) {
      oled_write_raw_P(zone2activeFrames[current_anim_frame], sizeof(zone2activeFrames[current_anim_frame]));
    }
    else {
      oled_write_raw_P(zone2inactiveFrames[current_anim_frame], sizeof(zone2inactiveFrames[current_anim_frame]));
    }

    oled_set_cursor(0, 5);

    if(zone3active) {
      oled_write_raw_P(zone3activeFrames[current_anim_frame], sizeof(zone3activeFrames[current_anim_frame]));
    }
    else {
      oled_write_raw_P(zone3inactiveFrames[current_anim_frame], sizeof(zone3inactiveFrames[current_anim_frame]));
    }
  }
}

bool oled_task_user(void) {
  if(get_current_wpm() != 000) {
    if(timer_elapsed32(anim_timer) > anim_frame_duration) {
      anim_timer = timer_read32();
      animation_phase(get_mods());
    }
    anim_sleep = timer_read32();

  }
  else {
    if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
      oled_write_raw_P(blackScreen[0], sizeof(blackScreen[0]));
    } 
    else {
      if(timer_elapsed32(anim_timer) > anim_frame_duration) {
        anim_timer = timer_read32();
        animation_phase(get_mods());
      }
    }
  }
  return false;
}
#endif // OLED_ENABLE
