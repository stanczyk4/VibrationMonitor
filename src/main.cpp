#include <ff.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/fs/fs.h>
#include <zephyr/kernel.h>
#include <zephyr/storage/disk_access.h>

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
    .type = FS_FATFS,
    .fs_data = &fat_fs,
};

#define DISK_DRIVE_NAME "SD"
#define DISK_MOUNT_PT "/" DISK_DRIVE_NAME ":"

static const char* disk_mount_pt = DISK_MOUNT_PT;

void get_sd_info()
{
    /* raw disk i/o */
    static const char* disk_pdrv = DISK_DRIVE_NAME;
    uint64_t memory_size_mb;
    uint32_t block_count;
    uint32_t block_size;

    if (disk_access_init(disk_pdrv) != 0)
    {
        printf("Storage init ERROR!\n");
        return;
    }

    if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_COUNT, &block_count))
    {
        printf("Unable to get sector count\n");
        return;
    }
    printf("Block count %u\n", block_count);

    if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_SIZE, &block_size))
    {
        printf("Unable to get sector size\n");
        return;
    }
    printf("Sector size %u\n", block_size);

    memory_size_mb = (uint64_t)block_count * block_size;
    printf("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));
}

int main()
{
    int res;
    static const char disk_pdrv[] = "SD";

    get_sd_info();

    while (1)
    {
        k_sleep(K_MSEC(100));
        printf("Hello, Zephyr with printf!\n");
    }
    return 0;
}
