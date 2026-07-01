package com.ubb.relations;

import com.ubb.domain.Duck;
import com.ubb.domain.TipRata;

import java.util.ArrayList;
import java.util.List;

public abstract class Card<T extends Duck> {
    //private long id;
    private String numeCard;
    private List<T> membri;

    public Card(String numeCard) {
        //this.id = id;
        this.numeCard = numeCard;
        this.membri = new ArrayList<>();
    }

    @Override
    public String toString() {
        return "Card{" +
                "numeCard='" + numeCard + '\'' +
                ", membri=" + membri +
                '}';
    }

//    public long getId() {
//        return id;
//    }

    public String getNumeCard() {
        return numeCard;
    }

    public List<T> getMembri() {
        return membri;
    }

    public abstract TipRata getTip();

    public void addMembru(T t) {
        membri.add(t);
        t.setCard(this);
    }

    public void removeMembru(T t) {
        membri.remove(t);
        t.setCard(null);
    }

    public double getAverageSpeed() {
        double sum = 0;
        for (T t : membri) {
            sum += t.getViteza();
        }
        return sum / membri.size();
    }

    public double getAverageResistance() {
        double sum = 0;
        for (T t : membri) {
            sum += t.getRezistenta();
        }
        return sum / membri.size();
    }
}
