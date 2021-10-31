from presentation.ui import ui
from testing.tests import run_all_tests

def concurs():
  run_all_tests()
  ui()

concurs()
