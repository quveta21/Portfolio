from ui.console_ui import ConsoleUI
from controller.service import Service
from repository.country_repo import CountryRepo
from tests import Tests

def main():
    c_repo = CountryRepo("model_country.txt")
    service = Service(c_repo)
    ui = ConsoleUI(service)
    ui.meniu()
    ui.run()

def tests():
    t = Tests()
    t.repoTests()

if __name__ == '__main__':
    tests()
    main()