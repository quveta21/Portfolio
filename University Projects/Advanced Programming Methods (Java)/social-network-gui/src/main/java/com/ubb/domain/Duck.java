package com.ubb.domain;

import com.ubb.relations.Card;

public abstract class Duck extends User {
    private TipRata tip;
    private double viteza;
    private double rezistenta;
    private Card card;

    public Duck(long id, String username, String email, String password, TipRata tip, double viteza, double rezistenta) {
        super(id, username, email, password);
        this.tip = tip;
        this.viteza = viteza;
        this.rezistenta = rezistenta;
        this.card = null;
    }

    public TipRata getTip() {
        return tip;
    }

    public double getViteza() {
        return viteza;
    }

    public double getRezistenta() {
        return rezistenta;
    }

    public Card<?> getCard() {
        return card;
    }

    public void setCard(Card<?> card) {
        this.card = card;
    }

    @Override
    public String toString() {
        return "Duck{" +
                "username='" + getUsername() + '\'' +
                ", rezistenta=" + rezistenta +
                ", viteza=" + viteza +
                ", tip=" + tip +
                //", card=" + card.getNumeCard() +
                '}';
    }
}
