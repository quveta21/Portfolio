package com.ubb.validation;

import com.ubb.domain.User;
import com.ubb.exceptions.ValidatorException;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User user) {
        String errMsg = "";
        if (user.getUsername() == null || "".equals(user.getUsername()))
            errMsg += "!! Username invalid !!\n";
        if (user.getPassword() == null || "".equals(user.getPassword()))
            errMsg += "!! Password invalid !!\n";
        if (user.getEmail() == null || (!user.getEmail().contains("@") &&  !user.getEmail().contains(".com")))
            errMsg += "!! Email invalid !!\n";
        if (!errMsg.isEmpty())
            throw new ValidatorException(errMsg);
    }
}
