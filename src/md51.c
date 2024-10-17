#include <sys/types.h>
#include <openssl/md5.h>

void md5( unsigned char *input, int ilen, unsigned char output[16] )
{
    MD5_CTX ctx;

    MD5Init( &ctx );
    MD5Update( &ctx, input, ilen );
    MD5End( &ctx, output );

    memset( &ctx, 0, sizeof( MD5_CTX ) );
}
