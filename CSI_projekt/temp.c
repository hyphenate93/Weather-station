volatile int32_t nTick;
volatile double temperature;
volatile double temp_pulse;

void measure_temp(void)
{
    //    *AT91C_TC0_IER        = AT91C_TC_LDRBS;               //Enable Interuppt On LDRBS High
    *AT91C_PIOB_OER = AT91C_PIO_PB25;  //Output Enable DigitalPin2
    *AT91C_PIOB_CODR = AT91C_PIO_PB25; //Clear DigitalPin2

    Delay(25);

    *AT91C_PIOB_SODR = AT91C_PIO_PB25;
    *AT91C_PIOB_ODR = AT91C_PIO_PB25; //StartPulse
    *AT91C_TC0_SR;
    *AT91C_TC0_IER = AT91C_TC_LDRBS;
    *AT91C_TC0_CCR = 0x4; //AT91C_TC_SWTRG;               //sw_reset in TC0_CCR0
    //Delay(nTempDelay);
    Delay(50000);
}
void TC0_Handler(void)
{
    double RA = *AT91C_TC0_RA;
    double RB = *AT91C_TC0_RB;
    *AT91C_TC0_IDR = AT91C_TC_LDRBS; //Disable interrupt TC_IER_LDRBS
                                     //    *AT91C_TC0_SR         = AT91C_TC_LDRBS;
    temp_pulse = RB - RA;            //Antalet klockpulser som signalen är låg
                                     //    temp_pulse = temp_pulse;
                                     //    temperature           = temp_pulse;
    temperature = (((temp_pulse * (1 / 42.0)) / 5.0) - 273.15);
    temperature = temperature;
}

void SysTick_Handler(void)
{
    nTick++;
}