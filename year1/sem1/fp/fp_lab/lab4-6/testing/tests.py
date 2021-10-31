from testing.participants_testing import run_participants_tests
from testing.undos_testing import run_undos_tests
from testing.strings_testing import run_strings_tests
from testing.computes_testing import run_computes_tests
from testing.comparators_testing import run_comparators_tests
from testing.conversions_testing import run_conversions_tests
from testing.lists_testing import run_lists_tests
from testing.validations_testing import run_validations_tests
from testing.svgs_testing import run_svgs_tests

def run_all_tests():
  run_participants_tests()
  run_undos_tests()
  run_strings_tests()
  run_computes_tests()
  run_comparators_tests()
  run_conversions_tests()
  run_lists_tests()
  run_validations_tests()
  run_svgs_tests()
