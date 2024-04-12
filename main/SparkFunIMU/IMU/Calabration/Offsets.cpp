 #include "Offsets.h"
 
 esp_err_t Offsets::save() {
        // Initialize NVS
        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            // NVS partition was truncated and needs to be erased
            // Retry nvs_flash_init
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);

        // Open
        nvs_handle_t my_handle;
        ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));

        // Write
        ESP_ERROR_CHECK(nvs_set_blob(my_handle, "accel", &accel, sizeof(accel)));
        ESP_ERROR_CHECK(nvs_set_blob(my_handle, "mag", &mag, sizeof(mag)));
        ESP_ERROR_CHECK(nvs_set_blob(my_handle, "gyro", &gyro, sizeof(gyro)));

        // Commit
        ESP_ERROR_CHECK(nvs_commit(my_handle));

        // Close
        nvs_close(my_handle);

        return ESP_OK;
    }

    esp_err_t Offsets::load() {
        // Initialize NVS
        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            // NVS partition was truncated and needs to be erased
            // Retry nvs_flash_init
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);

        // Open
        nvs_handle_t my_handle;
        ESP_ERROR_CHECK(nvs_open("storage", NVS_READONLY, &my_handle));

        // Read
        size_t required_size;
        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "accel", NULL, &required_size));
        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "accel", &accel, &required_size));

        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "mag", NULL, &required_size));
        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "mag", &mag, &required_size));

        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "gyro", NULL, &required_size));
        ESP_ERROR_CHECK(nvs_get_blob(my_handle, "gyro", &gyro, &required_size));

        // Close
        nvs_close(my_handle);

        return ESP_OK;
    }

void Offsets::print() {
    printf("Accel bias: %f %f %f\n", accel.bias.x, accel.bias.y, accel.bias.z);
    printf("Mag bias: %f %f %f\n", mag.bias.x, mag.bias.y, mag.bias.z);
    printf("Gyro bias: %f %f %f\n", gyro.bias.x, gyro.bias.y, gyro.bias.z);
    printf("\n");

    printf("Accel rotx: %f %f %f\n", accel.rot.x[0], accel.rot.x[1], accel.rot.x[2]);
    printf("Accel roty: %f %f %f\n", accel.rot.y[0], accel.rot.y[1], accel.rot.y[2]);
    printf("Accel rotz: %f %f %f\n", accel.rot.z[0], accel.rot.z[1], accel.rot.z[2]);
    printf("\n");

    printf("Accel scale: %f %f %f\n", accel.scale.x, accel.scale.y, accel.scale.z);
    printf("\n");

    printf("Mag rotx: %f %f %f\n", mag.rot.x[0], mag.rot.x[1], mag.rot.x[2]);
    printf("Mag roty: %f %f %f\n", mag.rot.y[0], mag.rot.y[1], mag.rot.y[2]);
    printf("Mag rotz: %f %f %f\n", mag.rot.z[0], mag.rot.z[1], mag.rot.z[2]);
    printf("\n");

    printf("Mag scale: %f %f %f\n", mag.scale.x, mag.scale.y, mag.scale.z);
    printf("\n");

    printf("Gyro bias: %f %f %f\n", gyro.bias.x, gyro.bias.y, gyro.bias.z);
    printf("\n");
}