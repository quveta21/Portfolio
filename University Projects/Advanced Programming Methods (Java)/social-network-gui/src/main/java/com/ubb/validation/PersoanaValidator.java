package com.ubb.validation;

import com.ubb.domain.Persoana;
import com.ubb.exceptions.ValidatorException;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class PersoanaValidator implements  Validator<Persoana> {
    // composition !!!
    private final UserValidator userValidator = new UserValidator();

    @Override
    public void validate(Persoana persoana) {
        userValidator.validate(persoana);   // validam strict partea de user
        // acum validam atributele specifice persoanei
        String errMsg = "";
        if (persoana.getNume() == null || "".equals(persoana.getNume()))
            errMsg += "!! Nume invalid !!\n";
        if (persoana.getPrenume() == null || "".equals(persoana.getPrenume()))
            errMsg += "!! Prenume invalid !!\n";
        try {
            LocalDate.parse(persoana.getDataNasterii(), DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        } catch (DateTimeParseException e) {
            errMsg += "!! Data nasterii invalida !!\n";
        }
        if (persoana.getOcupatie() == null || "".equals(persoana.getOcupatie()))
            errMsg += "!! Ocupatie invalida !!\n";
        if (!errMsg.isEmpty())
            throw new ValidatorException(errMsg);
    }
}
