from console_ui.ui import ConsoleUI
from controller.service import Service
from repository.camera_repo import CameraRepository
from tests import Tests


def main():
    """
    Partea centrala a aplicatiei
    """
    c_repo = CameraRepository("camere.txt")
    service = Service(c_repo)
    ui = ConsoleUI(service)
    ui.menu()
    ui.run()

def tests():
    """
    Ruleaza testele din program
    """
    t = Tests()
    t.repoTests()

if __name__ == "__main__":
    tests()
    main()