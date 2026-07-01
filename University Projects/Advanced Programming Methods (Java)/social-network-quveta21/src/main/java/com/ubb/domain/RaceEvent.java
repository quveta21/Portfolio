package com.ubb.domain;

import java.util.Arrays;
import java.util.Comparator;

public class RaceEvent extends Event {
    private Duck[] rate;
    private Culoar[] culoare;

    public RaceEvent(int eventId, Duck[] ducks, Culoar[] culoare) {
        super(eventId);
        this.eventId = eventId;
        this.rate = ducks;
        this.culoare = culoare;
    }

    public Duck[] getRate() {
        return this.rate;
    }

    public void setRate(Duck[] rate) {
        this.rate = rate;
    }

    public Culoar[] getCuloare() {
        return culoare;
    }

    @Override
    public String toString() {
        return super.toString() + ": RaceEvent{" +
                "rate=" + Arrays.toString(rate) +
                ", culoare=" + Arrays.toString(culoare) +
                '}';
    }

    public void writeSolution(Solution sol){
        System.out.println(sol.toString());
    }

    public void sortRate() {
        Arrays.sort(rate, Comparator.comparingDouble(Duck::getRezistenta));
    }

    public double maxDistance() {
        return culoare[culoare.length - 1].getBaliza();     // culoarele sunt deja sortate deci luam ultimul
    }

    public double minSpeed() {
        double min =  Double.MAX_VALUE;
        for (Duck r : rate) {
            if (r.getViteza() < min) {
                min = r.getViteza();
            }
        }
        return min;
    }

    public double calculateTime(Duck rata, Culoar culoar) {
        return 2.0 * culoar.getBaliza() / rata.getViteza();
    }

    public boolean eligibil(Duck rata, Culoar culoar, double T) {
        double time = calculateTime(rata, culoar);
        return (time <= T) || (T - time <= 1e-3);
    }

    public Duck[] fezabil(double T) {
        boolean[] folosit = new boolean[rate.length];
        Duck[] sol = new Duck[culoare.length];

        for (int ci = 0; ci < culoare.length; ci++) {
            Culoar c = culoare[ci];
            boolean gasit = false;

            for (int di = 0; di < rate.length; di++) {
                Duck r = rate[di];

                if (!folosit[di] && eligibil(r, c, T)) {
                    folosit[di] = true;
                    sol[ci] = r;
                    gasit = true;
                    break;
                }
            }

            if (!gasit) {
                //System.out.println("NU AM GASIT RATA PT CULOARUL " + c.getId());
                return null;
            }
        }

        return sol;
    }


    public Solution findOptimalSolution() {
        sortRate();     // trebuie sortate dupa rezistenta pentru o cautare optima

        double left = 0.0;
        double right = 2.0 * maxDistance() / minSpeed();    // timpul maxim e parcurs de cea mai lenta rata
        // pe cel mai lung culoar

        Duck[] bestAssignment = null;
        double bestTime = right;
        //StackContainer bestTasks = null;

        while (right - left > 1e-3) {       // precizia de 0.001
            double mid = (left + right) / 2.0;

            //taskRunner.flushTasks();     // golim lista anterioara de task-uri pentru a ramane doar cu solutia optima

            Duck[] candidate = fezabil(mid);

            if (candidate != null) {
                // solutie valida -> incercam un timp mai mic
                bestAssignment = candidate;
                bestTime = mid;
                //bestTasks = taskRunner.getContainerCopy();
                right = mid;    // cautam in stanga -> mai mic
            }
            else {
                left = mid;     // prea mic T, cautam mai mare
            }
        }
//        if (bestTasks != null) {
//            taskRunner.setContainer(bestTasks);
//        }

        //calculez efectiv timpul maxim din bestAssignment
        if (bestAssignment != null) {
            bestTime = 0.0;
            for (int i = 0; i < bestAssignment.length; i++) {
                //DuckTask dt = new DuckTask(bestAssignment[i], culoare[i]);
                double time = calculateTime(bestAssignment[i], culoare[i]);
                if (time > bestTime) {
                    bestTime = time;
                }
            }
        }

        return new Solution(bestAssignment, culoare, bestTime);
    }
}
