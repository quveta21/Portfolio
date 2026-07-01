package com.ubb.domain;

public class Solution {
    private final Duck[] rata;
    private final Culoar[] culoar;
    private double timp;

    public Solution(Duck[] rata, Culoar[] culoar, double timp) {
        this.rata = rata;
        this.culoar = culoar;
        this.timp = timp;
    }

    public Duck[] getRate() {
        return rata;
    }

    @Override
    public String toString() {
        if (this.rata == null || this.culoar == null) {
            return "No feasible solution found.\n";
        }
        String output = String.format("Best time: %.3f s%n", this.timp);
        for (int i = 0; i < this.culoar.length; i++) {
            output += "Lane " + this.culoar[i].getId() + " (d=" + this.culoar[i].getBaliza() + ") <- " +
                    "Duck " + this.rata[i].getId() + " (v=" + this.rata[i].getViteza() +
                    ", st=" + this.rata[i].getRezistenta() + ")\n";
        }
        return output;
    }
}
