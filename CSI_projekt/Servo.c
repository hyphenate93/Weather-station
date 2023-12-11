/*
int servo(int bright)
{
    if (bright<-50)
    {
        angle=angle-20;
        if(angle<1340)
        {
            angle=1340;
        }
            *AT91C_PWMC_CH7_CDTYUPDR = angle;
            return angle;
    }
    else if(bright>50)
    {
        angle=angle+20;
        if (angle>6400)
        {
            angle=6400;
        }
        *AT91C_PWMC_CH7_CDTYUPDR=angle;
        return angle;
    }
    else
    {
        sunfound=1;
        return angle;
    }
}
*/