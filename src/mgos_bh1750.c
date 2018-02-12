#include "mgos_bh1750.h"
#include "mgos_i2c.h"

/* Mode mapping */

uint16_t mode_lut[MODE_NUM_OF] = {
    /* UNCONFIGURED:*/              0,
    /*CONTINUOUS_HIGH_RES_MODE:*/   0x10,
    /*CONTINUOUS_HIGH_RES_MODE_2:*/ 0x11,
    /*CONTINUOUS_LOW_RES_MODE:*/    0x13,
    /*ONE_TIME_HIGH_RES_MODE:*/     0x20,
    /*ONE_TIME_HIGH_RES_MODE_2:*/   0x21,
    /*ONE_TIME_LOW_RES_MODE:*/      0x23,
};

bool mgos_bh1750_init(void){
    return true;
}

/* 
doc
*/
bh1750_t* bh1750_init(uint16_t addr){
    bh1750_t* res = malloc (sizeof(res));
    res->addr = addr;
    return res;
}

/*
doc
*/
bool begin(Mode mode){
    if (mode < UNCONFIGURED || mode > ONE_TIME_LOW_RES_MODE){
        // LOG()
        return false;
    }
    return true;
}

/*
doc
*/
bool configure(bh1750_t* bh1750, Mode mode){
    if (!bh1750){
        // ESP_LOGE(TAG, "mgos_bh1750.configure: null arg");
        return false;
    }

    mgos_i2c* i2c = mgos_i2c_get_global();
    mgos_i2c_write(i2c, bh1750->addr, (void*) &mode_lut[mode], sizeof(uint16_t), true);
    return true;
}

/*
doc
*/
uint16_t readLightLevel(bool maxWait){
    if (maxWait){
        return 1;
    }
    return 0;
}

