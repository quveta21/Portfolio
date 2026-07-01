package com.ubb.exceptions;

// checked
//public class ValidatorException extends Exception {
//    public ValidatorException(String message) {
//        super(message);
//    }
//}

// unchecked
public class ValidatorException extends MyException {
    public ValidatorException(String message) {
        super(message);
    }
}