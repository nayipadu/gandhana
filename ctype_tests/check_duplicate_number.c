
#include "../include/hash.h"
#include <stdint.h>

/* return true of there are no duplicates.
 * num [input] is array of integers
 * len [input] length of the array
 * Return value
 * true: duplicate present
 * false: no duplicates
 */

int
check_duplicate_numbers(hashCookie cookie, int *num, int len)
{
      int i;

      for (i=0; i < len; i++) {
         // lookup hash
         if(hash_lookup(cookie, (voidp) (intptr_t) num[i])) {
            // duplicate
            return 1;
         }
         hash_insert(cookie, (voidp) (intptr_t) num[i], 0);
      }
      return 0;
}
