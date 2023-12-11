
// light
void light_sensor(void)
{
    *AT91C_ADCC_CHER = 0x2; //Aktiverar CH 1
    *AT91C_ADCC_CR = 0x2;   //Startar mätning
    while ((*AT91C_ADCC_LCDR & 0xF000) != 0x1000)
    {
    } //Väntar på mätningsreslutat DRDY (0x400C0030)
    if ((*AT91C_ADCC_LCDR & 0xF000) == 0x1000)
    {
        lightitup = (*AT91C_ADCC_LCDR & 0xFFF); //Läser av värde i ADC_LCDR    (0x400C0020)
    }

    int bright;
    *AT91C_ADCC_CHER = (1 << 1); //Select channel in ADC_CHER
    *AT91C_ADCC_CR = (1 << 1);   //Start an ADC in ADC_CR
    while (1)
    { //wait until IDR_DRDY-> ADC_SR status register

        if ((*AT91C_ADCC_LCDR & 0xF000) == 0x1000)
        {
            break;
        }
    }
    bright = (*AT91C_ADCC_LCDR & (0xFFF)); //Read value in the ADC_LCDR
    Delay(30);
    return bright;
}