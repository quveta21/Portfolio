package com.ubb.validation;

import com.ubb.domain.Duck;
import com.ubb.domain.Persoana;
import com.ubb.domain.TipRata;
import com.ubb.exceptions.ValidatorException;

public class DuckValidator implements Validator<Duck> {
    // composition !!!
    private final UserValidator userValidator = new UserValidator();

    @Override
    public void validate(Duck duck) {
        userValidator.validate(duck);   // validam strict partea de user
        // acum validam atributele specifice ratei
        String errMsg = "";
        var tip = duck.getTip();
        if (duck.getTip() == null || (duck.getTip() != TipRata.FLYING &&
        duck.getTip() != TipRata.SWIMMING && duck.getTip() != TipRata.FLYING_AND_SWIMMING))
            errMsg += "!! Tip invalid !!\n";
        if (duck.getViteza() <= 0)
            errMsg += "!! Viteza invalida !!\n";
        if (duck.getRezistenta() <= 0)
            errMsg += "!! Rezistenta invalida !!\n";
        if (!errMsg.isEmpty())
            throw new ValidatorException(errMsg);
    }
}
