#include <ch.h>
#include <hal.h>

int k = 0;
char f = 1;
static void extcb( EXTDriver *extp, expchannel_t channel)
{
    extp = extp;
    channel = channel;
    if (k < 5000 && f == 1) {
        k += 1000;
    } else {
          f = 0;
          k -= 1000;
          if (k <= 0) {
              f = 1;
          }
    }
}

static const EXTConfig extcfg = {
  .channels =
  {
    [0]  = {EXT_CH_MODE_DISABLED, NULL},
    [1]  = {EXT_CH_MODE_DISABLED, NULL},
    [2]  = {EXT_CH_MODE_DISABLED, NULL},
    [3]  = {EXT_CH_MODE_DISABLED, NULL},
    [4]  = {EXT_CH_MODE_DISABLED, NULL},
    [5]  = {EXT_CH_MODE_DISABLED, NULL},
    [6]  = {EXT_CH_MODE_DISABLED, NULL},
    [7]  = {EXT_CH_MODE_DISABLED, NULL},
    [8]  = {EXT_CH_MODE_DISABLED, NULL},
    [9]  = {EXT_CH_MODE_DISABLED, NULL},
    [10] = {EXT_CH_MODE_DISABLED, NULL},
    [11] = {EXT_CH_MODE_DISABLED, NULL},
    [12] = {EXT_CH_MODE_DISABLED, NULL},
    [13] = {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, extcb}, //PC13 = Button
    [14] = {EXT_CH_MODE_DISABLED, NULL},
    [15] = {EXT_CH_MODE_DISABLED, NULL},
  }
};

PWMConfig pwm1conf = {
    .frequency = 500000,
    .period    = 5000,
    .callback  = NULL,
    .channels  = {
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                  {PWM_OUTPUT_DISABLED, NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

PWMConfig pwm2conf = {
    .frequency = 500000,
    .period    = 5000,
    .callback  = NULL,
    .channels  = {
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_DISABLED, NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

int main(void)
{
    chSysInit();
    halInit();
    palSetLineMode( LINE_LED1, PAL_MODE_ALTERNATE(2) );
    palSetLineMode( LINE_LED2, PAL_MODE_ALTERNATE(2) );
    pwmStart(&PWMD3 , &pwm1conf );
    pwmStart(&PWMD4 , &pwm2conf );
    extStart( &EXTD1, &extcfg );

    while (true)
    {
    	pwmEnableChannel(&PWMD3, 2 , k);
    	pwmEnableChannel(&PWMD4, 1 , k);
        chThdSleepMilliseconds(10);
    }
}

