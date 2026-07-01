package com.ubb.relations;

import com.ubb.domain.FlyingSwimmingDuck;
import com.ubb.domain.TipRata;

public class SkySwimmers extends Card<FlyingSwimmingDuck> {
    public SkySwimmers(String numeCard) {
        super(numeCard);
    }

    @Override
    public TipRata getTip() {
        return TipRata.FLYING_AND_SWIMMING;
    }

    @Override
    public void addMembru(FlyingSwimmingDuck duck) {
        super.addMembru(duck);
    }
}
