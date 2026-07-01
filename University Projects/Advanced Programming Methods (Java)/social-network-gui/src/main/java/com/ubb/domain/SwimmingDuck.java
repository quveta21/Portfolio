package com.ubb.domain;

public class SwimmingDuck extends Duck implements Inotator{
    public SwimmingDuck(long id, String username, String email, String password, TipRata tip, double viteza, double rezistenta) {
        super(id, username, email, password, tip, viteza, rezistenta);
    }

    @Override
    public void inoata() {

    }
}
