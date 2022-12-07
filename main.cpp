#include "mbed.h"
#include "CCS811.h"



Serial pc(USBTX, USBRX);

#ifdef TARGET_UBLOX_EVK_ODIN_W2
CCS811 ccs811(PF_0, PF_1);
#else
CCS811 ccs811(I2C_SDA, I2C_SCL);
#endif


uint16_t eco2, tvoc;


void CCS811Callback(void)
{

    ccs811.readData(&eco2, &tvoc);

    pc.printf("eCO2 reading :%dppm, TVOC reading :%dppb\r\n", eco2, tvoc);

}


int main()
{
    ccs811.init();
    wait(1);

    while(1) {
//        ccs811.readstatus(); //0x90 reports everything working, 0x98 measurement ready to be used
        wait(1);
        CCS811Callback();
        wait(1);
    }
}
