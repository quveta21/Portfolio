from tests.function_tests import test
from controller.console_ui import meniu, batch_mode
from controller.console_ui import start_ui

def main():
    test()
    meniu()
    batch_mode()
    #start_ui()

if __name__ == '__main__':
    main()