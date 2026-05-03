/* Command: test
 *
 * NOTE: Test is necessarily a compound command so it doesn't call init or end.
 */

#include "commands.h"

int test_cmd(State *state)
{
    call(state, "new");
    return 0;
}

