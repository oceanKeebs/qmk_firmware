#include "quantum.h"

// The first four layers gets a name for readability, which is then used in the OLED below.
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST
};

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
