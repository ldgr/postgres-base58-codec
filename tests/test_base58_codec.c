#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <assert.h>

#include "base58_codec.h"


void test_encode()
{
  char *decoded = "289050509339925577180148093133912309615";
  char *expected_encoded = "sRs3QJC4d5Dcf3EJna3KdK";

  mpz_t guid;
  mpz_init(guid);
  mpz_set_str(guid, decoded, 10);

  char *encoded;
  encoded = encode_base58(guid);
  
  assert (strcmp(encoded, expected_encoded) == 0);

  printf("test_encode passed\n");
}


void test_decode()
{
  char *encoded = "sRs3QJC4d5Dcf3EJna3KdK";
  char *expected_decoded = "289050509339925577180148093133912309615";

  mpz_t decoded;
  mpz_init(decoded);

  decode_base58(decoded, encoded);
  char *decoded_string = mpz_get_str(NULL, 10, decoded);

  assert (strcmp(decoded_string, expected_decoded) == 0); 
 
  printf("test_decode passed\n");
}


void test_encode_overflow()
{
  char *decoded = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084097";
  char *expected_encoded = "";
  mpz_t guid;
  mpz_init(guid);
  mpz_set_str(guid, decoded, 10);

  char *encoded;
  encoded = encode_base58(guid);

  assert (strcmp(encoded, expected_encoded) == 0);

  printf("test_encode_overflow passed\n");
}


int main()
{
  test_encode();
  test_decode();
  test_encode_overflow();
  printf("\nTests Pass\n");
  return 0;
}
