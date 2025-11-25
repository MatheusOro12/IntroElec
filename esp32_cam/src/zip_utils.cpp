#include "zip_utils.h"
#include <FS.h>
#include <SD_MMC.h>      // CORREÇÃO: usar SD_MMC em vez de SPIFFS
#include "esp_crc.h"
#include <cstring>

bool zip_create(const char *zipPath) {

    // Abre o arquivo .zip no SD
    File zip = SD_MMC.open(zipPath, FILE_WRITE);
    if (!zip) return false;

    // Arquivo que será compactado
    const char *filename = "/timelapse.bin";  
    File input = SD_MMC.open(filename, FILE_READ);

    if (!input) {
        zip.close();
        return false;
    }

    size_t fsize = input.size();
    uint8_t *buf = new uint8_t[fsize];

    if (!buf) {
        input.close();
        zip.close();
        return false;
    }

    input.read(buf, fsize);

    uint32_t crc = esp_crc32_le(0, buf, fsize);

    // ======== LOCAL FILE HEADER ========
    zip.write((const uint8_t*)"\x50\x4b\x03\x04", 4);
    zip.write((const uint8_t*)"\x14\x00", 2);
    zip.write((const uint8_t*)"\x00\x00", 2);
    zip.write((const uint8_t*)"\x00\x00", 2);
    zip.write((const uint8_t*)"\x00\x00\x00\x00", 4);

    zip.write((uint8_t*)&crc, 4);
    zip.write((uint8_t*)&fsize, 4);
    zip.write((uint8_t*)&fsize, 4);

    uint16_t fn_len = strlen(filename);
    zip.write((uint8_t*)&fn_len, 2);

    zip.write((const uint8_t*)"\x00\x00", 2);
    zip.write((const uint8_t*)filename, fn_len);

    zip.write(buf, fsize);

    delete[] buf;
    input.close();

    // ======== CENTRAL DIRECTORY ========
    uint32_t cd_start = zip.position();

    zip.write((const uint8_t*)"\x50\x4b\x01\x02", 4);
    zip.write((const uint8_t*)"\x14\x00\x14\x00", 4);
    zip.write((const uint8_t*)"\x00\x00\x00\x00", 4);

    zip.write((uint8_t*)&crc, 4);
    zip.write((uint8_t*)&fsize, 4);
    zip.write((uint8_t*)&fsize, 4);

    zip.write((uint8_t*)&fn_len, 2);

    zip.write((const uint8_t*)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);

    uint32_t offset = 0;
    zip.write((uint8_t*)&offset, 4);

    zip.write((const uint8_t*)filename, fn_len);

    uint32_t cd_end = zip.position();
    uint32_t cd_size = cd_end - cd_start;

    // ======== END OF CENTRAL DIRECTORY ========
    zip.write((const uint8_t*)"\x50\x4b\x05\x06", 4);
    zip.write((const uint8_t*)"\x00\x00\x00\x00", 4);

    uint16_t total_entries = 1;

    zip.write((uint8_t*)&total_entries, 2);
    zip.write((uint8_t*)&total_entries, 2);

    zip.write((uint8_t*)&cd_size, 4);
    zip.write((uint8_t*)&cd_start, 4);

    zip.write((const uint8_t*)"\x00\x00", 2);

    zip.close();
    return true;
}
