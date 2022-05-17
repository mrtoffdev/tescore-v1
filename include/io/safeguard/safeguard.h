#ifndef TESCORE_SAFEGUARD_H
#define TESCORE_SAFEGUARD_H

#include "../lib/aes.h"

typedef struct Safeguardctx {
    struct      AES_ctx ctx;
    uint8_t*    encrypted_dataBuffer,
                decrypted_dataBuffer,
                passphrase,
                saltIV;
    uint8_t     bufferSize;
    uint64_t    padding;
    char*       plain_strSrcBuffer;
} Safeguardctx;

#endif //TESCORE_SAFEGUARD_H
