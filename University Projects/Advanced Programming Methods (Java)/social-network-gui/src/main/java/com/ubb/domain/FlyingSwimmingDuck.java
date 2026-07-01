package com.ubb.domain;

public class FlyingSwimmingDuck extends Duck implements Inotator, Zburator{
    public FlyingSwimmingDuck(long id, String username, String email, String password, TipRata tip, double viteza, double rezistenta) {
        super(id, username, email, password, tip, viteza, rezistenta);
    }

    @Override
    public void zboara() {

    }

    @Override
    public void inoata() {

    }
}
