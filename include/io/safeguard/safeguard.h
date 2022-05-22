/*========================================
    SAFEGUARD ENCRYPTION / DECRYPTION
    Head Author: Christopher Abadillos Jr.
  ========================================*/
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

// Interface
void proc_encryptbuffer(const char* in_strmasterbuffer, char* out_encmasterbuffer);
void proc_decryptbuffer(const char* in_strmasterhexbuffer, char* out_decmasterstrbuffer);

#endif //TESCORE_SAFEGUARD_H
