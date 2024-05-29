#include "sd.h"

#include <ff.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/fs/fs.h>
#include <zephyr/kernel.h>
#include <zephyr/storage/disk_access.h>

#define DISK_DRIVE_NAME "SD"
#define DISK_MOUNT_PT "/" DISK_DRIVE_NAME ":"
#define DISK_MOUNT_PT_TEST DISK_DRIVE_NAME "/TEST"

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
    .type = FS_FATFS,
    .fs_data = &fat_fs,
};

static const char* disk_mount_pt = DISK_MOUNT_PT;

static int get_sd_info();
static void mount_sd_card();
static int lsdir(const char* path);
static bool create_some_entries(const char* base_path);
static int sd_card_speed_test();

void init_sd_card()
{
    int res;
    static const char disk_pdrv[] = "SD";

    if (get_sd_info() == 0)
    {
        mount_sd_card();

        if (sd_card_speed_test() == 0)
        {
            printf("Speed test finished\n");
        }
        else
        {
            printf("Speed test failed\n");
        }
    }

    fs_unmount(&mp);
}

void save_entry(const accelerometer_data& data)
{
    char path[32];
    struct fs_file_t file;
    int base = strlen(disk_mount_pt);

    fs_file_t_init(&file);

    if (base >= (sizeof(path) - 10))
    {
        printf("Not enough concatenation buffer to create file paths");
        return;
    }

    strncpy(path, disk_mount_pt, sizeof(path));

    path[base++] = '/';
    path[base] = 0;
    strcat(&path[base], "data.txt");

    if (fs_open(&file, path, FS_O_CREATE | FS_O_RDWR) != 0)
    {
        printf("Failed to create file %s", path);
        return;
    }

    char buf[256];
    snprintf(buf, sizeof(buf), "x_accel: %f, y_accel: %f, z_accel: %f, x_gyro: %f, y_gyro: %f, z_gyro: %f\n",
             data.x_accel, data.y_accel, data.z_accel, data.x_gyro, data.y_gyro, data.z_gyro);

    if (fs_write(&file, buf, strlen(buf)) != strlen(buf))
    {
        fs_close(&file);
        printf("write error\n");
        return;
    }

    // The f_sync function flushes the cached information of a writing file.
    if (fs_sync(&file) != 0)
    {
        printf("sync error\n");
        return;
    }

    // The f_close function closes an open file.
    fs_close(&file);
}

int get_sd_info()
{
    /* raw disk i/o */
    static const char* disk_pdrv = DISK_DRIVE_NAME;
    uint64_t memory_size_mb;
    uint32_t block_count;
    uint32_t block_size;

    if (disk_access_init(disk_pdrv) != 0)
    {
        printf("Storage init ERROR!\n");
        return -1;
    }

    if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_COUNT, &block_count))
    {
        printf("Unable to get sector count\n");
        return -1;
    }
    printf("Block count %u\n", block_count);

    if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_SIZE, &block_size))
    {
        printf("Unable to get sector size\n");
        return -1;
    }
    printf("Sector size %u\n", block_size);

    memory_size_mb = (uint64_t)block_count * block_size;
    printf("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));

    return 0;
}

void mount_sd_card()
{
    mp.mnt_point = disk_mount_pt;

    int res = fs_mount(&mp);

    if (res == FR_OK)
    {
        printf("Disk mounted.\n");
        lsdir(disk_mount_pt);

        // if (create_some_entries(disk_mount_pt))
        // {
        //     lsdir(disk_mount_pt);
        // }
    }
    else
    {
        printf("Error mounting disk.\n");
    }
}

int lsdir(const char* path)
{
    int res;
    struct fs_dir_t dirp;
    static struct fs_dirent entry;
    int count = 0;

    fs_dir_t_init(&dirp);

    /* Verify fs_opendir() */
    res = fs_opendir(&dirp, path);
    if (res)
    {
        printf("Error opening dir %s [%d]\n", path, res);
        return res;
    }

    printf("\nListing dir %s ...\n", path);
    for (;;)
    {
        /* Verify fs_readdir() */
        res = fs_readdir(&dirp, &entry);

        /* entry.name[0] == 0 means end-of-dir */
        if (res || entry.name[0] == 0)
        {
            break;
        }

        if (entry.type == FS_DIR_ENTRY_DIR)
        {
            printf("[DIR ] %s\n", entry.name);
        }
        else
        {
            printf("[FILE] %s (size = %zu)\n", entry.name, entry.size);
        }
        count++;
    }

    /* Verify fs_closedir() */
    fs_closedir(&dirp);
    if (res == 0)
    {
        res = count;
    }

    return res;
}

#define MAX_PATH 128
#define SOME_FILE_NAME "some.dat"
#define SOME_DIR_NAME "some"
#define SOME_REQUIRED_LEN MAX(sizeof(SOME_FILE_NAME), sizeof(SOME_DIR_NAME))

bool create_some_entries(const char* base_path)
{
    char path[MAX_PATH];
    struct fs_file_t file;
    int base = strlen(base_path);

    fs_file_t_init(&file);

    if (base >= (sizeof(path) - SOME_REQUIRED_LEN))
    {
        printf("Not enough concatenation buffer to create file paths");
        return false;
    }

    printf("Creating some dir entries in %s", base_path);
    strncpy(path, base_path, sizeof(path));

    path[base++] = '/';
    path[base] = 0;
    strcat(&path[base], SOME_FILE_NAME);

    if (fs_open(&file, path, FS_O_CREATE) != 0)
    {
        printf("Failed to create file %s", path);
        return false;
    }
    fs_close(&file);

    path[base] = 0;
    strcat(&path[base], SOME_DIR_NAME);

    if (fs_mkdir(path) != 0)
    {
        printf("Failed to create dir %s", path);
        /* If code gets here, it has at least successes to create the
         * file so allow function to return true.
         */
    }
    return true;
}

#define TEST_FILE_SIZE 1024
uint8_t buf_test[TEST_FILE_SIZE];

int sd_card_speed_test()
{
    char path[MAX_PATH];
    struct fs_file_t file;
    int base = strlen(disk_mount_pt);

    fs_file_t_init(&file);

    if (base >= (sizeof(path) - SOME_REQUIRED_LEN))
    {
        printf("Not enough concatenation buffer to create file paths");
        return 0;
    }

    strncpy(path, disk_mount_pt, sizeof(path));

    path[base++] = '/';
    path[base] = 0;
    strcat(&path[base], SOME_FILE_NAME);

    if (fs_open(&file, path, FS_O_CREATE | FS_O_RDWR) != 0)
    {
        printf("Failed to create file %s", path);
        return 0;
    }

    // Create test char array with custom file size
    memset(buf_test, 'X', TEST_FILE_SIZE);

    auto start = k_uptime_get();

    for (int i = 0; i < 1024; ++i)
    {
        // // Search for End of File
        // if (fs_seek(&file, 0, FS_SEEK_END) != 0)
        // {
        //     printf("Test 1 Error: FS_SEEK failed!\n");
        //     return -1;
        // }
        if (fs_write(&file, buf_test, TEST_FILE_SIZE) != TEST_FILE_SIZE)
        {
            fs_close(&file);
            printf("write error\n");
            return -1;
        }
    }

    auto end = k_uptime_get();

    printf("Wrote %d bytes in %d ms\n", TEST_FILE_SIZE * 1024, end - start);

    // The f_sync function flushes the cached information of a writing file.
    if (fs_sync(&file) != 0)
    {
        printf("sync error\n");
        return -1;
    }

    // The f_close function closes an open file.
    fs_close(&file);

    return 0;
}
