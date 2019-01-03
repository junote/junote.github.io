    #include <linux/module.h>  
    #include <linux/spi/spi.h>  
      
      
    #define SENSOR_NAME   "sensor"  
    #define SENSOR_SPI_BUS 0  
    #define SPI_MODE       0  
    #define SENSOR_MAX_SPEED 2*1000*1000  
      
    struct spi_device *sensor_spi=NULL;  
      
    int sensor_spi_write(unsigned int addr, unsigned int val, size_t len)  
    {  
        int status;  
        unsigned char write_buf[2];  
      
        write_buf[0] = addr;  
        write_buf[1] = val;  
      
        status = spi_write(sensor_spi, write_buf,2);  
        if (status)  
            dev_err(&sensor_spi->dev, "%s error %d\n", __FUNCTION__, status);  
        return status;  
    }  
      
    int sensor_spi_read(unsigned int addr, unsigned int *val, size_t len)  
    {  
        struct spi_message message;  
        struct spi_transfer x[1];  
        int status;  
        unsigned char write_buf[10];  
        unsigned char read_buf[10];  
      
        write_buf[0] =addr;  
        spi_message_init(&message);  
        memset(x, 0, sizeof(x));  
        x[0].len     = len;  
        x[0].tx_buf = write_buf;  
        x[0].rx_buf = read_buf;  
        spi_message_add_tail(&x[0], &message);  
        status = spi_sync(sensor_spi, &message);  
        if(status!=0)  
            dev_err(&sensor_spi->dev, "%s error %d\n", __FUNCTION__, status);  
        else  
            *val =read_buf[4];  
        return status;  
    }  
      
      
    static const struct spi_device_id sensor_spi_id[] = {  
        { SENSOR_NAME, 0 },  
        { }  
    };  
      
    MODULE_DEVICE_TABLE(spi, sensor_spi_id);  
      
    static int  sensor_probe(struct spi_device *spi)  
    {  
        sensor_spi=spi;  
        return 0;  
    }  
      
    static int  sensor_remove(struct spi_device *spi)  
    {  
        return 0;  
    }  
      
    #ifdef CONFIG_PM  
    static int sensor_suspend(struct device *dev)  
    {  
        return 0;  
    }  
      
    static int sensor_resume(struct device *dev)  
    {  
        return 0;  
    }  
      
    static const struct dev_pm_ops sensor_ops = {  
        .suspend = sensor_suspend,  
        .resume  = sensor_resume,  
    };  
    #endif  
      
      
    static struct spi_driver sensor_driver = {  
        .driver = {  
            .name  = SENSOR_NAME,  
            .owner = THIS_MODULE,  
        #ifdef CONFIG_PM  
            .pm   = &sensor_ops,  
        #endif  
        },  
        .probe    =  sensor_probe,  
        .remove   =  sensor_remove,  
        .id_table =  sensor_spi_id,  
    };  
      
    static __init int sensor_spi_init(void)  
    {  
        int status=-1;  
        struct spi_master *master;  
        struct spi_device *spi;  
        struct spi_board_info chip =  
        {  
            .modalias     = SENSOR_NAME,  
            .mode         = SPI_MODE,  
            .bus_num      = SENSOR_SPI_BUS,  
            .chip_select  = 0,  
            .max_speed_hz = SENSOR_MAX_SPEED,  
        };  
        spi_register_driver(&sensor_driver);  
        if (status<0)  
        {  
            pr_err("%s: spi_register_driver spi_driver failure. status = %d\n", __func__, status);  
    　　　　 return status;  
         }  
        pr_err("%s: spi_register_driver spi_driver success. status = %d\n", __func__, status);  
        master = spi_busnum_to_master(SENSOR_SPI_BUS);  
        if (!master)  
        {  
            status = -ENODEV;  
            goto error_busnum;  
        }  
        spi = spi_new_device(master, &chip);  
        if (!spi)  
        {  
            status = -EBUSY;  
            goto error_mem;  
        }  
        return status;  
      
    error_mem:  
    error_busnum:  
        printk("register spi device err!\n");  
        spi_unregister_driver(&sensor_driver);  
        return status;  
    }  
      
    static __exit void sensor_spi_exit(void)  
    {  
        spi_unregister_driver(&sensor_driver);  
        if(sensor_spi!=NULL)  
        spi_unregister_device(sensor_spi);  
    }  
      
    module_init(sensor_spi_init);  
    module_exit(sensor_spi_exit);  
    MODULE_LICENSE("GPL v2");  