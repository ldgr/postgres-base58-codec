#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>


const char alphabet[58] = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";


const char *max_integer = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096";


char *encode_base58(mpz_t uuid_int)
{
  mpz_t limit;
  mpz_init_set_str(limit, max_integer, 10);

  int limit_exceeded = mpz_cmp(uuid_int, limit);
  if (limit_exceeded > 0)
  {
    return "";
  }

  mpz_t dividend;
  mpz_init(dividend);
  mpz_set(dividend, uuid_int);

  mpz_t divisor;
  mpz_init(divisor);
  mpz_set_ui(divisor, 58);

  mpz_t quotient;
  mpz_init(quotient);

  mpz_t remainder;
  mpz_init(remainder);

  char buffer[1024];
  int buffer_position = 0;

  int comparator = mpz_cmp(dividend, divisor);
  while (comparator >= 0)
  {
    mpz_tdiv_qr(quotient, remainder, dividend, divisor);
    buffer[buffer_position] = alphabet[mpz_get_ui(remainder)];
    buffer_position++;
    mpz_set(dividend, quotient);
    comparator = mpz_cmp(dividend, divisor);
  }
  buffer[buffer_position] = alphabet[mpz_get_ui(dividend)];
  buffer_position++;

  char encoded[buffer_position];
  for (int i = buffer_position; i >= 0; i--) {
    encoded[buffer_position - i] = buffer[i - 1];
  }
  return (char *)encoded;
}


int alphabet_index(char letter)
{
  for (int i=0; i < 58; i++)
  {
    if (alphabet[i] == letter)
    {
        return i;
    }
  }
}


void decode_base58(mpz_t decoded_integer_result, char *encoded)
{
  mpz_t sum;
  int letter_index;
  mpz_t multiplier;
  mpz_t digit_value;

  mpz_init(sum);
  mpz_set_ui(sum, 0);

  mpz_init(multiplier);
  mpz_set_ui(multiplier, 1);

  mpz_init(digit_value);

  int string_length = strlen(encoded);

  for (int i = string_length; i > 0; i--)
  {
    letter_index = alphabet_index((char)encoded[i - 1]);
    mpz_mul_ui(digit_value, multiplier, letter_index);
    mpz_add(sum, sum, digit_value);
    mpz_mul_ui(multiplier, multiplier, 58);
  }
  mpz_set(decoded_integer_result, sum);
}