package com.ubb.repository;

import com.ubb.domain.Duck;
import com.ubb.domain.User;
import com.ubb.relations.Card;

public class CardRepository extends InMemoryRepository<Card<? extends Duck>> {
    public CardRepository() { super(); }

    public Card<? extends Duck> findByNume(String numeCard) {
        return getAll().stream()
                .filter(card -> card.getNumeCard().equals(numeCard))
                .findFirst()
                .orElse(null);
    }
}
