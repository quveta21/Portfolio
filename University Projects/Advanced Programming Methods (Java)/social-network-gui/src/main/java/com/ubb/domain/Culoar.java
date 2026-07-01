package com.ubb.domain;

public class Culoar {
    public int id;
    private double baliza;

    public Culoar(int id, double baliza) {
        this.id = id;
        this.baliza = baliza;
    }

    public int getId() {
        return id;
    }

    public double getBaliza() {
        return baliza;
    }

    @Override
    public String toString() {
        return "Culoar{" +
                "id=" + id +
                ", baliza=" + baliza +
                '}';
    }
}
