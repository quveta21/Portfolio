from console_ui.ui import ConsoleUI
from controller.service import Service
from repository.automobil_repo import AutomobilRepository

def main():
    a_repo = AutomobilRepository("automobile.txt")
    service = Service(a_repo)
    ui = ConsoleUI(service)
    ui.meniu()
    ui.run()

if __name__ == '__main__':
    main()