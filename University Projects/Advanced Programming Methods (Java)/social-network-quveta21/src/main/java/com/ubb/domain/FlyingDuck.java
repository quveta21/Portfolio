package com.ubb.domain;

public class FlyingDuck extends Duck implements Zburator{
    public FlyingDuck(long id, String username, String email, String password, TipRata tip, double viteza, double rezistenta) {
        super(id, username, email, password, tip, viteza, rezistenta);
    }

    @Override
    public void zboara() {

    }
}
