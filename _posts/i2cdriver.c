    #include <linux/module.h>  
    #include <linux/i2c.h>  
      
    #define SENSOR_BUS_NUM 0    //该设备在第几路iic上，根据硬件具体修改  
    #define SENSOR_SLAVE_ADDRESS 0x3e//设备地址，注意是7位地址（非8位地址,linux中会自动添加读写位）  
    #define SENSOR_NAME "sensor"  //设备的名字  
    struct i2c_client *sensor_client=NULL;  
      
    static int sensor_i2c_write(char *buf,int length)  
    {  
    #if 1  
        int ret;  
        ret=i2c_master_send(sensor_client, buf, length);  
        if(ret!=length)  
        {  
            pr_err("sensor_i2c_write: i2c_master_send error\n");  
            return -EIO;  
        }  
        else  
            return 0;  
    #endif  
    #if 0  
        struct i2c_msg msg=  
            {  
                .addr = sensor_client->addr,  
                .flags = 0,  
                .buf = buf,  
                .len = length  
            };  
        if(i2c_transfer(sensor_client->adapter, &msg, 1)<0)  
        {  
            pr_err("sensor_i2c_write: transfer error\n");  
            return -EIO;  
        }  
        else  
            return 0;  
    #endif  
    }  
      
    static int sensor_i2c_read(char *buf,int length)  
    {  
    #if 1  
        int ret;  
        ret=i2c_master_recv(sensor_client,buf,length);  
        if(ret!=length)  
        {  
            pr_err("sensor_i2c_read: i2c_master_recv error\n");  
            return -EIO;  
        }  
        else  
            return 0;  
    #endif  
    #if 0  
        struct i2c_msg msg[] = {  
            {  
                .addr = sensor_client->addr,  
                .flags = 0,  
                .buf = buf,  
                .len = 1  
            },  
            {  
                .addr = sensor_client->addr,  
                .flags = I2C_M_RD,  
                .buf = buf,  
                .len = 1  
            }  
        };  
      
        if(i2c_transfer(sensor_client->adapter, msg, 2)<0)  
        {  
            pr_err("sensor_i2c_read: transfer error\n");  
            return -EIO;  
        }  
        else  
            return 0;  
    #endif  
    }  
      
    void sensor_config(void)  
    {  
        char buf[10];  
        int ret;  
        buf[0]=0x28;  
        buf[1]=0x88;  
        ret=sensor_i2c_write(buf,1);  
        if(ret==0)  
            printk("write reg %d value %d ok.",buf[0],buf[1]);  
        buf[0]=0x28;  
        sensor_i2c_read(buf+1,1);  
            printk("reg 0x%x value is 0x%x",buf[0],buf[1]);  
    }  
      
    static int sensor_probe(struct i2c_client *client,const struct i2c_device_id *id)    
    {    
        sensor_client=client;   
       sensor_config();  
        return 0;   
    }    
        
    static int sensor_remove(struct i2c_client *client)   
    {    
        return 0;   
    }    
        
    static const struct i2c_device_id sensor_id[] = {   
        {SENSOR_NAME, 0},   
        { }   
    };    
    MODULE_DEVICE_TABLE(i2c, sensor_id);   
      
      
    #ifdef CONFIG_PM  
    static int sensor_suspend(struct device *dev)  
    {  
        return 0;  
    }  
      
    static int sensor_resume(struct device *dev)  
    {  
        return 0;  
    }  
    #endif  
      
    static const struct dev_pm_ops sensor_ops = {  
        .suspend = sensor_suspend,  
        .resume  = sensor_resume,  
    };  
      
       
    static struct i2c_driver sensor_driver = {  
        .driver = {  
                 .name = SENSOR_NAME,  
                 .owner = THIS_MODULE,  
        #ifdef CONFIG_PM  
                 .pm = &sensor_ops,  
        #endif  
        },  
        .probe    = sensor_probe,  
        .remove   = sensor_remove,  
        .id_table = sensor_id,  
    };  
      
    static struct i2c_board_info sensor_device = {  
        I2C_BOARD_INFO(SENSOR_NAME, SENSOR_SLAVE_ADDRESS),  
    };  
      
    static int __init sensor_init(void)  
    {  
        struct i2c_adapter *adap;  
        struct i2c_client *client;  
      
        adap = i2c_get_adapter(SENSOR_BUS_NUM);   
        if (!adap) {  
            printk("i2c adapter %d\n",SENSOR_BUS_NUM);    
            return -ENODEV;  
        } else {  
            printk("get i2c adapter %d ok\n", SENSOR_BUS_NUM);  
            client = i2c_new_device(adap, &sensor_device);  
        }  
        if (!client) {  
            printk("get i2c client %s @ 0x%02x fail!\n", sensor_device.type,  
                    sensor_device.addr);  
            return -ENODEV;  
        } else {  
            printk("get i2c client ok!\n");  
        }  
        i2c_put_adapter(adap);  
        i2c_add_driver(&sensor_driver);  
        printk("sensor init success!\n");  
        return 0;  
    }  
      
    static void __exit sensor_exit(void)  
    {  
        i2c_del_driver(&sensor_driver);  
        if(sensor_client!=NULL)  
        i2c_unregister_device(sensor_client);  
        printk("Module removed\n");  
    }  
    module_init(sensor_init);    
    module_exit(sensor_exit);    
    MODULE_AUTHOR("GPL");    
    MODULE_LICENSE("GPL");  