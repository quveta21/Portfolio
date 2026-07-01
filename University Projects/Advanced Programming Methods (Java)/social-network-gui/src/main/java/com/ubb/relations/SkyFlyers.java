package com.ubb.relations;

import com.ubb.domain.FlyingDuck;
import com.ubb.domain.TipRata;

public class SkyFlyers extends Card<FlyingDuck>{
    public SkyFlyers(String numeCard) {
        super(numeCard);
    }

    @Override
    public TipRata getTip() {
        return TipRata.FLYING;
    }

    @Override
    public void addMembru(FlyingDuck duck) {
        super.addMembru(duck);
    }
}
