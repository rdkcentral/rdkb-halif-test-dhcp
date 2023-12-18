extern int test_dhcp4cApi_hal_l1_register(void);  

int register_hal_l1_tests( void )
{
    int registerstatus=0;
    registerstatus |= test_dhcp4cApi_hal_l1_register();
    return registerstatus;
}

