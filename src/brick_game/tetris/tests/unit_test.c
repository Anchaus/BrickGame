#include "unit_test.h"

#ifdef LEAK_CHECK
#define FORK_STATUS CK_NOFORK
#else
#define FORK_STATUS CK_FORK
#endif

int main() {
  Suite *suite_list[] = {fsm_suite(), NULL};
  int failed_count = 0;

  for (Suite **suite_ptr = suite_list; *suite_ptr != NULL; suite_ptr++) {
    SRunner *runner = srunner_create(*suite_ptr);
    srunner_set_fork_status(runner, FORK_STATUS);
    srunner_run_all(runner, CK_NORMAL);
    failed_count += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed_count;
}