from repository.country_repo import CountryRepo, DuplicateException
from domain.country import CountryStats

class Tests:
    """
    Testele din program
    """
    def repoTests(self):
        """
        teste pentru repository
        """
        c_repo = CountryRepo("model_country.txt")
        assert c_repo.getAll() == []
        country = CountryStats("Italy","2022",1.7,5.9,55740000)
        c_repo.store(country)
        assert c_repo.getAll() == [country]
        country2 = CountryStats("Italy", "2022", 1.7, 5.9, 55740000)
        try:
            c_repo.store(country2)
            assert False
        except DuplicateException:
            assert True