void Delay(int nValue)
{
    int nDelayStatus;
    for (nDelayStatus = 0; nDelayStatus < nValue; nDelayStatus++)
    {
        asm("nop");
    }
}