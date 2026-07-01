package com.ubb.relations;

import com.ubb.domain.SwimmingDuck;
import com.ubb.domain.TipRata;

public class SwimMasters extends Card<SwimmingDuck>{
    public SwimMasters(String numeCard) {
        super(numeCard);
    }

    @Override
    public TipRata getTip() {
        return TipRata.SWIMMING;
    }

    @Override
    public void addMembru(SwimmingDuck duck) {
        super.addMembru(duck);
    }
}
