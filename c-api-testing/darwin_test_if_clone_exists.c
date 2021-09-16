#include <sys/attr.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

// Determine if the path specified supports APFS clone and print out if it does
// Compile with just make darwin_test_if_clone_exists
int main(void) {
    char *path = "/";

    struct attrlist attrlist = {
        .bitmapcount = ATTR_BIT_MAP_COUNT,
        .reserved = 0,
        .commonattr = 0,
        .volattr = ATTR_VOL_INFO | ATTR_VOL_CAPABILITIES,
        .dirattr = 0,
        .fileattr = 0,
        .forkattr = 0,
    };
    u_int32_t attrBuf[1000];
    int err = getattrlist(path, &attrlist, &attrBuf, sizeof(attrBuf), 0);
    if (err) {
        printf("failed to getattrlist");
        return 1;
    }
    vol_capabilities_attr_t *vol_capabilities = (vol_capabilities_attr_t *) &attrBuf[1];

    int supports_clone =
            (vol_capabilities->valid[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_CLONE)
            && (vol_capabilities->capabilities[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_CLONE);
    printf(
        "%s %s APFS clone",
        path,
        supports_clone ? "supports" : "doesn't support");

    return 0;
}
