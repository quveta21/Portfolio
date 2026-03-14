from controller.service import Service
from repository.melodie_repo import MelodieRepository
from ui.console_ui import ConsoleUI


def main():
    m_repo = MelodieRepository("melodii.txt")
    service = Service(m_repo)
    ui = ConsoleUI(service)
    ui.meniu()
    ui.run()

if __name__ == "__main__":
    main()