def create_list_manager():
    """
        Creeaza manager pentru lista de nr complexe: contine atat lista curenta, cat si lista de undo
        :return: dict cu 2 chei: 'lista_curenta', valoarea asociata este lista curenta de nr complexe, initial vida
                                 'lista_undo', lista de undo care contine starile anterioare ale listei curente, initial vida
    """
    return {'lista_curenta': [], 'lista_undo': []}

def get_lista_curenta(list_manager: dict) -> list:
    return list_manager['lista_curenta']

def get_lista_undo(list_manager: dict) -> list:
    return list_manager['lista_undo']

def set_lista_curenta(list_manager: dict, lista_curenta_noua: list):
    list_manager['lista_curenta'] = lista_curenta_noua

def set_lista_undo(list_manager: dict, lista_undo_noua: list):
    list_manager['lista_undo'] = lista_undo_noua

def add_to_undo(list_manager: dict):
    #get_lista_undo(list_manager).append(get_lista_curenta(list_manager))
    get_lista_undo(list_manager).append([nr for nr in get_lista_curenta(list_manager)])


def undo(list_manager):
    """
    Anuleaza ultima operatie efectuata (operatie care modifica lista)
    :param list_manager: manager gestionat de aplicatie
    :return: -; lista curenta este setata la starea listei de dinaintea ultimei operatii
                care a modificat lista
    """
    if len(get_lista_undo(list_manager)) == 0:
        raise ValueError("Nu se mai poate face undo.")

    #se face un "revert" la ultima stare a listei de dinaintea
    #efectuarii operatiei la care se face undo
    lista_anterioara = get_lista_undo(list_manager).pop()
    set_lista_curenta(list_manager, lista_anterioara)

def undo_ui(list_manager):
    try:
        undo(list_manager)
    except ValueError as e:
        print(e)